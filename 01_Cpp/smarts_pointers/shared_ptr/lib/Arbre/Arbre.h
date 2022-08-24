/* 
 * File:   Arbre.h
 * Author: philippe SIMIER
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

#endif /* ARBRE_H */

