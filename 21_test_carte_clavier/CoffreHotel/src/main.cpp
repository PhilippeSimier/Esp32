
/* 
 * File:   main.cpp
 * Author: fmartin
 *
 * Created on 1 février 2022, 23:55
 */

#include <Arduino.h>
#include "Coffre.h"

Coffre *leCoffre;

void setup() {
    Serial.begin(115200);
    leCoffre = new Coffre;
}

void loop() {
    leCoffre->Controler();
}