
SemaphoreHandle_t xMutex;

/* Tâche de basse priorité */
void lowPriorityTask( void * parameter )
{
  Serial.println((char *)parameter);
  for (;;) {

    /* Voyez si nous pouvons obtenir le sémaphore. */
    Serial.println("lowPriorityTask  attend la clé");
     xSemaphoreTake( xMutex, portMAX_DELAY );
    /* Nous avons pu obtenir le sémaphore et 
     *  pouvons maintenant accéder à la ressource partagée. */
    Serial.println("lowPriorityTask a gagné la clé");
    Serial.println("lowPriorityTask is running");
    delay(2000);
    /* Nous avons fini d'accéder à la ressource partagée. 
     * nous relâchons le sémaphore. */
    Serial.println("lowPriorityTask  rend la clé");
    xSemaphoreGive( xMutex );
  }
  vTaskDelete( NULL );
}

/* Tâche de haute priorité */
void highPriorityTask( void * parameter )
{
  Serial.println((char *)parameter);
  for (;;) {
    Serial.println("highPriorityTask  attend la clé");
    xSemaphoreTake( xMutex, portMAX_DELAY );
    Serial.println("highPriorityTask a gagné la clé");
    Serial.println("highPriorityTask is running");
    Serial.println("highPriorityTask rend la clé");
    xSemaphoreGive( xMutex );
    /* attente de 1s afin que lowPriorityTask ait une chance de s'exécuter */
    delay(1000);
  }
  vTaskDelete( NULL );
}


void setup() {
  Serial.begin(9600);

  /* creation d'un Mutex */
  xMutex = xSemaphoreCreateMutex();

  xTaskCreate(
    lowPriorityTask,    /* Task function. */
    "lowPriorityTask",  /* name of task. */
    1000,               /* Stack size of task */
    NULL,               /* parameter of the task */
    1,                  /* priority of the task */
    NULL);              /* Task handle to keep track of created task */

  delay(500);
  /* let lowPriorityTask run first then create highPriorityTask */

  xTaskCreate(
    highPriorityTask,   /* Task function. */
    "highPriorityTask", /* name of task. */
    1000,               /* Stack size of task */
    NULL,               /* parameter of the task */
    4,                  /* priority of the task */
    NULL);              /* Task handle to keep track of created task */
}

void loop() {
}
