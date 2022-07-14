/* 
 * File:   main.cpp
 * Author: philippe
 *
 * Created on 14 juillet 2022, 08:59
 * 
 * nous allons vérifier comment régler un minuteur 
 * pour générer périodiquement une interruption 
 * Comment gérer l'interruption dans une fonction ISR (routine de service d’interruption).
 */

#include <Arduino.h>
#include <freertos/portmacro.h>


volatile int interruptCounter;
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
    interruptCounter++;
    portEXIT_CRITICAL_ISR(&timerMux);   // Fin de section critique
    digitalWrite(LED, digitalRead(LED) ^ 1);
}

void setup() {

    Serial.begin(115200);
    pinMode(LED, OUTPUT);
    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &onTimer, true);
    timerAlarmWrite(timer, 1000000, true);
    timerAlarmEnable(timer);
}

void loop() {

    if (interruptCounter > 0) {

        portENTER_CRITICAL(&timerMux);
        interruptCounter--;
        portEXIT_CRITICAL(&timerMux);

        totalInterruptCounter++;

        Serial.print("An interrupt as occurred. Total number: ");
        Serial.println(totalInterruptCounter);

    }
}


