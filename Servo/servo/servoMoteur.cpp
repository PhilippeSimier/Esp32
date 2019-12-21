/**
    @author Simier philippe
    @date   Samedi 21/12/2019
    @file   servoMoteur.h
*/


#include "servoMoteur.h"


ServoMoteur::ServoMoteur()
{
  int freq = 50;
  channel = 0;
  gpio = 0;
  int resolution = 10;
  pos = 65;
  ledcSetup(channel, freq, resolution); // channel 0, 50 Hz, 16-bit width

  //ledcWrite(channel, pos);
}

void ServoMoteur::Attacher(int _gpio)
{
  gpio = _gpio;
  ledcAttachPin(gpio, channel);   // GPIO 2 assigned to channel 1
}

void ServoMoteur::Detacher()
{
  ledcDetachPin(gpio);
}



void ServoMoteur::Positionner(int _pos)
{
  if (_pos > 0) {
    pos = _pos;
    pos = map(pos, 0, 180, 22, 120); // change l'échelle
    ledcWrite(channel, pos);
  }
}
