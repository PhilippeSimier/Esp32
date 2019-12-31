void setup() {
  pinMode( 2, OUTPUT);
  pinMode( 13, INPUT_PULLUP); // BP est sur 13

  Serial.begin(9600);
  while (!Serial);

}

void loop() {
  int etat = digitalRead(13);
  Serial.print("GPIO13 : "); Serial.println(etat);
  digitalWrite(2, etat);
  delay(100);
}
