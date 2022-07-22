/* 
 * File:   mutex_bme280.cpp
 * Author: philippe SIMIER 
 *
 * Created on 22 juillet 2022, 22:17
 */

#include <Arduino.h>
#include <Adafruit_BME280.h>

typedef struct {
    float t;
    float h;
    float p;
} Mesure_t;

Mesure_t mesure;
SemaphoreHandle_t xMutex;   

// Déclaration des prototypes
void sensorTask(void * pvParameters);


void setup() {
    
    Serial.begin(115200);
    while (!Serial);
  
    // creation d'un Mutex 
    xMutex = xSemaphoreCreateMutex();
    
    // Création de la  tâche mesure
    xTaskCreatePinnedToCore(
            sensorTask,   // Function pour implémenter la tâche 
            "sensorTask", // le Nom de la tâche 
            10000,        // la taille de la pile en mots
            NULL,         // paramètre d'entrée
            1,            // Priorité de la tâche
            NULL,         // Tâche handle
            1             // Core where the task should run
            );  
    
}

void loop() {
   
    xSemaphoreTake(xMutex, portMAX_DELAY);  // début de la section critique
    
    Serial.printf("Temp : %.1f°C", mesure.t );
    Serial.printf(" Hum  : %.1f%%",  mesure.h );
    Serial.printf(" Pression : %.1fhPa\r\n", mesure.p );
 
    xSemaphoreGive(xMutex);  // Fin de la section critique
    
    delay(5000);
}


/**
 * Tache initialisation & lectur du capteur BME280
 * @param pvParameters
 */
void sensorTask(void * pvParameters) {
    
    
    Adafruit_BME280 bme;
    
    // Setup
    Serial.println("BME280 test");
    if (!bme.begin(0x76)) {
        Serial.println("Ne peut pas trouver le capteur BME280!");
        while (1);
    }
     
    // Boucle
    while (1) {
        
        xSemaphoreTake(xMutex, portMAX_DELAY);  // Début de la section critique
        
        mesure.t = bme.readTemperature();
        mesure.h = bme.readHumidity();
        mesure.p = bme.readPressure() / 100.0F;

        xSemaphoreGive(xMutex);  // Fin de la section critique
        delay(2500);
    }
}





