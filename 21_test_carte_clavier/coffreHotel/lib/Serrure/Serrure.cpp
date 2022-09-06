/* 
 * File:   Serrure.cpp
 * Author: Philippe SIMIER
 * 
 * Created on 2 février 2022, 01:01
 */

#include <Serrure.h>

Serrure::Serrure(const uint8_t _brocheLedD1, const uint8_t _brocheServo) :
brocheLedD1(_brocheLedD1),
brocheServo(_brocheServo)
{
    pinMode(brocheLedD1, OUTPUT);   // configuration broche Led D1 en sortie

    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);
    leServo.setPeriodHertz(50); //  configuration période 50 Hz pour le  servo
    leServo.attach(brocheServo, 1000, 2000); // affectation broche 5 pour commande servo
}

void Serrure::Deverrouiller() {
    digitalWrite(brocheLedD1, LOW);  // Eteindre Led D1
    leServo.write(0);  // commande servo à 0 °
}

void Serrure::Verrouiller() {
    digitalWrite(brocheLedD1, HIGH);  // Allumer Led D1
    leServo.write(180);   // commande servo à 180 °
}