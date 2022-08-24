/* 
 * File:   Ressource.cpp
 * Author: philippe SIMIER Lycée Touchard Washington Le Mans
 * 
 * Created on 23 août 2022, 09:49
 */

#include "Ressource.h"

/**
 * Constructeur
 * @param _name
 */
Ressource::Ressource(const std::string & _name) :
name(_name) {
    std::cout << "Ressource " << name << " created" << std::endl;
}

/**
 * Constructeur de copie à partir d'une référence
 * @param orig une référence sur une ressource
 */
Ressource::Ressource(const Ressource& orig) {
    name = orig.name + "_copied";
    std::cout << "Ressource " << name << " created" << std::endl;
}

/**
 * Constructeur de copie à partir d'un pointeur
 * @param orig un pointeur sur une ressource
 */
Ressource::Ressource(const Ressource *orig) {
    name = orig->name + "_copied";
    std::cout << "Ressource " << name << " created" << std::endl;
}


/**
 * Destructeur
 */
Ressource::~Ressource() {
    std::cout << "Ressource " << name << " released" << std::endl;
}

/**
 * Une méthode pour faire quelque chose
 */
void Ressource::doSomething() {
    std::cout << "Ressource " << name << " used" << std::endl;
}

/**
 * Opérateur  < inférieur
 * @param other
 * @return un booléen true ou false
 */
bool Ressource::operator<(const Ressource & autre) const {
    return this->name < autre.name;
}

