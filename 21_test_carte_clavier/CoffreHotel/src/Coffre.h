
/* 
 * File:   Coffre.h
 * Author: fmartin
 *
 * Created on 2 février 2022, 01:25
 */

#ifndef COFFRE_H
#define COFFRE_H

#include <Arduino.h>
#include <Keypad.h>
#include "Ecran.h"
#include "Serrure.h"

class Coffre {
public:

    enum ETATS_DU_COFFRE {
        OUVERT = 0,
        FERME
    };

    Coffre();
    ~Coffre();
    void Controler();
    void Ouvrir();
    void Fermer();
    void PurgerCode();
    void AjouterChiffre(const char _chiffre);
    
private:
    String codeOuverture;
    String codeFermeture;
    ETATS_DU_COFFRE etat;
    
    // Relations de composition
    Ecran *ecran;
    Keypad leClavier;
    Serrure laSerrure;
    
    // Configuration des E/S
    static const uint8_t LIGNES = 4;
    static const uint8_t COLONNES = 3;
    char touches[LIGNES * COLONNES]={
        '1', '2', '3',
        '4', '5', '6',
        '7', '8', '9',
        '*', '0', '#'
    };
    
    // Affectation des broches du keypad pour maquette soudée SNIR-ESP32
    // Affectation des E/S GPIO au L0, L1, L2, L3 du clavier
    uint8_t brochesEnLigne[LIGNES]={32, 33, 25, 26};
    // Affectation des E/S GPIO au C0, C1, C2 du clavier
    uint8_t brochesEnColonne[COLONNES]={4, 5, 15};
};

#endif /* COFFRE_H */

