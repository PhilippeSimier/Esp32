/*
  ESP 32 Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
  The ESP32 has an internal blue LED at D2 (GPIO 02)
  
*/

int LED = 22;

void setup() 
{
  pinMode(LED, OUTPUT);
  
}

void loop() 
{
  digitalWrite(LED, digitalRead(LED) ^1);   // turn the LED 
  delay(200);                       // wait for a second
  digitalWrite(LED, digitalRead(LED) ^1);    // turn the LED 
  delay(1000);                       // wait for a second
}
