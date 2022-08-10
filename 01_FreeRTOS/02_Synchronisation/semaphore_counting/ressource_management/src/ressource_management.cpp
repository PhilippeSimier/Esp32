/* 
 * File:   ressource_management.cpp
 * Author: philippe SIMIER Lycée Touchard Washington le Mans
 *
 * Created on 24 juillet 2022, 8:16
 */

#include <Arduino.h>

SemaphoreHandle_t xCountingSemaphore;

void Task1(void *pvParameters);
void Task2(void *pvParameters);

const int LED = 2;

void setup() {
    
    Serial.begin(115200); // Enable serial communication library.
    pinMode(LED, OUTPUT);

    xCountingSemaphore = xSemaphoreCreateCounting(1, 1);
    xSemaphoreGive(xCountingSemaphore);
    
    // Create task for Arduino led 
    xTaskCreate(Task1, // Task function
            "Ledon", // Task name
            1024, // Stack size 
            NULL,
            0, // Priority
            NULL);
    
    xTaskCreate(Task2, // Task function
            "Ledoff", // Task name
            1024, // Stack size 
            NULL,
            0, // Priority
            NULL);
    
    

}

void loop() {
}

void Task1(void *pvParameters) {
    

    while (1) {
        
        xSemaphoreTake(xCountingSemaphore, portMAX_DELAY);
        
        Serial.println("Inside Task1 and Serial monitor Resource Taken");
        digitalWrite(LED, HIGH);
        vTaskDelay(1000);   // attend 1 seconde
        
        xSemaphoreGive(xCountingSemaphore);
        
        vTaskDelay(1);   // Donne la main aux autres taches 
    }
}

void Task2(void *pvParameters) {
    
    
    
    while (1) {
        
        xSemaphoreTake(xCountingSemaphore, portMAX_DELAY);
        
        Serial.println("Inside Task2 and Serial monitor Resource Taken");
        digitalWrite(LED, LOW);
        vTaskDelay(1000);   // attend 1 seconde
        
        xSemaphoreGive(xCountingSemaphore);

        vTaskDelay(1);  // Donne la main aux autres taches 
    }
}