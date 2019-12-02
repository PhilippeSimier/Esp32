/**
  * @author kauve
  * @date   Vendredi 29 mars 2019
  * @file   timer.h
  */

#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

class Timer
{
public:
    Timer(bool _unCoup=false);
    void Lancer(unsigned long _milliSecondes);
    void Lancer(int _heures, int _minutes, int _secondes);
    bool Scruter();

private:
       unsigned long millisecondes;     /// Durée de l'attente
       unsigned long valeurPrecedente;  /// valeur du temps précédent
       bool unCoup;     /// Mode du timer vrai une seule fois, faux mode infini
       bool actif;      /// Etat du timer vrai pour actif
};

#endif // TIMER_H
