/* 
 * File:   thermostat.h
 * Author: pcruchet
 *
 * Created on 30 novembre 2023, 14:42
 */

#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include "afficheur.h"
#include "esp32_snir.h"

#define INTERVAL 5000 // mesure de la température toutes les 5s
#define HYSTERESIS 1

void InitialiserThermostat(void);
float FixerConsigne(const float _consigne);
bool RegulerTemperature(const float _consigne, const float _temperature, const int _hysteresis);

#endif /* THERMOSTAT_H */

