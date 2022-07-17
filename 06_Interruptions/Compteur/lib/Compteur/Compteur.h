/* 
 * File:   Compteur.h
 * Author: philippe SIMIER
 *
 * Created on 16 juillet 2022, 09:50
 */

#ifndef COMPTEUR_H
#define COMPTEUR_H

#include <Arduino.h>
#include <esp32-hal-gpio.h>

class Compteur {
    
public:
    Compteur(uint8_t sensePin, int _debounce = 200);
    Compteur(const Compteur& orig);
    virtual ~Compteur();
    int getValue(void);
    void reset(void);

private:
            
    static IRAM_ATTR void isr(void * arg);
               
    int lastMillis;
    int debounce;
    volatile int nb;
    
};


#endif /* COMPTEUR_H */

