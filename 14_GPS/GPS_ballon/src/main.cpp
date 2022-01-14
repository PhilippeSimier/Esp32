/*
 * Bibliothèque TinyGPS installation
 * pio lib -g install 416
 */

#include <TinyGPS.h>
#include <HardwareSerial.h>

static void print_date(TinyGPS &gps);
static bool lectureCapteur(unsigned long ms);

TinyGPS gps;
HardwareSerial serialGps(2); // sur hardware serial 2

void setup() {
    Serial.begin(115200);
    serialGps.begin(4800, SERIAL_8N1, 16, 17);
    delay(1000);
    Serial.print("Simple TinyGPS library v. ");
    Serial.println(TinyGPS::library_version());
}

void loop() {
    bool newData = false;

    newData = lectureCapteur(1000);

    if (newData) {
        float flat, flon;
        unsigned long age;
        gps.f_get_position(&flat, &flon, &age);
        Serial.print(" Latitude = ");
        Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
        Serial.print(" Longitude = ");
        Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
        Serial.print(" Altitude = ");
        Serial.println(gps.f_altitude());
        Serial.print(" Nb Satellites = ");
        Serial.println(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
        print_date(gps);
    }
}

static void print_date(TinyGPS &gps)
{
    int year;
    byte month, day, hour, minute, second, hundredths;
    unsigned long age;
    gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
    if (age == TinyGPS::GPS_INVALID_AGE)
        Serial.print("********** ******** ");
    else
    {
        char sz[32];
        sprintf(sz, "%02d/%02d/%02d %02d:%02d:%02d ",
                day, month, year, hour, minute, second);
        Serial.print(sz);
    }
}

static bool lectureCapteur(unsigned long ms){
    bool newData = false;
    unsigned long start = millis();
    do
    {
        while (serialGps.available())
            if (gps.encode(serialGps.read())){
                newData = true;
            }
    } while (millis() - start < ms);
    return newData;
}
