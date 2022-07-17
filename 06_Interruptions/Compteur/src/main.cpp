/* 
 * File:   main.cpp
 * Author: philippe SIMIER Touchard Washington
 *
 * Created on 16 juillet 2022, 09:32
 */

#include <Arduino.h>
#include <Compteur.h>

const int LED = 2;
const int BP = 33;


Compteur C1(BP,250);
Compteur C2(13,250);

void setup() {
    
    pinMode(LED, OUTPUT);
    Serial.begin(115200);
    Serial.println("Test BP");

    digitalWrite(LED, 0);    
}

void loop() {
    
    Serial.printf("compteur 1 : %d\r\n", C1.getValue());
    Serial.printf("compteur 2 : %d\r\n", C2.getValue());
    
    if (C1.getValue()%10 == 0) 
        digitalWrite(LED, 1);
    else
        digitalWrite(LED, 0);
    
    delay(10000);
}

