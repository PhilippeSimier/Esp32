int Int1 = 5;
int Int2 = 10;
int LED  = 2;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  delay(100);

  xTaskCreate(
    task1,                /* Task function. */
    "tache_1",            /* String with name of task. */
    10000,                /* Stack size in words. */
    (void*)&Int1,         /* Parameter passed as input of the task */
    1,                    /* Priority of the task. */
    NULL);                /* Task handle. */

  xTaskCreate(
    task2,                /* Task function. */
    "tache_2",            /* String with name of task. */
    10000,                /* Stack size in words. */
    (void*)&Int2,         /* Parameter passed as input of the task */
    1,                    /* Priority of the task. */
    NULL);                /* Task handle. */
}

void task1( void *parameter ) {
  Serial.print("Int1 : ");
  int nb = *((int*)parameter);  //lecture du parametre
  Serial.println(nb);
  
  for (int i=0; i < nb; i++){
    Serial.println(i);
    delay(500);
  }
  *((int*)parameter) = nb + 10;  // écriture du parametre
  vTaskDelete( NULL );
}

void task2( void *parameter ) {
  Serial.print("Int2 : ");
  int nb = *((int*)parameter);
  Serial.println(nb);
  
  for (int i=0; i < nb; i++){
    digitalWrite(LED, digitalRead(LED) ^1);
    delay(500);
  }
  
  vTaskDelete( NULL );
}

void loop() {
  delay(10000);
  Serial.print("Int1 : ");
  Serial.println(Int1);
  
}
