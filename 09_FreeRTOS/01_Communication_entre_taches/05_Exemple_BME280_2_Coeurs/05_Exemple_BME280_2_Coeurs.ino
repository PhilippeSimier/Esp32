#include <Wire.h>
#include <Adafruit_BME280.h>



typedef struct {
  float t;
  float h;
  float p;
} typeMesure;



Adafruit_BME280 bme;

QueueHandle_t queue;
int queueSize = 128;
static int taskCore = 1;
int LED = 22;

// Tache lecteur du capteur BME280
void sensorTask( void * pvParameters ) {
  typeMesure mesureSend;

  while (1) {
    mesureSend.t = bme.readTemperature();
    mesureSend.h = bme.readHumidity();
    mesureSend.p = bme.readPressure() / 100.0F;

    xQueueSend(queue, &mesureSend, portMAX_DELAY);
    delay(10000);
  }
}

// Tache blinking led intégrée verte
void blinkTask(void * pvParameters ) {
  while (1) {
    digitalWrite(LED, digitalRead(LED) ^1);
    delay(1000);
  }
}


void setup() {
  Serial.begin(115200);
  while (!Serial);

  queue = xQueueCreate( queueSize, sizeof( typeMesure ));

  Serial.println("BME280 test");
  if (!bme.begin(0x77)) {
    Serial.println("Ne peut pas trouver le capteur BME280!");
    while (1);
  }

  xTaskCreatePinnedToCore(
    sensorTask,     /* Function pour implémenter la tâche */
    "sensorTask",   /* le Nom de la tâche */
    10000,          /* la taille de la pile en mots */
    NULL,           /* paramètre d'entrée */
    0,              /* Priorité de la tâche */
    NULL,           /* Tâche handle */
    taskCore        /* Core where the task should run */
  );
  Serial.println("Tâche sensorTask créée...");

  pinMode(LED, OUTPUT);
  xTaskCreate(
    blinkTask,      /* la fonction associée . */
    "blinkTask",    /* le nom de la tâche */
    10000,          /* la taille de la pile */
    NULL,           /* parameter of the task */
    1,              /* priorité de la tâche */
    NULL);          /* Task handle to keep track of created task */
}

void loop() {
  typeMesure mesureReceive;

  Serial.println("----------------------");

  xQueueReceive(queue, &mesureReceive, portMAX_DELAY);

  Serial.print("température : "); Serial.println(mesureReceive.t);
  Serial.print("humidité : "); Serial.println(mesureReceive.h);
  Serial.print("pression : "); Serial.println(mesureReceive.p);

  delay(50);

}
