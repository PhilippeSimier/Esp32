#include <TinyGPS.h>
#include <HardwareSerial.h>

#define LED 22

TinyGPS gps;
HardwareSerial serialGps(2);  // sur hardware serial 2

void setup() {
    Serial.begin(115200);
    serialGps.begin(4800, SERIAL_8N1, 16, 17);

    // initialize digital pin LED_BUILTIN as an output.
    pinMode(LED, OUTPUT);
    Serial.print("Simple TinyGPS library v. ");
    Serial.println(TinyGPS::library_version());
}

void loop() {
    bool newData = false;
    unsigned long chars;
    unsigned short sentences, failed;
    
    // Pendant une seconde lecture des caractères envoyés par le GPS
    for (unsigned long start = millis(); millis() - start < 1000;) {
        while (serialGps.available()) {
            char c = serialGps.read();
            // Serial.write(c);   
            if (gps.encode(c)) // si des caratères sont reçus alors newdata = true
                newData = true;
        }
    }

    if (newData) {
        float flat, flon;
        unsigned long age;
        gps.f_get_position(&flat, &flon, &age);
        Serial.print("LAT=");
        Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
        Serial.print(" LON=");
        Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
        //Serial.print(" SAT=");
        //Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
        //Serial.print(" PREC=");
        //Serial.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
        Serial.print(" altitude=");
        Serial.println(gps.f_altitude());
    }

    gps.stats(&chars, &sentences, &failed);
    /*Serial.print(" CHARS=");
    Serial.print(chars);
    Serial.print(" SENTENCES=");
    Serial.print(sentences);
    Serial.print(" CSUM ERR=");
    Serial.println(failed);*/
    if (chars == 0)
        Serial.println("** No characters received from GPS: check wiring **");
}



