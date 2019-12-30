#include <Wire.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme;

QueueHandle_t queue;
int queueSize = 128;

void sensorTask( void * pvParameters ) {
  float t, h, p;
  while (true) {
    t = bme.readTemperature();
    h = bme.readHumidity();
    p = bme.readPressure() / 100.0F;

    xQueueSend(queue, &t, portMAX_DELAY);
    xQueueSend(queue, &h, portMAX_DELAY);
    xQueueSend(queue, &p, portMAX_DELAY);
    delay(1000);
  }
}


void setup() {
  Serial.begin(9600);
  while (!Serial);

  queue = xQueueCreate( queueSize, sizeof( int ) );

  Serial.println("BME280 test");
  if (!bme.begin(0x76)) {
    Serial.println("Ne peut pas trouver le capteur BME280!");
    while (1);
  }

  xTaskCreate(
    sensorTask,     /* Function pour implémenter la tâche */
    "sensorTask",   /* le Nom de la tâche */
    10000,          /* la taille de la pile en mots */
    NULL,           /* paramètre d'entrée */
    0,              /* Priorité de la tâche */
    NULL );         /* Tâche handle */
  Serial.println("Tâche sensorTask créée...");
}

void loop() {
  float t, h, p;
  Serial.println("----------------------");

  xQueueReceive(queue, &t, portMAX_DELAY);
  xQueueReceive(queue, &h, portMAX_DELAY);
  xQueueReceive(queue, &p, portMAX_DELAY);

  Serial.print("température : "); Serial.println(t);
  Serial.print("humidité : "); Serial.println(h);
  Serial.print("pression : "); Serial.println(p);

  delay(1000);
}
