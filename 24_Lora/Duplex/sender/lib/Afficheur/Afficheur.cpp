/* 
 * File:   Afficheur.cpp
 * Author: philippe SIMIER Lycée Touchard Washington
 * 
 * Created on 11 février 2022, 11:15
 */

#include "Afficheur.h"

// Constructeur de Afficheur
// Sur la carte Ballon adresse 0x3c connecté sur SDA et SCL

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
void Afficheur::afficher(String message1, String message2) {
    clear();
    drawString(0,0, message1 );
    drawStringMaxWidth(0, 32, 110, message2);
    display();
}


/**
 * Méthode pour afficher une grandeur physique
 * @param char* message le libellé
 * @param valeur  la valeur à afficher
 * @param unite   l'unite de la grandeur
 */
void Afficheur::afficherFloat(String message, float valeur, String unite, int precision) {
    String valst(valeur,precision);
    clear();
    drawString(0,0, message );
    drawString(0,32, valst + unite);
    display();

}
