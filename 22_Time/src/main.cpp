/* 
 * File:   main.cpp
 * Author: philippe SIMIER
 *
 * Created on 20 mars 2022, 12:24
 * 
 */

#include <Arduino.h>
#include <ESP32Time.h>

ESP32Time rtc;

const char * months[] = {
    "Janvier", "Février", "Mars", "Avril", "Mai", "Juin", "Juillet",
    "Août", "Septembre", "Octobre", "Novembre", "Décembre"
};

const char * days[] = {
    "Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"
};

void setup() {

    Serial.begin(115200);
    rtc.setTime(30, 24, 15, 10, 1, 2024); // 10th January 2024 15:24:30

}

void loop() {

    struct tm now = rtc.getTimeStruct();

    Serial.printf("%s %d %s %d ",
            days[now.tm_wday],
            now.tm_mday,
            months[now.tm_mon],
            now.tm_year + 1900);

    Serial.println(&now, "%H:%M:%S");


    delay(1000);
}

