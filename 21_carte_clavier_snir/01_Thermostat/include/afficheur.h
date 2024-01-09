/* 
 * File:   afiicheur.h
 * Author: pcruchet
 *
 * Created on 29 novembre 2023, 13:21
 */

#ifndef AFFICHEUR_H
#define AFFICHEUR_H

#include <Arduino.h>
#include <SSD1306.h>
#include <string.h>
#include "fonts.h"

void InitialiserAfficheur(void);
void AfficherTemperature(const int _temperature, const int _dixiemes);

#endif /* AFFICHEUR_H */

