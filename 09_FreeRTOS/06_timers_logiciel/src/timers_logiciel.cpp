/* 
 * File:   timers_logiciel.cpp
 * Author: philippe SIMIER Lycée Touchard Le Mans
 *
 * Programme de démonstration pour l'utilisation des timers logiciel
 * Created on 2 août 2022, 17:34
 */

#include <Arduino.h>
#define LED 2

TimerHandle_t timerPeriodique, oneShotTimer;

// Les prototypes des fonctions callbacks

void oneShotTimerCallback(TimerHandle_t xTimer);
void autoReloadTimerCallback(TimerHandle_t xTimer);

void setup() {

    pinMode(LED, OUTPUT);
    Serial.begin(115200);
    while (!Serial);
    Serial.println("Start");

    // Création du timer OneShot
    oneShotTimer = xTimerCreate(
            "OneShot", // le nom du timer - not used by FreeRTOS. 
            pdMS_TO_TICKS(3000), // le temps d'attente en ticks. 3000 -> 3 secondes 
            pdFALSE, // uxAutoRealod to pdFALSE creates a one-shot software timer. 
            (void*) 1, // ID de minuterie  (NULL = not use). 
            oneShotTimerCallback // la fonction de callback associée au timer 
            );
    if (oneShotTimer == NULL) {
        for (;;); /* échec! */
    }

    // Création du timer périodique 1 seconde
    timerPeriodique = xTimerCreate(
            "AutoReload",
            pdMS_TO_TICKS(1000),
            pdTRUE,
            (void*) 2,
            autoReloadTimerCallback);
    if (timerPeriodique == NULL) {
        for (;;); /* échec! */
    }

    // Démarrage des deux timers
    xTimerStart(oneShotTimer, 0);
    xTimerStart(timerPeriodique, 0);

}

void loop() {
}

void oneShotTimerCallback(TimerHandle_t xTimer) {

    TickType_t xTimeNow = xTaskGetTickCount();

    Serial.printf("oneShotTimerCallback - %d\r\n", xTimeNow);
}

void autoReloadTimerCallback(TimerHandle_t xTimer) {

    TickType_t xTimeNow = xTaskGetTickCount();
    digitalWrite(LED, digitalRead(LED) ^1); // turn the LED 
    Serial.printf("autoReloadTimerCallback - %d\r\n", xTimeNow);
}

