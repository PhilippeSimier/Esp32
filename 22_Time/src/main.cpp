/* 
 * File:   main.cpp
 * Author: philippe SIMIER
 *
 * Created on 20 mars 2022, 12:24
 * 
 */

#include <Arduino.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <DateTimeManager.h>
#include <Afficheur.h>


DateTimeManager dtm;
Afficheur *afficheur; // Un afficheur Oled

const char *ssid     = "Votre_SSID";
const char *password = "Votre_Mot_De_Passe";
WiFiUDP ntpUDP;
const char *ntpServerName = "ntp-p1.obspm.fr";
NTPClient timeClient(ntpUDP, ntpServerName);

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

    
    timeClient.begin();
    
    while ( !timeClient.update()){
        
        Serial.print("!");
        afficheur->afficher('!');
        delay(500);
    }
    maintenant = timeClient.getEpochTime();
    Serial.println(maintenant);
    if (dtm.setCurrentTime(maintenant) == 0){
        Serial.println("La mise à jour de la date et de l'heure a réussie");
        afficheur->afficher("Synchro\nTime OK");

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

