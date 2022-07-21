/* 
 * File:   tache_parametre.cpp
 * Author: philippe SIMIER Lycée Touchard Washington le Mans
 *
 * programme exemple 
 * passage de paramètre à une tache par son adresse
 * chaque tâche lorsqu'elle est terminée va écrire une nouvelle valeur dans sa variable parameter
 * la communication avec la tâche principale est bidirectionnelle.
 * 
 * Created on 21 juillet 2022, 17:18
 */

#include <Arduino.h>

void tache(void * parameter);
char * name;
int  param1 = 10;
int  param2 = 20;

void setup() {
    
    Serial.begin(115200);
    delay(1000);
    
    int app_cpu = xPortGetCoreID(); // Which CPU?
    Serial.printf("setup CPU %d \n\r", app_cpu);
    
    TaskHandle_t h = xTaskGetCurrentTaskHandle();
    name =  pcTaskGetName(h);    // Une tâche peut interroger son propre nom en transmettant son propre handle ou NULL
    
    xTaskCreate(
            tache,             // Task function 
            "Tache 1",         // String with name of task
            10000,             // Stack size in words 
            static_cast<void *>(&param1),   // Address of parameter passed as input of the task 
            1,                 // Priority of the task
            NULL);             // Task handle

    
    xTaskCreate(
            tache,             // Task function
            "Tache 2",         // String with name of task
            10000,             // Stack size in words
            static_cast<void *>(&param2),   // Address of parameter passed as input of the task
            2,                 // Priority of the task 2 
            NULL);             // Task handle
}

void loop() {
    Serial.printf("Execution de %s ", name);
    Serial.printf("param1 %d param2 %d\n\r", param1, param2);
    delay(1000);
}

/**
 * @brief la fonction qui sera instanciée sous forme de tâche
 * @param parameter un pointeur généric (void *) contient l'adresse d'un variable de type int
 */
void tache(void * parameter) {
    
    int id = *(static_cast<int *>(parameter));     // Récupère l'argument de la tâche le nombre de tour dans la boucle
    char* nom =  pcTaskGetName(NULL); // Une tâche peut interroger son propre nom en transmettant son propre handle ou NULL
    
    for (int i = 0; i < id; i++) {
        Serial.printf("Execution de  %s " , nom);
        Serial.printf("i = %d\n\r", i);
        delay(1000);
    }
    Serial.printf("Fin de  %s\n\r" , nom);
    id++ ;
    *(static_cast<int *>(parameter)) = id;  // écriture du parametre car nous connaissons son adresse
    vTaskDelete(NULL);        // Une tâche peut s'auto détruire 
}

