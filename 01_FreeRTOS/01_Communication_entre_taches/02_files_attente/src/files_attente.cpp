/* 
 * File:   files_attente.cpp
 * Author: philippe SIMIER Lycée Touchard Washington Le Mans
 * 
 * Ici nous insérons  des éléments dans la file d'attente 
 * dans la fonction de boucle principale, 
 * 
 * les éléments sont retirés de la file par la tâche affichage
 * 
 * nous utilisons les fonctions 
 * xQueueCreate, xQueueSend, xQueueReceive
 *
 * Created on 21 juillet 2022, 18:26
 */

#include <Arduino.h>

QueueHandle_t file; // handle pour une file
void tache(void * parameter);

void setup() {
    Serial.begin(115200);

    // Création d'une file  pour 10 éléments des entiers
    file = xQueueCreate(10, sizeof ( int)); 
    if (file == NULL) {
        Serial.println("Erreur de création de file");
    }
    
    // Création de la tâche affichage
    xTaskCreate(
            tache,             // Task function 
            "Affichage",        // String with name of task
            10000,             // Stack size in words 
            NULL,        // Parameter passed as input of the task 
            1,                 // Priority of the task
            NULL);             // Task handle
        
}

void loop() {
        

    // insertion de 5 éléments dans la file
    for (int i = 0; i < 5; i++) {
        xQueueSend(file, &i, portMAX_DELAY); // insertion des 10 éléments dans la file
        
    }
    delay(1000);

}


/**
 * @brief Tâche pour retirer les éléments de la file et les afficher
 * @param parameter un pointeur généric (void *) 
 */
void tache(void * parameter) {
    
    char* nom =  pcTaskGetName(NULL); // Une tâche peut interroger son propre nom en transmettant son propre handle ou NULL
    int element;
    
    // Boucle principale
    while(1){
        xQueueReceive(file, &element, portMAX_DELAY);
        Serial.printf("Execution de  %s :" , nom);
        Serial.printf("Elément retiré  %d \r\n" , element);
        delay(1000);
    }
    
    
}

