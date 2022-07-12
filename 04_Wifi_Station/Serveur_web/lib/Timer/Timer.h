/* 
 * File:   Timer.h
 * Author: philippe
 *
 * Created on 12 juillet 2022, 17:30
 */

#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

class Timer {
public:

    Timer(bool _unCoup = false);
    Timer(const Timer& orig);
    virtual ~Timer();

    void lancer(unsigned long _milliSecondes);
    void lancer(int _heures, int _minutes, int _secondes);
    bool scruter();

private:

    unsigned long millisecondes;    // Durée de l'attente
    unsigned long valeurPrecedente; // valeur du temps précédent
    bool unCoup;                    // Mode du timer vrai une seule fois, faux mode infini
    bool actif;                     // Etat du timer vrai pour actif

};

#endif /* TIMER_H */

