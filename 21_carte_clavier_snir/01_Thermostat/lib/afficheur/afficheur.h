/* 
 * File:   afficheur.h
 * Author: pcruchet
 *
 * Created on 29 novembre 2023, 13:21
 */

#ifndef AFFICHEUR_H
#define AFFICHEUR_H

#include <Arduino.h>
#include <SSD1306.h>
#include <string.h>
#include "DejaVu_Sans_Mono_32.h"

void initialiserAfficheur(void);
void afficherTemperature(const int _temperature, const int _dixiemes);

#endif /* AFFICHEUR_H */

