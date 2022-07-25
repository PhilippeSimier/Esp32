/* 
 * File:   mutex_bme280.cpp
 * Author: philippe SIMIER 
 *
 * Exemple de programme montrant l'utilisation d'un MUTEX
 * pour proteger une section partagée (la variable mesure)
 * Created on 22 juillet 2022, 22:17
 */

#include <Arduino.h>
#include <Adafruit_BME280.h>
#include <TM1637TinyDisplay6.h>       // Include 6-Digit Display Class Header

typedef struct {
    float t;
    float h;
    float p;
} Mesure_t;

Mesure_t mesure;
SemaphoreHandle_t xMutex;

// Déclaration des prototypes
void sensorTask(void * pvParameters);
void displayTask(void * pvParameters);
void infos();

void setup() {

    Serial.begin(115200);
    while (!Serial);
    infos();
    
    // creation d'un Mutex 
    xMutex = xSemaphoreCreateMutex();

    // Création de la  tâche mesure
    xTaskCreatePinnedToCore(
            sensorTask, // Function pour implémenter la tâche 
            "sensorTask", // le Nom de la tâche 
            10000, // la taille de la pile en mots
            NULL, // paramètre d'entrée
            1, // Priorité de la tâche
            NULL, // Tâche handle
            1 // Core where the task should run
            );

    // Création de la  tâche affichage
    xTaskCreatePinnedToCore(
            displayTask, // Function pour implémenter la tâche 
            "displayTask", // le Nom de la tâche 
            10000, // la taille de la pile en mots
            NULL, // paramètre d'entrée
            1, // Priorité de la tâche
            NULL, // Tâche handle
            1 // Core where the task should run
            );

}

void loop() {



    xSemaphoreTake(xMutex, portMAX_DELAY); // début de la section critique


    Serial.printf("Temp : %.1f°C", mesure.t);
    Serial.printf(" Hum  : %.1f%%", mesure.h);
    Serial.printf(" Pression : %.1fhPa\r\n", mesure.p);

    xSemaphoreGive(xMutex); // Fin de la section critique

    vTaskDelay(pdMS_TO_TICKS(5000)); // passage à l'état bloquée pour 5000 ms (converti en tick)
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

        xSemaphoreTake(xMutex, portMAX_DELAY); // Début de la section critique

        mesure.t = bme.readTemperature();
        mesure.h = bme.readHumidity();
        mesure.p = bme.readPressure() / 100.0F;

        xSemaphoreGive(xMutex); // Fin de la section critique

        vTaskDelay(pdMS_TO_TICKS(2500));
    }
}

/**
 * 
 * @param pvParameters
 */
void displayTask(void * pvParameters) {

    TM1637TinyDisplay6 display(14, 27); // 6-Digit Display Class (CLK = 14 DIO = 27)
    display.setBrightness(BRIGHT_HIGH);
    display.clear();
    float temperature, humidite, pression;

    while (1) {
        xSemaphoreTake(xMutex, portMAX_DELAY); // Début de la section critique
        temperature = mesure.t;
        humidite = mesure.h;
        pression = mesure.p;
        xSemaphoreGive(xMutex); // Fin de la section critique

        display.showNumber(temperature,2);
        vTaskDelay(pdMS_TO_TICKS(2000));
        display.showNumber(humidite,2);
        vTaskDelay(pdMS_TO_TICKS(2000));
        display.showNumber(pression,1);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void infos() {
    esp_chip_info_t out_info;
    esp_chip_info(&out_info);
    
    Serial.print("CPU freq : ");
    Serial.println(String(ESP.getCpuFreqMHz()) + " MHz");
    
    Serial.print("CPU cores : ");
    Serial.println(String(out_info.cores));
    
    Serial.print("Flash size : ");
    Serial.println(String(ESP.getFlashChipSize() / 1000000) + " MB");
    
    Serial.print("Free RAM : ");
    Serial.println(String((long) ESP.getFreeHeap()) + " bytes");
    
    Serial.print("Min. free seen : "); 
    Serial.println(String((long)esp_get_minimum_free_heap_size()) + " bytes");
    
    Serial.print("tsk IDLE_PRIORITY : ");
    Serial.println(String((long) tskIDLE_PRIORITY));
    
    Serial.print("config MAX_PRIORITIES : ");
    Serial.println(String((long) configMAX_PRIORITIES));
    
    Serial.print("config TICK_RATE_HZ : ");
    Serial.println(String(configTICK_RATE_HZ) + " Hz");
    
    Serial.println();
}





