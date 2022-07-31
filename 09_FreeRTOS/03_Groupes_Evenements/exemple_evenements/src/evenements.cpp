/*
 * File:   evenements.cpp
 * Author: philippe
 *
 * Created on 31 juillet 2022, 20:15
 */

#include <Arduino.h>
#include "freertos/event_groups.h"

// define event bits
#define TASK_1_BIT ( 1 << 0 ) //1
#define TASK_2_BIT ( 1 << 1 ) //10
#define TASK_3_BIT ( 1 << 2 ) //100
#define ALL_SYNC_BITS (TASK_1_BIT | TASK_2_BIT | TASK_3_BIT) //111

hw_timer_t * timer = NULL; // déclaration d'un hardware timer
EventGroupHandle_t eg; // déclaration d'un event group
SemaphoreHandle_t xMutex; // déclaration d'un mutex pour protéger Serial
int count = 0;

void task1(void * parameter);
void task2(void * parameter);
void task3(void * parameter);

// timer ISR callback

void IRAM_ATTR onTimer() {
    BaseType_t xHigherPriorityTaskWoken;
    count++;
    switch (count) {
        case 2: // set event bit of task1
            xEventGroupSetBitsFromISR(eg, TASK_1_BIT, &xHigherPriorityTaskWoken);
            break;

        case 3: // set event bit of task 2 and 3
            xEventGroupSetBitsFromISR(eg, TASK_2_BIT | TASK_3_BIT, &xHigherPriorityTaskWoken);
            break;

        case 4: // reset counter to start again
            count = 0;
            break;

        default:
            break;
    }
}

void setup() {

    Serial.begin(115200);

    eg = xEventGroupCreate(); // création du groupe
    xMutex = xSemaphoreCreateMutex();

    timer = timerBegin(0, 80, true); // 1 tick takes 1/(80MHZ/80) → 1 microsecond
    timerAttachInterrupt(timer, &onTimer, true); // attach onTimer function to our timer
    timerAlarmWrite(timer, 1000000, true); // call onTimer function every second 1000000 ticks  true – repeat the alarm
    timerAlarmEnable(timer); // start timer alarm
    Serial.println("start timer");

    xTaskCreate(task1, "task1", 10000, NULL, 1, NULL);
    xTaskCreate(task2, "task2", 10000, NULL, 1, NULL);
    xTaskCreate(task3, "task3", 10000, NULL, 1, NULL);


}

void loop() {
}

void task1(void * parameter) {

    while (1) {
        EventBits_t xbit = xEventGroupWaitBits(eg, TASK_1_BIT, pdTRUE, pdTRUE, portMAX_DELAY);
        
        xSemaphoreTake(xMutex, portMAX_DELAY);
        Serial.print("Tache 1 a reçu son bit d'evenement: ");
        Serial.println(xbit);
        xSemaphoreGive(xMutex);
        
    }
    vTaskDelete(NULL);
}

void task2(void * parameter) {

    while (1) {
        // attend à l'état bloqué le bit d'evenement TASK_2_BIT
        EventBits_t xbit = xEventGroupWaitBits(eg, TASK_2_BIT, pdTRUE, pdTRUE, portMAX_DELAY);
        
        xSemaphoreTake(xMutex, portMAX_DELAY);
        Serial.print("Tache 2 a reçu son bit d'evenement: ");
        Serial.println(xbit);
        xSemaphoreGive(xMutex);
    }
    vTaskDelete(NULL);
}

void task3(void * parameter) {

    while (1) {
        EventBits_t xbit = xEventGroupWaitBits(eg, TASK_3_BIT, pdTRUE, pdTRUE, portMAX_DELAY);
        
        xSemaphoreTake(xMutex, portMAX_DELAY);
        Serial.print("Tache 3 a reçu son bit d'evenement: ");
        Serial.println(xbit);
        xSemaphoreGive(xMutex);
    }
    vTaskDelete(NULL);
}

