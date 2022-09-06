
/* 
 * File:   Serrure.h
 * Author: Philippe SIMIER
 *
 * Created on 2 février 2022, 01:01
 * pio pkg install --library madhephaestus/ESP32Servo
 * 
 */

#ifndef SERRURE_H
#define SERRURE_H

#include <Arduino.h>
#include <ESP32Servo.h>  

class Serrure {
public:
    Serrure(const uint8_t _brocheLedD1 = 13, const uint8_t _brocheServo = 2); // Affectation broches LedD1:GPIO13 et servo:GPIO2
    void Deverrouiller();
    void Verrouiller();

private:
    Servo leServo;
    uint8_t brocheLedD1;
    uint8_t brocheServo;
};

#endif /* SERRURE_H */

