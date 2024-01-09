/* 
 * File:   thermometre.h
 * Author: pcruchet
 *
 * Created on 30 novembre 2023, 08:22
 */

#ifndef THERMOMETRE_H
#define THERMOMETRE_H

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "esp32_snir.h"

void initialiserCapteurTemperature(void);
bool obtenirTemperature(int *_temperature, int * _dixiemes, const int _numCapteur=0);


#endif /* THERMOMETRE_H */

