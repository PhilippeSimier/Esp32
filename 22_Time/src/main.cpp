/* 
 * File:   main.cpp
 * Author: philippe SIMIER
 *
 * Created on 20 mars 2022, 12:24
 * 
 */

#include <Arduino.h>
#include <DateTimeManager.h>
#include <Afficheur.h>


DateTimeManager dtm;
Afficheur *afficheur; // Un afficheur Oled
struct tm timeInfo;
time_t now;

void setup() {

    Serial.begin(115200);
       
    if (dtm.setCurrentTime(946684800) == 0)  // Unixtime for Sat Jan 01 2000 00:00:00 GMT+0000
        Serial.println("La mise à jour de la date et de l'heure a réussie"); 
    
    afficheur = new Afficheur;
}

void loop() {

    dtm.printCurrentTime();
    time(&now);
    localtime_r(&now, &timeInfo);
    afficheur->afficherDateTime(timeInfo);
    
    delay(1000);
}

