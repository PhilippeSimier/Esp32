/* 
 * File:   main.cpp
 * Author: philippe SIMIER Touchard washington Le Mans
 *
 * Created on 14 juillet 2022, 08:59
 * 
 * Programme de démonstration pour régler un minuteur 
 * qui va générer périodiquement une interruption 
 * Exemple de fonction ISR (routine de service d’interruption).
 */

#include <Arduino.h>

volatile int interruption;
int totalInterruptCounter;
int LED = 2;

hw_timer_t * timer = NULL;

portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;


/**
 * La routine de service d’interruption doit être une fonction qui renvoie void 
 * et ne prend aucun argument.
 */
void IRAM_ATTR onTimer() {
    portENTER_CRITICAL_ISR(&timerMux);  // Début de section critique
    interruption = 1;
    portEXIT_CRITICAL_ISR(&timerMux);   // Fin de section critique
    digitalWrite(LED, digitalRead(LED) ^ 1);
}

void setup() {

    Serial.begin(115200);
    pinMode(LED, OUTPUT);
    interruption = 0;
    
    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &onTimer, true);
    timerAlarmWrite(timer, 1000000, true);   // 1s périodique
    timerAlarmEnable(timer);
}

void loop() {

    if (interruption) {

        portENTER_CRITICAL(&timerMux);
        interruption = 0;
        portEXIT_CRITICAL(&timerMux);

        totalInterruptCounter++;

        Serial.print("An interrupt as occurred. Total number: ");
        Serial.println(totalInterruptCounter);

    }
}


