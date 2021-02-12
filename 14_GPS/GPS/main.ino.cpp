#include <TinyGPS.h>
#include <HardwareSerial.h>


TinyGPS gps;
HardwareSerial serialGps(2); // sur hardware serial 2

void setup() {
    Serial.begin(115200);
    serialGps.begin(4800, SERIAL_8N1, 16, 17);
    Serial.print("Simple TinyGPS library v. ");
    Serial.println(TinyGPS::library_version());
}

void loop() {
    bool newData = false;
    unsigned long chars;


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
        Serial.print(" altitude=");
        Serial.println(gps.f_altitude());
    }


    if (chars == 0)
        Serial.println("** No characters received from GPS: check wiring **");
}



