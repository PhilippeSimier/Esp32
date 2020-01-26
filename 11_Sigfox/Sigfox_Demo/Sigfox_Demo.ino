#include "sigfox.h"

typedef struct {
  int16_t temp;
  unsigned char compteur;
  unsigned char humidite;
} trame;

Sigfox mySigfox(26, 27, true);
int16_t temperature;

void setup() {
  Serial.begin(9600);
  mySigfox.begin();
  trame t;
  
  t.temp = mySigfox.obtenirTemp();
  t.compteur = 1;
  t.humidite = 50;
  delay(1000);
  bool statusSig = mySigfox.envoyer(&t, sizeof(t));

}

void loop() {
  // put your main code here, to run repeatedly:

}
