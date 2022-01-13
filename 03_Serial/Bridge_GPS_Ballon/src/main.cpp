/*
        Gps pour le ballon BYONICS GPS5 HA
*/

#include <HardwareSerial.h>

#define LED 22

HardwareSerial serialGps(1); // Déclaration d'un controleur lié à UART 1

void setup() {
  Serial.begin(115800);
  serialGps.begin(4800, SERIAL_8N1, 16, 17);

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED, OUTPUT);
}


void loop() {

  char car;

  if (serialGps.available() > 0) {
    car = serialGps.read();
    Serial.write(car);
  }

}
