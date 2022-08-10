/* 
 * File:   taskNotify.cpp
 * Author: philippe  SIMIER Lycée Touchard Le Mans
 *
 * Created on 1 août 2022, 09:14
 */

#include <Arduino.h>
#include <esp_task_wdt.h>

#include "task_manager.h"

extern TaskHandle_t loop2TaskHandle;

void setup() {

    esp_task_wdt_init(60, true); // time in seconds
    enableLoopWDT();

    Serial.begin(115200);
    delay(100);


    Serial.println("Setup 1");
    createTask2();
}

void loop() {
    
    static uint32_t valueToSend = 0;
    uint32_t receivedValue;

    if (xTaskNotify(loop2TaskHandle, valueToSend, eSetValueWithoutOverwrite) == pdTRUE) 
    {
        valueToSend++;
        
        if (xTaskNotifyWait(0, ULONG_MAX, &receivedValue, 1000) == pdFAIL) {
            Serial.println("error, task2 do not response");
        }
        Serial.printf("Notification pour Tache principale : Valeur reçue = %d\r\n", receivedValue);
    }
    delay(2000);
}

