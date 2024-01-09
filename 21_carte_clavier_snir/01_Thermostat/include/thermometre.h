/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

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

void InitialiserCapteurTemperature(void);
bool ObtenirTemperature(int *_temperature, int * _dixiemes, const int _numCapteur=0);


#endif /* THERMOMETRE_H */

