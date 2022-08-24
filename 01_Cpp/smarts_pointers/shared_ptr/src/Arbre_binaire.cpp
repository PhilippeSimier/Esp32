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
    unArbre->push(first);
    unArbre->push(second);
    unArbre->push(third);
    unArbre->push(fourth);



}

void loop() {

}



