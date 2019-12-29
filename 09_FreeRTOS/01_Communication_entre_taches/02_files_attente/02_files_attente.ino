/*
 * Ici nous insérons et consommons des éléments dans la file d'attente 
 * de la fonction de boucle principale Arduino, 
 * afin de nous concentrer sur les appels API de base.
 * xQueueCreate, xQueueSend, xQueueReceive
 */


QueueHandle_t queue;

void setup() {
  Serial.begin(9600);

  queue = xQueueCreate( 10, sizeof( int ) );
  if (queue == NULL) {
    Serial.println("Erreur de création de file");
  }
}

void loop() {
  if (queue == NULL)
    return;
    
  for (int i = 0; i < 10; i++) {
    xQueueSend(queue, &i, portMAX_DELAY);
  }
  
  int element;
  for (int i = 0; i < 10; i++) {
    xQueueReceive(queue, &element, portMAX_DELAY);
    Serial.print(element);
    Serial.print("|");
  }
  Serial.println();
  delay(1000);
}
