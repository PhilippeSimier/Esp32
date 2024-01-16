/* 
 * File:   DateTimeManager.cpp
 * Author: Philippe Simier Lycée Touchard Washington Le Mans
 * 
 * Created on 11 janvier 2024, 17:40
 */

#include "DateTimeManager.h"

DateTimeManager::DateTimeManager() {
    
    ntpServerName = "ntp-p1.obspm.fr";
    timeZone      = "CET-1CEST,M3.5.0,M10.5.0/3";
}

DateTimeManager::~DateTimeManager() {

}

/**
 * @brief   Methode pour synchroniser la RTC avec un serveur de temps
 *          elle permet aussi de définir une timeZone.
 * @return  true si la synchronisation réussie
 */
bool DateTimeManager::synchroniser() {

    struct tm timeinfo;
    int retour;
    
    configTime(0, 0, ntpServerName.c_str(), "pool.ntp.org");  // connexion aux serveurs NTP, avec un offset nul. Temps UTC
    while (!getLocalTime(&timeinfo)) {
        Serial.println("!");
    }
    // Définir la timezone 
    retour = setenv("TZ", timeZone.c_str(), 1);

    // Mettre à jour la variable d'environnement TZ
    tzset();
    
    if (retour == 0)
        return true;
    else return false;
}

int DateTimeManager::setCurrentTime(unsigned long epoch) {

    int retour;
    struct timeval new_time;
    new_time.tv_sec = epoch;
    new_time.tv_usec = 0;

    retour = settimeofday(&new_time, NULL);

    return retour;

}

/**
 * @brief  Méthode pour obtenir le temps epoch courant de la rtc
 * @return le temps epoch 
 */
unsigned long DateTimeManager::getCurrentTime() const {

    struct timeval current_time;
    gettimeofday(&current_time, NULL);

    return current_time.tv_sec;

}

/**
 * @brief Méthode pour écrire la date et l'heure courante Central European Time (CET)
 *        en français. 
 * @param time_t Type arithmétique le nombre de secondes depuis 00h00, le 1er janvier 1970 (UTC)
 *        flux un objet dérivant de Stream (par exemple Serial) 
 */
void DateTimeManager::printCurrentTime(const time_t _time, Stream &flux) const {

    const char * months[] = {
        "Janv.", "Févr.", "Mars", "Avr.", "Mai", "Juin", "Juil.",
        "Août", "Sept.", "Oct.", "Nov.", "Déc."
    };

    const char * days[] = {
        "Dim.", "Lun.", "Mar.", "Mer.", "Jeu.", "Ven.", "Sam."
    };

    struct tm timeInfo;

    // convertit l'heure depuis l'époque en heure calendaire exprimée en heure locale
    localtime_r(&_time, &timeInfo);

    flux.printf("%s %d %s %d ",
            days[timeInfo.tm_wday],
            timeInfo.tm_mday,
            months[timeInfo.tm_mon],
            timeInfo.tm_year + 1900);

    flux.print(&timeInfo, "%H:%M:%S");
    flux.println(" CET");

}



