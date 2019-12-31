byte ledPin = 2; // LED
byte interruptPin = 13; // button BP D13

volatile byte state = LOW;

SemaphoreHandle_t xBinarySemaphore;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP); // set interrupt pin in pullup mode
  // attach interrupt to the pin
  attachInterrupt(digitalPinToInterrupt(interruptPin), ISRcallback, CHANGE);

  /* initialize binary semaphore */
  xBinarySemaphore = xSemaphoreCreateBinary();

  /* this task will process the interrupt event
    which is forwarded by interrupt callback function */
  xTaskCreate(
    ISRprocessing,      /* Task function. */
    "ISRprocessing",    /* name of task. */
    1000,               /* Stack size of task */
    NULL,               /* parameter of the task */
    4,                  /* priority of the task */
    NULL);
}

void loop() {
}

/* fonction ISR appellé par interruption GPIO13 CHANGE  */
void ISRcallback() {
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  /* unblock  the interrupt processing task now */
  xSemaphoreGiveFromISR( xBinarySemaphore, &xHigherPriorityTaskWoken );
}

/* Cette fonction sera invoquée quand additionalTask sera créée */
void ISRprocessing( void * parameter )
{
  Serial.println((char *)parameter);
  /* loop forever */
  for (;;) {
    /* La tâche prend le sémaphore s'il est présent, sinon attend */
    xSemaphoreTake( xBinarySemaphore, portMAX_DELAY );
    Serial.println("ISRprocessing is running");
    /* toggle the LED now */
    state = !state;
    digitalWrite(ledPin, state);
    delay(100);
  }
  vTaskDelete( NULL );
}
