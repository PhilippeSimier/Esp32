void setup() {
  Serial.begin(9600);
  /* nous créons une nouvelle tâche ici */
  xTaskCreate(
    additionalTask,    /* la fonction associée . */
    "additional Task", /* le nom de la tâche */
    10000,             /* la taille de la pile */
    NULL,              /* parameter of the task */
    1,                 /* priorité de la tâche */
    NULL);             /* Task handle to keep track of created task */
}
/* loop() function appelée par Arduino ESP32 loopTask */
void loop() {
  Serial.println("C'est la tâche Arduino");
  delay(1000);
}
/* cette fonction sera invoquée lors de la création de additionalTask */
void additionalTask( void * parameter )
{
  /* boucle infinie */
  for (;;) {
    Serial.println("C'est la tâche additionnelle");
    delay(1000);
  }
  /* supprimer la tâche à la fin,
    cela n'arrivera jamais puisque c'est après une boucle infinie */
  vTaskDelete( NULL );
}
