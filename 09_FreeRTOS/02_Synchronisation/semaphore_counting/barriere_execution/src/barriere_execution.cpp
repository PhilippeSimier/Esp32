/* 
 * File:   barriere_execution.cpp
 * Author: philippe SIMIER Lycée Touchard Le Mans
 *
 * Created on 24 juillet 2022, 17:26
 */

#include <Arduino.h>

int nTasks = 4;
SemaphoreHandle_t barrierSemaphore = xSemaphoreCreateCounting(nTasks, 0);

void genericTask(void * parameter) {
    
    String taskMessage = "Tâche numéro : ";
    int nb;
    String give = " donne un semaphore";
    nb = (int) parameter;
    taskMessage = taskMessage + nb + give;
    Serial.println(taskMessage);
    xSemaphoreGive(barrierSemaphore); // Incrémente le sémaphore désigné par barrierSemaphore
    vTaskDelete(NULL);
}

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("Démarrage du lancement des tâches..");
    int i;

    for (i = 0; i < nTasks; i++) {
        xTaskCreatePinnedToCore(
                genericTask, /* Function to implement the task */
                "genericTask", /* Name of the task */
                10000, /* Stack size in words */
                (void *) i, /* Task input parameter */
                0, /* Priority of the task */
                NULL, /* Task handle. */
                1); /* Core where the task should run */
    }

    // Barrière attend que les 4 taches aient donné un sémaphore
    for (int j = 0; j < nTasks; j++) {
        xSemaphoreTake(barrierSemaphore, portMAX_DELAY); // Décrémente le sémaphore désigné par son descripteur
        Serial.println("un sémaphore est pris");
    }
    
    Serial.println("Tâches lancées et barrière des sémaphores passés...");
}

void loop() {
    vTaskSuspend(NULL);
}

