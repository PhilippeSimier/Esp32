/* 
 * File:   Arbre_binaire.cpp
 * Author: philippe SIMIER Lycée Touchard Le Mans
 *
 * Created on 24 août 2022, 16:01
 */

#include <Arduino.h>
#include <Ressource.h>
#include <Arbre.h>

using namespace std;

void setup() {

    Serial.begin(115200);
    while (!Serial)
        continue;

    RessourcePtr first( new Ressource("First value"));
    RessourcePtr second(new Ressource("Second value"));
    RessourcePtr third( new Ressource("Third value"));
    RessourcePtr fourth(new Ressource("Fourth value"));
    
    typedef std::shared_ptr< Arbre<RessourcePtr> >   ArbrePtr;
    
    ArbrePtr unArbre( new Arbre<RessourcePtr>() );
    std::cout << "Hauteur = " << unArbre->hauteur() << " Taille = " << unArbre->taille() << std::endl;
    unArbre->push(third);
    std::cout << "Hauteur = " << unArbre->hauteur() << " Taille = " << unArbre->taille() << std::endl;
    unArbre->push(fourth);
    std::cout << "Hauteur = " << unArbre->hauteur() << " Taille = " << unArbre->taille() << std::endl;
    unArbre->push(second);
    std::cout << "Hauteur = " << unArbre->hauteur() << " Taille = " << unArbre->taille() << std::endl;
    unArbre->push(first);
    std::cout << "Hauteur = " << unArbre->hauteur() << " Taille = " << unArbre->taille() << std::endl;
    unArbre->push(first);
    std::cout << "Hauteur = " << unArbre->hauteur() << " Taille = " << unArbre->taille() << std::endl;

}

void loop() {

}



