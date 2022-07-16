/* 
 * File:   Compteur.h
 * Author: philippe SIMIER
 *
 * Created on 16 juillet 2022, 09:50
 */

#ifndef COMPTEUR_H
#define COMPTEUR_H

#include <Arduino.h>

class Compteur {
    
public:
    Compteur(byte sensePin, int _debounce = 200);
    Compteur(const Compteur& orig);
    virtual ~Compteur();
    int getValue();
    void reset();

private:
    
    // void  IRAM_ATTR interuption();
    
    static IRAM_ATTR void isr();
    static Compteur* anchor;
           
    int lastMillis;
    int debounce;
    volatile int nb;
    
};


#endif /* COMPTEUR_H */

