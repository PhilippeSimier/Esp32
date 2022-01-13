#include <Arduino.h>
#include <HardwareSerial.h>


HardwareSerial serialSigfox(2); // Déclaration d'un controleur lié à UART 2

void setup() {
  Serial.begin(115200);

  // Carte Ruche connectée
  // GPIO16 Rx_esp32
  // GPIO17 Tx_esp32
  serialSigfox.begin(9600, SERIAL_8N1, 16, 17);
  delay(1000);
  Serial.println("Sigfox Serial Bridge");

  pinMode(02, OUTPUT);
}

void loop() {

  char car;

  if (Serial.available() > 0) {
    car = Serial.read();
    serialSigfox.write(car);
    Serial.write(car);
  }

  if (serialSigfox.available() > 0) {
    car = serialSigfox.read();
    Serial.write(car);
  }

}
