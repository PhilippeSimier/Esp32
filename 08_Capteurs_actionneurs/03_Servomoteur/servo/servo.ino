
#include "servoMoteur.h"

ServoMoteur monServo1;
ServoMoteur monServo2;
int flag;

void setup() {
  Serial.begin(9600);
  monServo1.Attacher(15, 200, 3000);
  monServo2.Attacher(2);
  flag = 0;

}

void loop() {
  int pos;
  if (Serial.available() > 0) {
    // lit ce qui arrive sur le port série et le convertit en nombre entier
    pos = Serial.parseInt();
    if (pos > 0 && pos <= 180) {
      if (flag == 1) {
        monServo1.Positionner(pos);
        Serial.print("servo 1 : ");
        flag = 0;
      }
      else {
        monServo2.Positionner(pos);
        Serial.print("servo 2 : ");
        flag = 1;
      }

      Serial.println(pos);
    }

  }
}
