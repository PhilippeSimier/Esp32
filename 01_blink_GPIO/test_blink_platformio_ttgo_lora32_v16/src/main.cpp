/* 
 * File:   main.cpp
 * Author: philippe
 *
 * Created on 29 mai 2022, 20:20
 * 
 * Board  T3 1.6
 * 
 */

#include <Arduino.h>

#define LED 25 //green led 

void setup()
{
    pinMode(LED, OUTPUT);
    Serial.begin(115200);
    Serial.println("Setup done");
}

void loop()
{
    digitalWrite(LED, digitalRead(LED) ^1); // turn the LED
    delay(200); // wait for 0.2 second
    digitalWrite(LED, digitalRead(LED) ^1); // turn the LED 
    delay(2000); // wait for 2 seconds
    
}

