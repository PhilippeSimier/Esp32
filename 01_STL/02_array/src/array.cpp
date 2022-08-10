/* 
 * File:   array.cpp
 * Author: philippe SIMIER Lycée Touchard le Mans
 *
 * Created on 30 juillet 2022, 16:32
 */

#include <Arduino.h>
#include <array>
#include <algorithm>

void AfficherValeurs(int val)
{
    Serial.printf(" %2d", val);
}

void setup() {

    Serial.begin(115200);
    
    // Déclaration et initialisation d'un tableau
    std::array < int,10 > tableau1  {15, 8, 25, 2, 9, 0, 12, 38, 10, 3};
    
    Serial.println("Affichage du tableau");
    std::for_each (tableau1.begin(), tableau1.end(), AfficherValeurs);
    Serial.println("");
    
    Serial.println("Affichage du tableau trié");
    std::sort(tableau1.begin(), tableau1.end());
    std::for_each (tableau1.begin(), tableau1.end(), AfficherValeurs);
    Serial.println("");
    
    
}  


void loop() {
}

