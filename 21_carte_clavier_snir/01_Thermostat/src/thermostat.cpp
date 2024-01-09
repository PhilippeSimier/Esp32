#include "thermostat.h"


void InitialiserThermostat(void)
{
    pinMode(BP1, INPUT); // bouton +
    pinMode(BP2, INPUT); // bouton -

    pinMode(D1, OUTPUT); //led rouge
    pinMode(D2, OUTPUT); //led verte
    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);
}

float FixerConsigne(const float _consigne)
{
    float consigne = _consigne;
    int dixiemes;
    int unite;

    if (digitalRead(BP1) == LOW)
        consigne += 0.5;
    if (digitalRead(BP2) == LOW)
        consigne -= 0.5;

    dixiemes = (int) (round((consigne - floor(consigne))*10));
    unite = (int) floor(consigne);
    AfficherTemperature(unite, dixiemes);
    delay(200);

    return consigne;
}

bool RegulerTemperature(const float _consigne, const float _temperature, const int _hysteresis)
{
    bool retour = false;
    if (_temperature < (_consigne - _hysteresis/2.0))
    {
        // Chauffe
        digitalWrite(D1, HIGH);
        digitalWrite(D2, LOW);
        retour = true;
    }

    if (_temperature >= (_consigne + _hysteresis/2.0))
    {
        // Repos
        digitalWrite(D1, LOW);
        digitalWrite(D2, HIGH);
    }
    return retour;
}
