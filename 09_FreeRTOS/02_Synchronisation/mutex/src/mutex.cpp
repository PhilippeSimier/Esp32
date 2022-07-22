/* 
 * File:   mutex.cpp
 * Author: philippe SIMIER Touchard Le Mans
 *
 * Created on 22 juillet 2022, 19:14
 */

#include<Arduino.h>

SemaphoreHandle_t xMutex;

// Les prototypes des tâches
void lowPriorityTask(void * parameter);
void highPriorityTask(void * parameter);


void setup() {
    Serial.begin(115200);

    /* creation d'un Mutex */
    xMutex = xSemaphoreCreateMutex();

    xTaskCreate(
            lowPriorityTask, /* Task function. */
            "lowPriorityTask", /* name of task. */
            1000, /* Stack size of task */
            NULL, /* parameter of the task */
            1, /* priority of the task */
            NULL); /* Task handle to keep track of created task */

    delay(500);
    /* let lowPriorityTask run first then create highPriorityTask */

    xTaskCreate(
            highPriorityTask, /* Task function. */
            "highPriorityTask", /* name of task. */
            1000, /* Stack size of task */
            NULL, /* parameter of the task */
            4, /* priority of the task */
            NULL); /* Task handle to keep track of created task */
}

void loop() {
}


/* Tâche de basse priorité */
void lowPriorityTask(void * parameter) {
    
    
    for (;;) {

        
        Serial.println("\r\nlowPriorityTask  attend la clé");
        
        /* Voyez si nous pouvons obtenir le sémaphore. */
        xSemaphoreTake(xMutex, portMAX_DELAY);
        /* Nous avons pu obtenir le sémaphore et 
         *  pouvons maintenant accéder à la ressource partagée. */
        Serial.println("lowPriorityTask a gagné la clé");
        Serial.println("lowPriorityTask is running");
        delay(2000);
        /* Nous avons fini d'accéder à la ressource partagée. 
         * nous relâchons le sémaphore. */
        Serial.println("lowPriorityTask  rend la clé");
        xSemaphoreGive(xMutex);
    }
    
    
}

/* Tâche de haute priorité */
void highPriorityTask(void * parameter) {
    
    
    for (;;) {
        Serial.println("highPriorityTask  attend la clé");
        
        xSemaphoreTake(xMutex, portMAX_DELAY);
        Serial.println("highPriorityTask a gagné la clé");
        Serial.println("highPriorityTask is running");
        Serial.println("highPriorityTask rend la clé");
        xSemaphoreGive(xMutex);
        /* attente de 1 seconde afin que lowPriorityTask ait une chance de s'exécuter */
        delay(1000);
    }
    
}


