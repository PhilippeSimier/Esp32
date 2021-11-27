/* 
 * File:   biblio.h
 * Author: philippe
 *
 * Created on 27 novembre 2021, 08:08
 */

#ifndef BIBLIO_H
#define BIBLIO_H

#include <Arduino.h>
#include <SPIFFS.h>
#define LED 2

void tacheBlink(void * parameter);

void envoyerFichier(String fichier);


#endif /* BIBLIO_H */

