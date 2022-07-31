/* 
 * File:   list.cpp
 * Author: philippe SIMIER Lycée Touchard le Mans
 *
 * Created on 31 juillet 2022, 10:17
 */

#include <Arduino.h>
#include <list>

using namespace std;

// Les prototypes des fonctions utilisées
void afficher(const list<int> &l);
void afficherInverse(const list<int> &l);

void setup(){
    
    Serial.begin(115200);
    
    list<int> liste;
    
    for (int i=0; i<30; i++){
        liste.push_back(i*2 + 1);
    }

    afficher(liste);
    
    list<int>::iterator it = liste.begin(); // un itérateur sur le premier élément
    advance (it,2);                         // on avance de deux pour pointer sur le troisième
    it = liste.erase(it);                   // on efface le troisième élément
    afficher(liste);                        // on affiche de nouveau
    afficherInverse(liste);                 // on affiche en inversant l'ordre
    
}

void loop(){
    
}

void afficher(const list<int> &l){
    
    for (auto it = l.begin(); it != l.end(); ++it){
        Serial.printf("%d ", *it);
    }
    Serial.print("\r\n");
}

/**
 * @brief  affiche une liste en inversant l'ordre
 * @param l une liste d'entiers
 */
void afficherInverse(const list<int> &l){
    
    for (auto rit = l.rbegin(); rit != l.rend(); ++rit){
        Serial.printf("%d ", *rit);
    }
    Serial.print("\r\n");
}


