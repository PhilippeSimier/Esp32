#include <Arduino.h>
#include <afficheur.h>
#include <thermometre.h>
#include <thermostat.h>

float temperature = 0;
float consigne = 0;
unsigned long precedent;

void setup()
{
    initialiserAfficheur();
    initialiserCapteurTemperature();
    initialiserThermostat();

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
        consigne = fixerConsigne(consigne);
    }
    else
    {
        unsigned long courant = millis();
        if (courant - precedent >= INTERVAL)
        {
            precedent = courant;
            if (obtenirTemperature(&unite, &dixiemes) == true)
                afficherTemperature(unite, dixiemes);

            if(regulerTemperature(consigne, unite + dixiemes / 10, HYSTERESIS) == true)
                digitalWrite(RELAY_1,HIGH);
            else
                digitalWrite(RELAY_1,LOW);
                
        }
    }
}