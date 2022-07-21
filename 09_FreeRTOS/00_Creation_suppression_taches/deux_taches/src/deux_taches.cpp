/*
 * File:   deux_taches.cpp
 * Author: Philippe SIMIER 
 *         Lycée Touchard Washington Le Mans
 * 
 *  
 *  Exemple de création de 2 tâches totalement indépendantes utilisant une même fonction nommée tache :
 * 
 *  Created on 20 juillet 2022, 15:42
 */



#include <Arduino.h>

void tache(void * parameter);
char * name;
int  param = 20;


void setup() {
    
    Serial.begin(115200);
    delay(1000);
    
    int app_cpu = xPortGetCoreID(); // Which CPU?
    Serial.printf("setup CPU %d \n\r", app_cpu);
    
    TaskHandle_t h = xTaskGetCurrentTaskHandle();
    name =  pcTaskGetName(h);    // Une tâche peut interroger son propre nom en transmettant son propre handle ou NULL
    
    xTaskCreate(
            tache,             // Task function 
            "TacheUne",        // String with name of task
            10000,             // Stack size in words 
            (void *)10,        // Parameter passed as input of the task 
            1,                 // Priority of the task
            NULL);             // Task handle

    
    xTaskCreate(
            tache,             // Task function
            "TacheDeux",       // String with name of task
            10000,             // Stack size in words
            (void *)param,     // Parameter passed as input of the task
            1,                 // Priority of the task
            NULL);             // Task handle
}

void loop() {
    Serial.printf("Execution de %s \n\r", name);
    delay(1000);
}

/**
 * @brief la fonction qui sera instanciée sous forme de tâche
 * @param parameter un pointeur généric (void *) 
 */
void tache(void * parameter) {
    
    int id = (int)parameter;          // Récupère l'argument de la tâche le nombre de tour dans la boucle
    char* nom =  pcTaskGetName(NULL); // Une tâche peut interroger son propre nom en transmettant son propre handle ou NULL
    
    for (int i = 0; i < id; i++) {
        Serial.printf("Execution de  %s\n\r" , nom);
        Serial.printf("i = %d\n\r", i);
        delay(1000);
    }
    Serial.printf("Fin de  %s\n\r" , nom);
    vTaskDelete(NULL);              // Une tâche peut s'auto détruire 
}


