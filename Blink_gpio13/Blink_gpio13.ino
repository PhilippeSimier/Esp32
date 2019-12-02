/*
 
*/

#define LED 13
#define InAna 3

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() {
  
  int value = analogRead(InAna);

  Serial.println(value);
  digitalWrite(LED, HIGH);
  delay(200); // delay in between reads for stability
  digitalWrite(LED, LOW);
  delay(1000);
}
