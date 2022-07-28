/* 
 * File:   vector.cpp
 * Author: philippe SIMIER Lycée Touchard Le Mans
 * 
 * Programme pour tester l'utilisation du conteneur std::vector 
 * et de quelques méthodes comme push_back, sort et find
 * Created on 27 juillet 2022, 08:25
 */

#include <Arduino.h>
#include <vector>
#include <algorithm>    // fonction sort
#include <iostream>      // flux de sortie
#include <optional>

std::vector<String> monVecteur = {"programme", "langage", "cpp", "esp32"};

// Prototype pour afficher un vecteur de String
void afficher(const std::vector<String> &v);

void setup() {
    pinMode(02, OUTPUT);
    Serial.begin(115200);

    afficher(monVecteur);

    monVecteur.push_back("arduino");
    sort(monVecteur.begin(), monVecteur.end()); // pour trier le tableau

    afficher(monVecteur);

    // Recherche d'un élément
    std::vector<String>::iterator it; // déclaration d'un itérator
    it = find(monVecteur.begin(), monVecteur.end(), "cpp");

    if (it != monVecteur.end()){
        Serial.print( "Element trouvé : ");
        Serial.println(*it);
    }
    else
         Serial.println( "Element non trouvé");


    std::cout << "La taille de mon vecteur : " << monVecteur.size() << std::endl;
    std::cout << "La capacité de mon vecteur : " << monVecteur.capacity() << std::endl;
    std::cout << "Setup done" << std::endl;


}

void loop() {

}

/**
 * 
 * @param v une référence sur un veteur de String
 */
void afficher(const std::vector<String> &v) {

    for (int i = 0; i < v.size(); i++) {
        Serial.print(v.at(i));
        Serial.print(" | ");
    }
    Serial.print("\n\r");
}

