/* 
  Dans cet exemple nous allons créer deux taches avec la même priorité d’exécution. 
  La tache principale (loop) reste inactive.
*/

void setup() {
  Serial.begin(9600);
  delay(1000);
  xTaskCreate(
    tacheUne,     /* Task function. */
    "TacheUne",   /* String with name of task. */
    10000,        /* Stack size in words. */
    NULL,         /* Parameter passed as input of the task */
    1,            /* Priority of the task. */
    NULL);        /* Task handle. */
  
  xTaskCreate(
    tacheDeux,    /* Task function. */
    "TacheDeux",  /* String with name of task. */
    10000,        /* Stack size in words. */
    NULL,         /* Parameter passed as input of the task */
    1,            /* Priority of the task. */
    NULL);        /* Task handle. */
}

void loop() {
  delay(1000);
}

void tacheUne( void * parameter )
{
  for ( int i = 0; i < 10; i++ ) {
    Serial.println("Bonjour de tache 1");
    delay(1000);
  }
  Serial.println("Fin de tache 1");
  vTaskDelete( NULL );
}

void tacheDeux( void * parameter)
{
  for ( int i = 0; i < 10; i++ ) {
    Serial.println("Bonjour de tache 2");
    delay(1000);
  }
  Serial.println("Fin de tache 2");
  vTaskDelete( NULL );
}
