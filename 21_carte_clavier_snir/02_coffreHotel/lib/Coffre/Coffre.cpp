
/* 
 * File:   Coffre.cpp
 * Author: fmartin
 * 
 * Created on 2 février 2022, 01:25
 */

#include "Coffre.h"

Coffre::Coffre() :
leClavier(touches, brochesEnLigne, brochesEnColonne, LIGNES, COLONNES) {
    ecran = new Ecran;
    Ouvrir();
    PurgerCode();
}

Coffre::~Coffre() {
    delete ecran;
}

void Coffre::Controler() {
    char touche = leClavier.getKey();
    if (touche != NO_KEY) {
        Serial.println(touche);
        switch (etat) {
            case OUVERT:
                switch (touche) {
                    case '*':PurgerCode();
                        break;
                    case '#':
                        if (codeFermeture.length() >= 4) {
                            Fermer();
                        }
                        break;
                    default:
                        AjouterChiffre(touche);
                        break;
                }
                break;
            case FERME:
                switch (touche) {
                    case '*':PurgerCode();
                        break;
                    case '#':
                        if (codeFermeture == codeOuverture) {
                            Ouvrir();
                        }
                        break;
                    default:
                        AjouterChiffre(touche);
                        break;
                }
                break;
        }
    }
}

void Coffre::PurgerCode() {
    switch (etat) {
        case OUVERT:
            codeFermeture.clear();
            break;
        case FERME:
            codeOuverture.clear();
            break;
    }
    ecran->AfficherMessage("Code : ", 1);
}

void Coffre::AjouterChiffre(const char _chiffre) {
    String texte = "Code : ";
    int nbChiffres = 0;

    switch (etat) {
        case OUVERT:
            codeFermeture += _chiffre;
            nbChiffres = codeFermeture.length();
            break;
        case FERME:
            codeOuverture += _chiffre;
            nbChiffres = codeOuverture.length();
            break;
    }
    for (int indice = 0; indice < nbChiffres; indice++) {
        texte += "*";
    }
    ecran->AfficherMessage(texte, 1);
}

void Coffre::Fermer() {
    ecran->AfficherMessage("Porte fermée");
    laSerrure.Verrouiller(); // Commande led D1 pour allumage et commande servo pour verrouillage
    etat = FERME;
    PurgerCode();  // Effacer code
}

void Coffre::Ouvrir() {
    ecran->AfficherMessage("Porte ouverte");
    laSerrure.Deverrouiller();  // Commande led D1 pour extinction et commande servo pour déverrouillage 
    etat = OUVERT;
    PurgerCode();  // Effacer code
}