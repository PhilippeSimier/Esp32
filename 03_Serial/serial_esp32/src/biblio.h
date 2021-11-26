/* 
 * File:   biblio.h
 * Author: psimier
 *
 * Created on 25 novembre 2021, 09:42
 */

#ifndef BIBLIO_H
#define BIBLIO_H

#include <Arduino.h>
#include <SPIFFS.h>
#define LED 2

void tacheBlink(void * parameter);

void envoyerFichier(String fichier);



#endif /* BIBLIO_H */

