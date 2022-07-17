/* 
 * File:   Compteur.cpp
 * Author: philippe
 * 
 * Attention cette classe ne peut être instanciée qu'une seule fois
 * 
 * Created on 16 juillet 2022, 09:50
 */

#include "Compteur.h"

Compteur::Compteur(uint8_t sensePin, int _debounce) :
lastMillis(0),
debounce(_debounce),        
nb(0)       
{
    
    pinMode(sensePin, INPUT_PULLUP);  
    attachInterruptArg(sensePin, Compteur::isr, this, FALLING);
}

Compteur::Compteur(const Compteur& orig) {
}

Compteur::~Compteur() {
}

void Compteur::reset(void) {
    nb = 0;
}

void IRAM_ATTR Compteur::isr(void * arg) {
    Compteur* pt = static_cast<Compteur*>(arg);  // cast le pointeur générique en pointeur sur Compteur
    if (millis() - pt->lastMillis > pt->debounce) { //Software anti-rebond

        ets_printf("triggered\r\n");
        pt->nb++;
    }
    pt->lastMillis = millis();
}



int Compteur::getValue(void) {
    return this->nb;
}



