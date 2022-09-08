/* 
 * File:   coffreHotel.cpp
 * Author: psimier
 *
 * Created on 6 septembre 2022, 14:57
 */

#include <Arduino.h>
#include <Coffre.h>

Coffre *leCoffre;

void setup() {
    Serial.begin(115200);
    leCoffre = new Coffre;
}

void loop() {
    leCoffre->Controler();
}

