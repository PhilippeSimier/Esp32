/* 
 * File:   Timer.cpp
 * Author: philippe
 * 
 * Created on 12 juillet 2022, 17:30
 */

#include "Timer.h"

/**
 * @brief Timer::Timer
 * @param _unCoup permet de définir le mode du timer par défaut mode infini, si true alors une seule fois
 * @details Constructeur de la classe. Le timer est inactif, il faut appelé Lancer ensuite.
 */

Timer::Timer(bool _unCoup) :
unCoup(_unCoup),
actif(false) {
    
}

Timer::Timer(const Timer& orig) {
}

Timer::~Timer() {
}

/**
 * @brief Timer::lancer
 * @param _milliSecondes Durée de la tempo
 * @details Lance le timer avec le temps en millisecondes
 */
void Timer::lancer(unsigned long _milliSecondes)
{
    millisecondes = _milliSecondes;
    valeurPrecedente = millis();
    actif = true;
}

/**
 * @brief Timer::lancer
 * @param _heures
 * @param _minutes
 * @param _secondes
 * @details Lance le timer avec le temps exprimé en heures, minutes, secondes
 */
void Timer::lancer(int _heures, int _minutes, int _secondes)
{
    millisecondes = (60 * ( 60 * _heures + _minutes) + _secondes) * 1000 ;
    valeurPrecedente = millis();
    actif = true;
}

/**
 * @brief Timer::scruter
 * @return vrai si le temps est écoulé, faux sinon
 * @details Si le timer est configuré pour une seule fois, l'attribut actif repasse à faux
 */
bool Timer::scruter()
{
    bool retour = false;
    if(actif && (millis() - valeurPrecedente >= millisecondes))
    {
        valeurPrecedente = millis();
        retour = true;
        if(unCoup)
          actif = false;
    }
    return retour;
}

