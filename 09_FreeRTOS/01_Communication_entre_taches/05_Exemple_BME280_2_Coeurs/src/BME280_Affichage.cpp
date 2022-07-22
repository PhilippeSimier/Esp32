/* 
 * File:   BME280_Affichage.cpp
 * Author: philippe SIMIER Touchard Washington
 *
 * Created on 22 juillet 2022, 10:21
 * 
 * j'ai utilisé la commande suivante pour installer la biblio
 * pio pkg install --library "adafruit/Adafruit BME280 Library@^2.2.2"
 * 
 */

#include <Wire.h>
#include <Adafruit_BME280.h>

typedef struct {
    float t;
    float h;
    float p;
} Mesure_t;

QueueHandle_t queue;

// Déclaration des prototypes
void sensorTask(void * pvParameters);
void blinkTask(void * pvParameters);


void setup() {
    
    Serial.begin(115200);
    while (!Serial);
    
    int queueSize = 10;
    queue = xQueueCreate(queueSize, sizeof ( Mesure_t));

    // Création des tâches
    xTaskCreatePinnedToCore(
            sensorTask,   // Function pour implémenter la tâche 
            "sensorTask", // le Nom de la tâche 
            10000,        // la taille de la pile en mots
            NULL,         // paramètre d'entrée
            1,            // Priorité de la tâche
            NULL,         // Tâche handle
            1             // Core where the task should run
            );
    
    xTaskCreatePinnedToCore(
            blinkTask,    // la fonction associée 
            "blinkTask",  // le nom de la tâche 
            10000,        // la taille de la pile 
            NULL,         // parameter of the task 
            1,            // priorité de la tâche
            NULL,         // Task handle to keep track of created task
            1);           // Core where the task should run
}

void loop() {
    Mesure_t mesureReceive;

    xQueueReceive(queue, &mesureReceive, portMAX_DELAY);

    Serial.printf("Temp : %.1f°C", mesureReceive.t );
    Serial.printf(" Hum  : %.1f%%",  mesureReceive.h );
    Serial.printf(" Pression : %.1fhPa\r\n", mesureReceive.p );
 
    delay(5);

}


/**
 * Tache initialisation & lecteur du capteur BME280
 * @param pvParameters
 */
void sensorTask(void * pvParameters) {
    
    Mesure_t mesureSend;
    Adafruit_BME280 bme;
    
    // Setup
    Serial.println("BME280 test");
    if (!bme.begin(0x76)) {
        Serial.println("Ne peut pas trouver le capteur BME280!");
        while (1);
    }
    TickType_t xLastWakeTime = xTaskGetTickCount();   // Initialise the xLastWakeTime variable with the current time.
    

    // Boucle
    while (1) {
        mesureSend.t = bme.readTemperature();
        mesureSend.h = bme.readHumidity();
        mesureSend.p = bme.readPressure() / 100.0F;

        xQueueSend(queue, &mesureSend, portMAX_DELAY);
        xTaskDelayUntil( &xLastWakeTime, pdMS_TO_TICKS( 1000 ) ); // toutes les 1000 ms
    }
}

// Tache blinking led 

void blinkTask(void * pvParameters) {

    pinMode(2, OUTPUT);

    while (1) {
        digitalWrite(2, digitalRead(2) ^ 1);
        delay(1000);
    }
}