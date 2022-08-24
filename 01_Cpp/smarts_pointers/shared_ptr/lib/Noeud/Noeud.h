/* 
 * File:   Noeud.h
 * Author: philippe SIMIER
 *
 * Created on 24 août 2022, 21:04
 */

#ifndef NOEUD_H
#define NOEUD_H

#include <iostream>
#include <memory>


template <typename ELEMENT>
class Noeud {
    
typedef std::shared_ptr<Noeud<ELEMENT>> NoeudPtr;    

public:
    
    Noeud(const ELEMENT & value);
    virtual ~Noeud();
    
    void push(NoeudPtr node);

private:
    NoeudPtr leftNode;
    ELEMENT value;
    NoeudPtr rightNode;

};


// Implementation de la classe Noeud

template <typename ELEMENT>
Noeud<ELEMENT>::Noeud(const ELEMENT & value) :
leftNode(),
value(value),
rightNode()
{
    std::cout << "Node " << value << " created" << std::endl;
}

template <typename ELEMENT>
Noeud<ELEMENT>::~Noeud() {
    std::cout << "Node " << value << " released" << std::endl;
}

template <typename ELEMENT>
void Noeud<ELEMENT>::push( NoeudPtr node ) {
    if (node->value < value) {
        if (leftNode.get() == nullptr) {
            leftNode = node;
            std::cout << "Insert on left of " << value << std::endl;
        } else {
            leftNode->push(node);
        }
    } else {
        if (rightNode.get() == nullptr) {
            rightNode = node;
            std::cout << "Insert on right of " << value << std::endl;
        }
        else {
            rightNode->push(node);
        }
    }
}


#endif /* NOEUD_H */

