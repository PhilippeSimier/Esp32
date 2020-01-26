/*
   SigFox
*/
#include <HardwareSerial.h>

#define LED 22


HardwareSerial serialSig(2);




void setup() {
  Serial.begin(9600);
  serialSig.begin(9600, SERIAL_8N1, 26, 27);
  Serial.println("Sigfox Serial Bridge");
  
  pinMode(LED, OUTPUT);
}


void loop() {
  
  char car;
  
  if (Serial.available() > 0) {
    car = Serial.read();
    serialSig.write(car);
  }

  if (serialSig.available() > 0) {
    car = serialSig.read();
    Serial.write(car);
  }
  
}
