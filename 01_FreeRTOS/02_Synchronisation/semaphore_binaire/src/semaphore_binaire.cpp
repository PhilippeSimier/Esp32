/* 
 * File:   semaphore_binaire.cpp
 * Author: philippe SIMIER Lycée Touchard Washington le Mans
 *
 * Created on 23 juillet 2022, 18:16
 */

#include <Arduino.h>

byte ledPin = 2; // LED
byte interruptPin = 13; // button BP D13

volatile byte state = LOW;

SemaphoreHandle_t xBinarySemaphore;

void ISRcallback();
void ISRprocessing(void * parameter);

void setup() {

    Serial.begin(115200);
    pinMode(ledPin, OUTPUT);

    pinMode(interruptPin, INPUT_PULLUP); // set interrupt pin in input with pullup 
    // attach interrupt to the pin
    attachInterrupt(digitalPinToInterrupt(interruptPin), ISRcallback, FALLING);

    /* initialize binary semaphore */
    xBinarySemaphore = xSemaphoreCreateBinary();

    /* this task will process the interrupt event
      which is forwarded by interrupt callback function */
    xTaskCreate(
            ISRprocessing, /* Task function. */
            "ISRprocessing", /* name of task. */
            1000, /* Stack size of task */
            (void *) "ISR", /* parameter of the task */
            4, /* priority of the task */
            NULL);
}

void loop() {
}

/* fonction ISR appellé par interruption GPIO13 CHANGE  */
void ISRcallback() {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    /* unblock  the interrupt processing task now */
    xSemaphoreGiveFromISR(xBinarySemaphore, &xHigherPriorityTaskWoken);
}

/* Cette fonction sera invoquée quand additionalTask sera créée */
void ISRprocessing(void * parameter) {

    Serial.println((char *) parameter);
    int i = 0;
    unsigned int lastMillis = millis();
    
    /* loop forever */
    while (1) {
        /* La tâche prend le sémaphore s'il est présent, sinon attend */
        xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
        // Serial.println("ISRprocessing is running ");

        if (millis() - lastMillis > 250) { //Software anti-rebond
            i++;
            Serial.println(i);
            /* toggle the LED now */
            state = !state;
            digitalWrite(ledPin, state);

        }
        lastMillis = millis();

    }
    vTaskDelete(NULL);
}

