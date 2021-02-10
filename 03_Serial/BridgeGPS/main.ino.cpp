/*
Gps
*/
#include <HardwareSerial.h>

#define LED 22


HardwareSerial serialGps(2);



// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  serialGps.begin(4800, SERIAL_8N1, 16, 17);

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  
  char car;
  //non utilisé pour le gps
  /*
  if (Serial.available() > 0) {
    car = Serial.read();
    serialGps.write(car);
  }
 */
  if (serialGps.available() > 0) {
    car = serialGps.read();
    Serial.write(car);
  }
  
}

