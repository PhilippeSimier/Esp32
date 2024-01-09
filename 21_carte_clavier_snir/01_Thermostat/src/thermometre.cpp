#include "thermometre.h"

OneWire onWire(TEMP);
DallasTemperature capteurTemp(&onWire);

void InitialiserCapteurTemperature(void)
{
    capteurTemp.begin();
}

bool ObtenirTemperature(int *_temperature, int * _dixiemes, const int _numCapteur)
{
    bool retour = false;
    capteurTemp.requestTemperatures();
    float temperature = capteurTemp.getTempCByIndex(_numCapteur);
    if(temperature != DEVICE_DISCONNECTED_C)
    {
        retour = true;
        *_dixiemes = (int)(round((temperature - floor(temperature))*10));
        *_temperature = (int)floor(temperature);
    }
    return retour;
}
