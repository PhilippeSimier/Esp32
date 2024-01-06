/* 
 * File:   biblio.h
 * Author: philippe
 *
 * Created on 27 novembre 2021, 08:08
 */

#ifndef BIBLIO_H
#define BIBLIO_H


#define CONNECTEUR_BAS   // Définit la position du connecteur clavier en haut ou bas

#define LED 2 // définition de la LED bleue sur le board ESP32
#define D1 13 // définition de la LED rouge
#define D2 12 // définition de la LED verte
#define BP1 39 // définition des boutons-poussoirs
#define BP2 34
#define BP3 35 

#include <Arduino.h>
#include <SPIFFS.h>
#include <Keypad.h>
#include <Led.h>                // Les quatre Leds RGB
#include <Afficheur.h>

void createTaskBlink(void);
static void tacheBlink(void * parameter);

void createTaskBridge(void);
static void tacheBridge(void * parameter);

void envoyerFichier(String fichier, Stream &flux);

void createTaskClavier(void);
static void taskClavier(void *pvParameters);

void createTaskLed1Led2(void);
static void taskLed1Led2(void *pvParameters);

void chenillard(const word nb = 4);


#endif /* BIBLIO_H */

