/* 
 * File:   rx_fm.cpp
 * Author: philippe SIMIER
 * 
 * Created on 30 janvier 2023, 11:46
 */

#include <Arduino.h>
#include <RDA5807.h>
#include <driver/adc.h>
#include <Keypad.h>

RDA5807 rx;
bool checkI2C();
int vol_avant = 3;
bool mute = false;

// Déclaration des caractères sur les touches
char keys[4][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};

byte rowPins[4]{26, 25, 33, 32};
byte colPins[3]{15, 5, 4};

Keypad clavier = Keypad((char *) keys, rowPins, colPins, 4, 3);

void setup() {

    Serial.begin(115200);
    while (!Serial);

    // plage de valeurs de 0 à 4095. (ADC_WIDTH_BIT_12)
    adc1_config_width(ADC_WIDTH_BIT_12);
    //11 dB pour une tension d’entrée de 0.15v à 3.6v sur l'entrée analogique
    adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);

    delay(500);

    if (!checkI2C()) {
        Serial.println("\nCheck your circuit!");
        while (1);
    }

    rx.setup();
    rx.setVolume(3);

    delay(500);
    Serial.print("RTL 104.3MHz\n\r");
    rx.setFrequency(10430); // The frequency you want to select in MHz multiplied by 100.

    Serial.print("\n\rCurrent Channel: ");
    Serial.print(rx.getRealChannel());
    delay(500);

    Serial.print("\n\rReal Frequency.: ");
    Serial.print(rx.getRealFrequency());

    Serial.print("\n\rRSSI: ");
    Serial.print(rx.getRssi());

}

void loop() {

    int value = adc1_get_raw(ADC1_CHANNEL_0);
    // Mise à l'échelle
    int vol = map(value, 0, 4095, 0, 15);

    if (vol != vol_avant) {

        rx.setVolume(vol);
        if (!mute) {
            Serial.print("\n\rVolume = ");
            Serial.print(vol);
        }
        vol_avant = vol;
        delay(500);
    }

    char key = clavier.getKey();
    if (key) {
        switch (key) {
            case '*':
                Serial.print("\n\rSeek down station");
                rx.seek(1, 0);
                delay(100);
                Serial.print("\n\rReal Frequency : ");
                Serial.print(rx.getRealFrequency()/100.0);
                Serial.print(" MHz");
                break;

            case '#':
                Serial.print("\n\rSeek up station");
                rx.seek(1, 1);
                delay(100);
                Serial.print("\n\rReal Frequency : ");
                Serial.print(rx.getRealFrequency()/100.0);
                Serial.print(" MHz");
                break;

            case '0':
                if (!mute) {
                    rx.setMute(true);
                    Serial.print("\n\rRadio is Mute");
                    mute = true;

                } else {
                    rx.setMute(false);
                    Serial.print("\n\rVolume = ");
                    Serial.print(rx.getVolume());
                    mute = false;
                }
                break;
                delay(500);

        }
    }


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
