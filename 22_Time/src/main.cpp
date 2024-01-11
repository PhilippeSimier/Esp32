/* 
 * File:   main.cpp
 * Author: philippe SIMIER
 *
 * Created on 20 mars 2022, 12:24
 * 
 */

#include <Arduino.h>



const char * months[] = {
    "Janv.", "Févr.", "Mars", "Avr.", "Mai", "Juin", "Juil.",
    "Août", "Sept.", "Oct.", "Nov.", "Déc."
};

const char * days[] = {
    "Dim.", "Lun.", "Mar.", "Mer.", "Jeu.", "Ven.", "Sam."
};

void setup() {

    Serial.begin(115200);
    
    struct timeval new_time;
    new_time.tv_sec = 1704981007; // 11 Janvier 2024 13:50:07
    if (settimeofday(&new_time, NULL) == 0) {
        Serial.printf("La mise à jour de la date et de l'heure a réussi.\r\n");
    }
    
    // Définir la timezone sur Paris (Central European Time)
    if (setenv("TZ", "CET-1CEST,M3.5.0,M10.5.0/3", 1) != 0) {
        Serial.printf("Erreur lors de la définition de la timezone");
       
    }

    // Mettre à jour la variable d'environnement TZ
    tzset();

}

void loop() {

    struct tm timeInfo;
    time_t now;    // time_t Type arithmétique le nombre de secondes depuis 00h00, le 1er janvier 1970 UTC
    
    time(&now);   // renvoie l'heure actuelle du système sous forme de temps depuis l'époque
    
   
    
    localtime_r(&now, &timeInfo);  // convertit l'heure depuis l'époque en heure calendaire exprimée en heure locale
    
    Serial.printf("%s %d %s %d ",
            days[timeInfo.tm_wday],
            timeInfo.tm_mday,
            months[timeInfo.tm_mon],
            timeInfo.tm_year + 1900);

    Serial.println(&timeInfo, "%H:%M:%S");
    
    delay(1000);
}

