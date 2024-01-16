/* 
 * File:   main.cpp
 * Author: philippe SIMIER
 *
 * Created on 20 mars 2022, 12:24
 * 
 */

#include <Arduino.h>
#include <WiFi.h>
#include <DateTimeManager.h>
#include <Afficheur.h>


DateTimeManager dtm;
Afficheur *afficheur; // Un afficheur Oled

const char *ssid     = "Livebox-5648";
const char *password = "vz9Lcc2RnTTmnDuD4Y";


void setup() {

    Serial.begin(115200);
    afficheur = new Afficheur;
    unsigned long maintenant;
    
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

}

void loop() {

    // time_t Type arithmétique le nombre de secondes depuis 00h00, le 1er janvier 1970 UTC
    time_t now;

    // renvoie l'heure actuelle du système sous forme de temps depuis l'époque
    time(&now);


    dtm.printCurrentTime(now, Serial);
    afficheur->afficherDateTime(now);

    
    
    delay(1000);
}

