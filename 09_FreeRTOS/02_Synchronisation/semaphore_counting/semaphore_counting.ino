int nTasks = 4;
SemaphoreHandle_t barrierSemaphore = xSemaphoreCreateCounting( nTasks, 0 );

void genericTask( void * parameter ) {
  String taskMessage = "Tâche numéro : ";
  int nb;
  nb = *((int *)parameter);
  taskMessage = taskMessage + nb;
  Serial.println(taskMessage);
  xSemaphoreGive(barrierSemaphore);   // Incrémente le sémaphore désigné par barrierSemaphore
  vTaskDelete(NULL);
}



void setup()
{
  Serial.begin(9600); 
  delay(1000);
  Serial.println("Starting to launch tasks..");
  int i;
  
  for (i = 0; i < nTasks; i++) {
    xTaskCreatePinnedToCore(
      genericTask,        /* Function to implement the task */
      "genericTask",      /* Name of the task */
      10000,              /* Stack size in words */
      (void *)&i,         /* Task input parameter */
      0,                  /* Priority of the task */
      NULL,               /* Task handle. */
      1);                 /* Core where the task should run */
  }

  for (i = 0; i < nTasks; i++) {
    xSemaphoreTake(barrierSemaphore, portMAX_DELAY);   // Décrémente le sémaphore désigné par son descripteur
  }
  Serial.println("Tasks launched and semaphore passed...");
}

void loop() {
  vTaskSuspend(NULL);
}
