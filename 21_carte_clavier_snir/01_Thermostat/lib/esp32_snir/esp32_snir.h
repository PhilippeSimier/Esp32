/* 
 * File:   esp32_snir.h
 * Author: pcruchet
 *
 * Created on 29 novembre 2023, 13:56
 */

#ifndef ESP32_SNIR_H
#define ESP32_SNIR_H

#define BP1 39 // définition des boutons-poussoirs
#define BP2 34
#define BP3 35 
#define SW 23  // définition de l’interrupteur

#define LED 2 // définition de la LED bleue sur le board ESP32
#define D1 13 // définition de la LED rouge
#define D2 12 // définition de la LED verte

#define ADD_OLED 0x3C // adresse de l’afficheur OLED sur le bus I2C

#define DATALEDS 19 // définition du GPIO pour la commande des LED RGB
#define NB_PIXELS 4 // nombre de pixels sur la carte.       

#define ADC_LDR 36 // définition du GPIO pour la conversion analogique numérique

#define RELAY_1 27 // définition du GPIO pour le relais 1
#define RELAY_2 14 // définition du GPIO pour le relais 2

#define TX_RS232 17  // définition de la broche de transmission pour la RS232
#define RX_RS232 16  // définition de la broche de réception pour la RS232

#define TEMP 18 // définition du bus 1-wire pour le capteur de température

#define PWM 2 // définition du GPIO pour le servomoteur

#endif /* ESP32_SNIR_H */

