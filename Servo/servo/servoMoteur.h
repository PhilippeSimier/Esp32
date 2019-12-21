/**
  * @author simier philippe
  * @date   Samedi 21/12/2019
  * @file   servoMoteur.h
  */

#ifndef SERVOMOTEUR_H
#define SERVOMOTEUR_H

#include <Arduino.h>
#include "esp32-hal-ledc.h"

class ServoMoteur
{
public:
    ServoMoteur();
    void Positionner(int pos);
    void Attacher(int _gpio);
    void Detacher();
    

private:
    int channel;
    int gpio;
    int pos;
    int resolution;
    int freq;   
};

#endif // SERVOMOTEUR_H
