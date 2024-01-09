/* 
 * File:   Led.cpp
 * Author: philippe Simier Touchard Washington
 * 
 * Created on 14 février 2022, 15:40
 */

#include "Led.h"

// Constructeur de Led

Led::Led(word _numPixels) :
NeoPixelBus<NeoRgbFeature, Neo800KbpsMethod>(_numPixels, DATALEDS),
numPixels(_numPixels),
nb_ms(100) {
    Begin();
    Show(); // cela réinitialise tous les leds couleurs à un état désactivé
}

Led::~Led() {
}

/**
 * @brief Allume la led avec la couleur demandée
 * @param couleur RgbColor une couleur 
 */

void Led::allumer(const RgbColor &couleur, const word id) {
    if (id < numPixels) {
        SetPixelColor(id, couleur);
        Show();
    }
}

/**
 * Eteint la led
 */
void Led::eteindre(const word id) {
    if (id < numPixels) {
        SetPixelColor(id, RgbColor(0, 0, 0));
        Show();
    }
}

/**
 * @brief Allume les leds du ruban une par une jusqu'à nb
 * @param couleur
 * @param nb
 */
void Led::cheniller(const RgbColor &couleur, word nb) {

    if (nb > numPixels)
        nb = numPixels;
    for (int i = 0; i < nb; i++) {
        allumer(couleur, i);
        delay(nb_ms);
    }
}

/**
 * @brief allume les led du ruban une par une 
 *        à partir de l'extrémité
 * @param couleur
 * @param nb
 */
void Led::chenillerInverse(const RgbColor &couleur, word nb) {

    if (nb > numPixels)
        nb = numPixels;
    for (int i = nb - 1; i > 0; i--) {
        allumer(couleur, i);
        delay(nb_ms);
    }
    eteindre(0);
}

void Led::setDelay(const int nb){
    nb_ms = nb;
}


