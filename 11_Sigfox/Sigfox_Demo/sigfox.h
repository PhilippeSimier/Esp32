/**
  * @file sigfox.h
  * @author Philippe SIMIER
  * @date 26 janvier 2020
  * @details Assure la communication avec le réseau Sigfox avec les commandes AT
  * 
  */



#ifndef __SIGFOX__
#define __SIGFOX__


#include "Arduino.h"
#include <HardwareSerial.h>

class Sigfox
{
  public:

    Sigfox(uint8_t rxPin, uint8_t txPin, bool debugEn);

    String tester(void);
    void begin(void);
    
    String   obtenirID(void);
    String   obtenirPAC(void);
    uint16_t obtenirTemp(void);

    bool envoyer(const void* data, uint8_t size);

  private:
    uint8_t rx, tx;
    HardwareSerial *serialSig;
    bool debug;
    String obtenirData(void);

};

#endif
