/* 
 * File:   Throwing.cpp
 * Author: philippe SIMIER Lycée Touchard Le Mans
 * 
 * Une classe pour lancer une exception si l'argument passé dans le constructeur vaut 0
 * 
 * Created on 11 août 2022, 18:35
 */

#include "Throwing.h"


Throwing::Throwing(int _arg) :
arg(_arg) {
    
    std::cout << this << " In constructor, arg = " << arg << std::endl;
    
    if (arg == 0) {
        throw std::runtime_error("Exception in constructor");
    }

}

/**
 * @details Le constructeur par copie se base sur un autre objet du même type pour construire l'objet en cours :
 * @param orig
 */
Throwing::Throwing(const Throwing& orig) {
    
    arg = orig.arg;
    std::cout << this << " In copy constructor, arg = " << arg << std::endl;
}

Throwing::~Throwing() {
    
    std::cout << this << " In destructor, arg = " << arg << std::endl;
    
}

