/* 
 * File:   fstream.cpp
 * Author: philippe SIMIER Lycée Touchard le Mans
 *
 * Created on 29 juillet 2022, 17:23
 * 
 * programme pour tester les flux sur fichiers
 */

#include <Arduino.h>
#include <SPIFFS.h>
#include <fstream>

void setup() {

    Serial.begin(115200);

    if (!SPIFFS.begin(true)) {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }

    std::ofstream flux_sortie;
    
    flux_sortie.open("/spiffs/test.txt");   // Ouverture d'un fichier en écriture

    flux_sortie << "une première ligne dans le fichier test.txt\r\n";
    flux_sortie << "Maître corbeau sur un arbre perché\r\n";
    flux_sortie.close();

    std::ifstream flux_entree("/spiffs/test.txt");

    char c;
    while (flux_entree.get(c)) {

        Serial.print(c);
    }

}

void loop() {
}


