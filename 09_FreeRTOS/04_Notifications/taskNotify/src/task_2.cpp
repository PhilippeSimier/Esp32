#include <Arduino.h>

#include "task_manager.h"

extern TaskHandle_t loopTaskHandle;

void setup2(void) {

    enableLoop2WDT();
    Serial.println("Setup 2");
}

void loop2(void) {

    uint32_t receivedValue;

    if (xTaskNotifyWait(0, ULONG_MAX, &receivedValue, 1000) == pdPASS) {
        Serial.printf("Notification pour Tache 2 : Valeur reçue = %d\r\n", receivedValue);
        
        receivedValue = receivedValue * 2;   // Renvoie à la tache principale une notification avec le double de la valeur reçue
        xTaskNotify(loopTaskHandle, receivedValue , eSetValueWithOverwrite);   
    }
}

