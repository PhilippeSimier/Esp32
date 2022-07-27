/* 
 * File:   vector.cpp
 * Author: philippe SIMIER Lycée Touchard Le Mans
 * 
 * Programme pour tester l'utilisation du conteneur std::vector
 * Created on 27 juillet 2022, 08:25
 */

#include <Arduino.h>
#include <vector>
#include <algorithm>    // fonction sort
#include <iostream>      // flux de sortie
#include <optional>

std::vector<String> monVecteur = {"bonjour", "comment", "allez", "vous"};

void setup() {
    pinMode(02, OUTPUT);
    Serial.begin(115200);

    monVecteur.push_back("?");
    sort(monVecteur.begin(), monVecteur.end()); // pour trier le tableau

    for (int i = 0; i < monVecteur.size(); i++) {
        Serial.print(monVecteur.at(i));
        Serial.print(" | ");
    }
    Serial.print("\n\r");

    std::cout << "La taille de mon vecteur : " << monVecteur.size() << std::endl;
    std::cout << "La capacité de mon vecteur : " << monVecteur.capacity() << std::endl;
    std::cout << "Setup done" << std::endl;


}

void loop() {

}
