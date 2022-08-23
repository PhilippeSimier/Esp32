/* 
 * File:   Ressource.cpp
 * Author: philippe SIMIER Lycée Touchard Washington Le Mans
 * 
 * Created on 23 août 2022, 09:49
 */

#include "Ressource.h"

Ressource::Ressource(const std::string & _name):
name(_name)
{
    std::cout << "Ressource " << name << " created" << std::endl;
}

Ressource::Ressource(const Ressource& orig) {
}

Ressource::~Ressource() {
    std::cout << "Resource " << name << " released" << std::endl;
}

void Ressource::doSomething() {
    std::cout << "Resource " << name << " used" << std::endl;
}

