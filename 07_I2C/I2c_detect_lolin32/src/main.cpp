/* 
 * File:   main.ino.cpp
 * Author: philippe
 *
 * Created on 14 juillet 2021, 22:11
 */

#include <Arduino.h>
#include <Wire.h>

#define DISPLAY_ERROR false 
#define USER_PIN      false

String I2Ctest() {
    byte error, address;
    int nDevices;
    String s;

    s  = "     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\r\n";
    s += "00:         ";
    
    nDevices = 0;
    for (address = 3; address < 120; address++) {
        if ((address % 16) == 0) {
            s += "\r\n";
            s += String(address, HEX);
            s += ":";
        }
        
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0) {
            s += " ";
            if (address < 16)
                s += "0";
            s += String(address, HEX);
            nDevices++;

        } else {
            s += " --";
        }
        
    }

    s += "\r\n";
    return s;
}

void setup() {
    Serial.begin(115200);
    Serial.println("I2C scanner");

    Wire.begin();
    Wire.setClock(50000);
    size_t clock = Wire.getClock();
    Serial.print("clock : ");
    Serial.println(clock);
    Serial.println(I2Ctest());
}

void loop() {
    
}