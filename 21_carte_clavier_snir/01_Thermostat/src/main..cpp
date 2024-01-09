#include <Arduino.h>
#include <math.h>
#include "afficheur.h"
#include "thermometre.h"
#include "thermostat.h"

float temperature = 0;
float consigne = 0;
unsigned long precedent;

void setup()
{
    InitialiserAfficheur();
    InitialiserCapteurTemperature();
    InitialiserThermostat();

    pinMode(SW, INPUT);
    pinMode(RELAY_1,OUTPUT);
    precedent = millis() - INTERVAL; // pour passer imédiatement la première fois
}

void loop()
{
    int unite;
    int dixiemes;

    if (digitalRead(SW) == LOW)
    {
        consigne = FixerConsigne(consigne);
    }
    else
    {
        unsigned long courant = millis();
        if (courant - precedent >= INTERVAL)
        {
            precedent = courant;
            if (ObtenirTemperature(&unite, &dixiemes) == true)
                AfficherTemperature(unite, dixiemes);

            if(RegulerTemperature(consigne, unite + dixiemes / 10, HYSTERESIS) == true)
                digitalWrite(RELAY_1,HIGH);
            else
                digitalWrite(RELAY_1,LOW);
                
        }
    }
}