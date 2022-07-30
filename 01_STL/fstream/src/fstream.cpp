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
#include <iostream>

void setup() {

    Serial.begin(115200);

    if (!SPIFFS.begin(true)) {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }

    std::ofstream flux_sortie;

    try {

        flux_sortie.open("/spiffs/test.txt"); // Ouverture d'un fichier en écriture dans la partition flash spiffs

        flux_sortie << "Une première ligne dans le fichier test.txt\r\n";
        flux_sortie << "Maître corbeau sur un arbre perché\r\n";
        flux_sortie.close();

        std::ifstream flux_entree("/spiffs/test.txt");

        

        // Lecture ligne par ligne
        std::string line;
        
        if (flux_entree.is_open()) {
            Serial.println("lecture fichier ligne par ligne ");
            while (getline(flux_entree, line)) {
                std::cout << line << '\n';
            }
            flux_entree.close();
        } else
            Serial.println("Unable to open file");

        delay(500);

        // Lecture caractère par caractère
        flux_entree.open("/spiffs/test.txt"); // re Ouverture du fichier
        char c;
        if (flux_entree.is_open()) {
            Serial.println("lecture fichier caractère par caractère ");
            while (flux_entree.get(c)) {

                Serial.print(c);
            }
            flux_entree.close();
        } else
            Serial.println("Unable to open file");

    }    
    catch (std::exception e) {
        Serial.println(e.what());

    }
}

void loop() {
}


