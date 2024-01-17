/* 
 * File:   main.cpp
 * Author: philippe SIMIER Lycée Touchard
 *
 * Created on 20 mars 2022, 12:24
 * 
 */

#include <Arduino.h>
#include <WiFi.h>
#include <DateTimeManager.h>
#include <Afficheur.h>
#include <RTClib.h>


DateTimeManager dtm;
Afficheur *afficheur;    // Un afficheur Oled
RTC_DS3231 rtc_DS3231;   // Une horloge temps réel DS3231

const char *ssid     = "PA_philippe";
const char *password = "ygyc3556";


void setup() {

    Serial.begin(115200);
    afficheur = new Afficheur;
    
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        afficheur->afficher('.');
    }
    Serial.println("Connecté au réseau WiFi");
    
    if (dtm.synchroniser()){
        Serial.println("La mise à jour de la date et de l'heure a réussi");
    }
    
    // Synchronise l'horloge temps réel DS3231
    if (rtc_DS3231.begin()) {
        time_t now;
        time(&now);
        rtc_DS3231.adjust(DateTime((uint32_t)now));
    }  else {
        Serial.println("Une erreur est apparue pendant le démarrage de la RTC DS3231");
    }

}

void loop() {

    // time_t Type arithmétique le nombre de secondes depuis 00h00, le 1er janvier 1970 UTC
    time_t now;

    // renvoie l'heure actuelle du système sous forme de temps depuis l'époque
    time(&now);

    dtm.printDateTime(now);
    afficheur->afficherDateTime(now);
    
    delay(1000);
    // Affichage de l'heure renvoyée par la rtc DS3231
    dtm.printDateTime(rtc_DS3231.now().unixtime());
    afficheur->afficherDateTime(rtc_DS3231.now().unixtime());
    
    delay(1000);
}

