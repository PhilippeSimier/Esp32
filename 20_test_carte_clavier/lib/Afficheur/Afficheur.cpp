/* 
 * File:   Afficheur.cpp
 * Author: philippe Simier Touchard Washington
 * 
 * Created on 14 février 2022, 12:18
 */

#include "Afficheur.h"


// Constructeur de Afficheur
// Sur la carte PCT  adresse 0x3c connecté sur SDA et SCL

Afficheur::Afficheur() :
SSD1306Wire(0x3c, SDA, SCL, GEOMETRY_128_64) {
    init();
    setFont(ArialMT_Plain_24);
    flipScreenVertically();
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
 * Méthode pour afficher un mot de passe
 * @param message le mot de passe
 */
void Afficheur::afficherMdp(const String message){
    clear();
    String psd;
    for (int i = 0; i<message.length(); i++){
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
    snprintf(sz, sizeof(sz), "%.1f", valeur);
    String valst(sz);
    afficher(message + valst + unite);

}

