#include <Arduino.h>
#include <SPI.h>
#include <BME280.h>
#include <BME280I2C.h>

int LED = 2;


BME280I2C::Settings parametrage(
        BME280::OSR_X1,
        BME280::OSR_X1,
        BME280::OSR_X1,
        BME280::Mode_Forced,
        BME280::StandbyTime_1000ms,
        BME280::Filter_16,
        BME280::SpiEnable_False,
        BME280I2C::I2CAddr_0x77 // I2C address 77 pour BME 280 Adafruit.
        );

BME280I2C *bme;

void setup() {
    pinMode(LED, OUTPUT);
    Serial.begin(115200);


    bme = new BME280I2C(parametrage);
    while (!bme->begin()) {
        Serial.println("Could not find BME280 sensor!");
        delay(1000);
    }

    switch (bme->chipModel()) {
        case BME280::ChipModel_BME280:
            Serial.println("Found BME280 sensor! Success.");
            break;
        case BME280::ChipModel_BMP280:
            Serial.println("Found BMP280 sensor! No Humidity available.");
            break;
        default:
            Serial.println("Found UNKNOWN sensor! Error!");
    }


}

void loop() {
    digitalWrite(LED, digitalRead(LED) ^1); // turn the LED 
    delay(200); // wait for 0.2 second
    digitalWrite(LED, digitalRead(LED) ^1); // turn the LED 
    delay(2000); // wait for 2 seconds
}