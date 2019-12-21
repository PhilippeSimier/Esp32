
#include "servoMoteur.h"

ServoMoteur monServo;

void setup() {
  Serial.begin(9600);
  monServo.Attacher(2);

}

void loop() {
  int pos;
  if (Serial.available() > 0) {
    // lit ce qui arrive sur le port série et le convertit en nombre entier
    pos = Serial.parseInt();
    if (pos > 0) {
      monServo.Positionner(pos);
      Serial.println(pos);
    }

  }
}
