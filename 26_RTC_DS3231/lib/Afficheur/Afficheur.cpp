/* 
 * File:   Afficheur.cpp
 * Author: philippe Simier Touchard Washington
 * 
 * Created on 14 février 2022, 12:18 V1.0
 * improved on 30 November 2023
 */

#include "Afficheur.h"


// Constructeur de Afficheur
// Sur la carte PCT  adresse 0x3c connecté sur SDA et SCL

Afficheur::Afficheur() :
SSD1306Wire(0x3c, SDA, SCL, GEOMETRY_128_64) {
    init();
    setFont(ArialMT_Plain_24);
    flipScreenVertically();
    message = "";
}

Afficheur::~Afficheur() {
}

/**
 * Méthode pour afficher un message
 * @param message String le message à afficher
 */
void Afficheur::afficher(const String message) {
    clear();
    drawStringMaxWidth(0, 0, 110, message);
    display();
}

/**
 * Méthode pour afficher les 10 derniers caractères reçus
 * @param car le caractère suivant à placer sur l'afficheur
 */
void Afficheur::afficher(const char car) {
    switch (car) {
        case 0x7F:
            message = "";
            break;
        case '\b':
            message = message.substring(0, message.length() - 1);
            break;
        default:
            message += String(car);
    }
    
    if (message.length() > 10){
        message = message.substring(1);
    }
    clear();
    drawString(0, 0, message);
    display();

}

/**
 * Méthode pour afficher un mot de passe
 * @param message le mot de passe
 */
void Afficheur::afficherMdp(const String message) {
    clear();
    String psd;
    for (int i = 0; i < message.length(); i++) {
        psd += "*";

    }
    drawStringMaxWidth(0, 0, 110, psd);
    display();
}

/**
 * Méthode pour afficher une grandeur physique
 * @param char* message le libellé
 * @param valeur  la valeur à afficher
 * @param unite   l'unite de la grandeur
 */
void Afficheur::afficherFloat(const String message, const float valeur, const String unite) {

    char sz[32];
    snprintf(sz, sizeof (sz), "%.1f", valeur);
    String valst(sz);
    afficher(message + valst + unite);

}

/**
 * Méthode pour afficher une date et l'heure
 * @param dateTime
 */
void Afficheur::afficherDateTime(const DateTime dateTime){
    
    char date[13];
    snprintf(date, sizeof(date), "%02d:%02d:%4d", dateTime.day(), dateTime.month(), dateTime.year());
    char time[11];
    snprintf(time, sizeof(time), "%02d:%02d:%02d", dateTime.hour(), dateTime.minute(), dateTime.second());
    char message[26];
    snprintf(message, sizeof(message), "%s\n%s", date, time);
    
    setFont(Dialog_plain_19);
    afficher(message);
    setFont(ArialMT_Plain_24);
}
