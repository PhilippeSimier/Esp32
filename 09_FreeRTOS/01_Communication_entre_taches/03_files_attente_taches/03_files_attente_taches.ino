#include <Adafruit_CircuitPlayground.h>
#include <Adafruit_Circuit_Playground.h>



QueueHandle_t queue;
int queueSize = 10;

void setup() {
  Serial.begin(9600);
  delay(2000);
  queue = xQueueCreate( queueSize, sizeof( int ) );
  if (queue == NULL) {
    Serial.println("Error creating the queue");
  }

  xTaskCreate(
    producerTask, /* Task function. */
    "Producer",   /* String with name of task. */
    10000,        /* Stack size in words. */
    NULL,         /* Parameter passed as input of the task */
    1,            /* Priority of the task. */
    NULL);        /* Task handle. */

  xTaskCreate(
    consumerTask, /* Task function. */
    "Consumer",   /* String with name of task. */
    10000,        /* Stack size in words. */
    NULL,         /* Parameter passed as input of the task */
    1,            /* Priority of the task. */
    NULL);        /* Task handle. */
}

void loop() {
  Serial.println("in the loop");
  delay(6000);
}

void producerTask( void * parameter )
{
  float valeur = 1.0;
  for ( int i = 0; i < queueSize; i++ ) {
    xQueueSend(queue, &valeur, portMAX_DELAY);
    valeur *= 2;
  }
  vTaskDelete( NULL );
}

void consumerTask( void * parameter)
{
  float element;
  for ( int i = 0; i < queueSize; i++ ) {
    xQueueReceive(queue, &element, portMAX_DELAY);
    Serial.print(element);
    Serial.print("|");
  }
  vTaskDelete( NULL );
}
