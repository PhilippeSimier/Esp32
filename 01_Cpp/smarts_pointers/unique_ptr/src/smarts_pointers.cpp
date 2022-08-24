/* 
 * File:   smarts_pointers.cpp
 * Author: philippe SIMIER
 *
 * Created on 23 août 2022, 09:43
 */

#include <Arduino.h>
#include <Ressource.h>

void Process(const RessourcePtr& re);

void setup(){
    
    Serial.begin(115200);
    while (!Serial)
        continue;
    
    RessourcePtr r1( new Ressource("Demo") );
    r1->doSomething();
    Process(r1);
    
    // Création d'une ressource r2 avec le constructeur de copie
    RessourcePtr r2( new Ressource(r1.get()) );
    r2->doSomething();
    
    /*  Les lignes de code suivantes ne se compilent pas
    
    RessourcePtr r2;            // Basé sur nullptr
    r2 = r1;                    // Copie impossible

    RessourcePtr r3( r1 );      // Copie impossible
    */
}

void loop(){
    
}

void Process(const RessourcePtr& re){
    re->doSomething();
}

