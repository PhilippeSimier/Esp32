/* 
 * File:   Arbre.h
 * Author: philippe SIMIER Lycée Touchard Washington
 *
 * Created on 24 août 2022, 20:59
 */

#ifndef ARBRE_H
#define ARBRE_H

#include <iostream>
#include <memory>
#include <Noeud.h>

template <typename ELEMENT>
class Arbre {
    typedef std::shared_ptr<Noeud<ELEMENT>> NoeudPtr;

public:
    Arbre();
    virtual ~Arbre();

    void push(const ELEMENT & value);
    int hauteur();
    int taille();


private:
    NoeudPtr root;

};

// Implementations

template <typename ELEMENT>
Arbre<ELEMENT>::Arbre() :
root() {
}

template <typename ELEMENT>
Arbre<ELEMENT>::~Arbre() {
    std::cout << "Tree released" << std::endl;
}

/**
 * Insert un élément dans l'arbre
 * @param value
 */
template <typename ELEMENT>
void Arbre<ELEMENT>::push(const ELEMENT & value) {

    NoeudPtr node(new Noeud<ELEMENT>(value));
    if (root.get() == nullptr) {
        root = node;
        std::cout << "First insertion of " << value << std::endl;
    } else {
        root->push(node);
    }
}

/**
 * @brief Calcule la hauteur de l'arbre
 * @return int la hauteur de l'arbre
 */
template <typename ELEMENT>
int Arbre<ELEMENT>::hauteur() {
    int h {0};

    if (root.get() != nullptr) {
        h = root->hauteur() -1 ;
    }
    return h;
}

/**
 * 
 * @return int le nombre de noeuds
 */
template <typename ELEMENT>
int Arbre<ELEMENT>::taille() {
    int t {0};
    if (root.get() != nullptr) {
        t = root->taille();
    }
    return t;
}

#endif /* ARBRE_H */

