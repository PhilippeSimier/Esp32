/* 
 * File:   rtc.cpp
 * Author: philippe SIMIER Touchard Washington
 *
 * Created on 28 décembre 2023, 09:57
 * 
 * 
 */

#include <Arduino.h>
#include <Afficheur.h>
#include <RTClib.h>

#define LED 2

RTC_DS3231 rtc;
Afficheur *afficheur; // Un afficheur Oled

char daysOfTheWeek[7][10] = {"Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"};

void setup() {
    Serial.begin(115200);
    pinMode(LED, OUTPUT);
    if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
        Serial.flush();
        while (1) delay(10);
    }
    if (rtc.lostPower()) {
        Serial.println("RTC lost power, let's set the time!");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
    afficheur = new Afficheur;
}

void loop() {
    
    DateTime now = rtc.now(); 
    afficheur->afficherDateTime(now);
    
    Serial.println(daysOfTheWeek[now.dayOfTheWeek()]);      
    delay(1000);
}