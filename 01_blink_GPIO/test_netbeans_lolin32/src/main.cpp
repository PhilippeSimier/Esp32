/* 
 * File:   main.cpp
 * Author: philippe
 *
 * Created on 5 novembre 2021, 17:42
 */

#include <Arduino.h>

int LED = 2;

void setup() 
{
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  Serial.println("Setup done");
  
}

void loop() 
{
  digitalWrite(LED, digitalRead(LED) ^1);   // turn the LED 
  delay(500);                       // wait for 0.2 second
  digitalWrite(LED, digitalRead(LED) ^1);    // turn the LED 
  delay(2000);                       // wait for 2 seconds
}