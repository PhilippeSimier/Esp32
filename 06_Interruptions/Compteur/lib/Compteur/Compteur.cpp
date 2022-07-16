/* 
 * File:   Compteur.cpp
 * Author: philippe
 * 
 * Attention cette classe ne peut être instanciée qu'une seule fois
 * 
 * Created on 16 juillet 2022, 09:50
 */

#include "Compteur.h"

Compteur::Compteur(byte sensePin, int _debounce) :
lastMillis(0),
debounce(_debounce),        
nb(0)       
{
    anchor = this;
    pinMode(sensePin, INPUT_PULLUP);  
    attachInterrupt(sensePin, Compteur::isr, FALLING);
}

Compteur::Compteur(const Compteur& orig) {
}

Compteur::~Compteur() {
}

void Compteur::reset() {
    nb = 0;
}

void IRAM_ATTR Compteur::isr() {
    if (millis() - anchor->lastMillis > anchor->debounce) { //Software anti-rebond

        ets_printf("triggered\r\n");
        anchor->nb++;
    }
    anchor->lastMillis = millis();
}



int Compteur::getValue() {
    return this->nb;
}

Compteur* Compteur::anchor = NULL;


