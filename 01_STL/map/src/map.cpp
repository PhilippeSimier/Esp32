/* 
 * File:   map.cpp
 * Author: philippe SIMIER Lycée Touchard le Mans
 * 
 * test avec le contenur std::map
 * 
 * 
 * Created on 28 juillet 2022, 21:37
 */

#include <Arduino.h>
#include <map>
#include <exception>

std::map<String, int> m;

// Prototype d'une fonction pour afficher le contenu de la map avec un iterateur
void afficher(std::map<String, int> &x);
// Prototype d'une fonction pour afficher le contenu de la map avec un range
void afficher2(std::map<String, int> &x);

void setup() {

    Serial.begin(115200);

    // Quelques  possibilités pour insérer des éléments dans la map
    m.insert({"abc", 1});
    m.insert(std::make_pair("bcd", 2));
    m.insert(std::pair<String, int>("cde", 3));
    m["def"] = 4;

    afficher(m);

    // suppression d'un élément méthode erase
    m.erase("bcd");

    afficher2(m);

    // rechercher un élément méthode find
    auto a = m.find("abc");
    if (a != m.end()) {

        Serial.println("Element avec la clé 'abc' trouvé :");
        Serial.print(a->first.c_str());
        Serial.print(" : ");
        Serial.println(a->second);

    } else {
        Serial.println("Pas d'élement avec la clé 'abc'.");
    }

    // rechercher une valeur avec la méthode at
    try{
        int value = m.at("bcd");
        Serial.println(value);       
    }
    catch( std::exception e)
    {
        Serial.println(e.what());
        Serial.println("Clé pas trouvée !");
    }
    
    // rechercher une valeur avec l'opérateur []
    int value = m["xyz"];
    Serial.println(value);
    Serial.println("-----------");
    afficher(m);

}

void loop() {
}

/**
 * @brief fonction pour afficher m 
 *        Utilise un itérateur  
 * @param _m une référence vers une map
 */
void afficher(std::map<String, int> &x) {

    std::map<String, int>::iterator it;

    for (it = x.begin(); it != x.end(); it++) {
        Serial.print(it->first);
        Serial.print(" : ");
        Serial.print(it->second);
        Serial.println();
    }

}

/**
 * @brief nous pouvons également utiliser une boucle for 
 *        basée sur la plage pour parcourir tous les éléments de la map.
 * @param x une référence vers une map
 */
void afficher2(std::map<String, int> &x) {

    for (std::pair<String, int> element : x) {
        Serial.print(element.first.c_str());
        Serial.print(" : ");
        Serial.print(element.second);
        Serial.println();
    }
}