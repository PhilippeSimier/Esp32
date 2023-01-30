/* 
 * File:   rx_fm.cpp
 * Author: philippe SIMIER
 *
 * Created on 30 janvier 2023, 11:46
 */

#include <Arduino.h>
#include <RDA5807.h>

RDA5807 rx;
bool checkI2C();

void setup() {

    Serial.begin(115200);
    while (!Serial);

    delay(500);



    if (!checkI2C()) {
        Serial.println("\nCheck your circuit!");
        while (1);
    }


    rx.setup();
    rx.setVolume(3);


    delay(500);
    //****
    Serial.print("RTL 104.3MHz\n\r");
    rx.setFrequency(10430); // The frequency you want to select in MHz multiplied by 100.

    Serial.print("\n\rCurrent Channel: ");
    Serial.print(rx.getRealChannel());
    delay(500);

    Serial.print("\n\rReal Frequency.: ");
    Serial.print(rx.getRealFrequency());

    Serial.print("\n\rRSSI: ");
    Serial.print(rx.getRssi());


    // Mute test
    Serial.print("\n\rAfter 5s device will mute during 3s");
    delay(5000);
    rx.setMute(true);
    delay(3000);
    rx.setMute(false);
    Serial.print("\n\rMute test has finished.");

    // Seek test
    Serial.print("\n\rSeek station");
    for (int i = 0; i < 10; i++) {
        rx.seek(1, 0);
        Serial.print("\n\rReal Frequency.: ");
        Serial.print(rx.getRealFrequency());
        delay(5000);
    }


    Serial.print("\n\rRTL 104.3MHz\n\r");
    rx.setFrequency(10430);


}

void loop() {



}

/**
 * Returns true if device found
 */
bool checkI2C() {
    Wire.begin();
    byte error, address;
    int nDevices;
    Serial.println("I2C bus Scanning...");
    nDevices = 0;
    for (address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        if (error == 0) {
            Serial.print("\nI2C device found at address 0x");
            if (address < 16) {
                Serial.print("0");
            }
            Serial.println(address, HEX);
            nDevices++;
        } else if (error == 4) {
            Serial.print("\nUnknow error at address 0x");
            if (address < 16) {
                Serial.print("0");
            }
            Serial.println(address, HEX);
        }
    }
    if (nDevices == 0) {
        Serial.println("No I2C devices found\n");
        return false;
    } else {
        Serial.println("done\n");
        return true;
    }
}
