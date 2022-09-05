
/* 
 * File:   Serrure.h
 * Author: fmartin
 *
 * Created on 2 février 2022, 01:01
 */

#ifndef SERRURE_H
#define SERRURE_H

#include <Arduino.h>
#include <ESP32Servo.h>  // Bibliothèque ESP32Servo  #id 4744

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

