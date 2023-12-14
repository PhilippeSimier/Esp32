/* 
 * File:   echo_serial.cpp
 * Author: philippe
 *
 * Created on 14 décembre 2023, 07:42
 */

#include <Arduino.h>

    void setup() {
        Serial.begin(115200);
        Serial.println("Echo Serial");
    }

    void loop() {

        char car;

        if (Serial.available() > 0) {
            car = Serial.read();
            Serial.write(car);
        }
    }
