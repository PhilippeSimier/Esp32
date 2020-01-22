/**
    @author Simier philippe
    @date   Samedi 21/12/2019
    @file   servoMoteur.h
*/


#include "servoMoteur.h"

// initialisation de la variable de classe channel
int ServoMoteur::compteurChannel = 0;

ServoMoteur::ServoMoteur()
{
  channel = compteurChannel;
  compteurChannel++; 
  gpio = 0;
  pos = 90;
  ledcSetup(channel, 50, 16); // channel 0, 50 Hz, 16-bit width
}

void ServoMoteur::Attacher(int _gpio, int _mini, int _maxi)
{
  gpio = _gpio;
  ledcAttachPin(gpio, channel);   
  mini = (int)((float)_mini/0.30517);
  maxi = (int)((float)_maxi/0.30517);
}

void ServoMoteur::Attacher(int _gpio)
{
  gpio = _gpio;
  ledcAttachPin(gpio, channel);   
  mini = 1782;
  maxi = 7864;
}

void ServoMoteur::Detacher()
{
  ledcDetachPin(gpio);
}



void ServoMoteur::Positionner(int _pos)
{
  if (_pos >= 0 && _pos <= 180) {
    pos = _pos;
    pos = map(pos, 0, 180, mini, maxi); // change l'échelle
    ledcWrite(channel, pos);
  }
}
