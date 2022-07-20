/*
 * File:   main.cpp
 * Author: Anthony Le Cren 
 *         Lycée Touchard Washington Le Mans
 * 
 *
 * Created on 20 juillet 2022, 15:42
 *
 *
 * 
 * connect TM1637 pin CLK to GPIO 14
 * connect TM1637 pin DIO to GPIO 27
 * connect TM1637 pin Vcc to 5V or 3.3V
 * connect TM1637 pin GND to GND
 **/

#include <Arduino.h>
#include <TM1637TinyDisplay6.h>       // Include 6-Digit Display Class Header


// Define Digital Pins
#define CLK 14
#define DIO 27
#define LED 2

TM1637TinyDisplay6 display(CLK, DIO); // 6-Digit Display Class
float val = 10.0;

void setup() {

    pinMode(LED, OUTPUT);
    Serial.begin(115200);
    Serial.println("Setup done");

    display.setBrightness(BRIGHT_HIGH); // BRIGHT_LOW BRIGHT_0 to BRIGHT_7 and BRIGHT_HIGH
    display.clear();
    display.showString("HELLO F4KMN");
    delay(1000);
    display.showNumber(421);
    delay(1000);
    display.showNumber(123.456);
    delay(1000);
}

void loop() {

    digitalWrite(LED, digitalRead(LED) ^1); // turn the LED 
    delay(100); // wait for 0.1 second
    digitalWrite(LED, digitalRead(LED) ^1); // turn the LED 
    delay(100); // wait for 0.1 second
    display.showNumber(val);
    val += 0.01;
}