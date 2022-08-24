/* 
 * File:   Ressource.h
 * Author: philippe SIMIER Lycée Touchard Le Mans
 *
 * Created on 23 août 2022, 09:49
 */

#ifndef RESSOURCE_H
#define RESSOURCE_H

#include <iostream>
#include <memory>



class Ressource {

public:
    
    Ressource(const std::string & _name);
    Ressource(const Ressource& orig);
    Ressource(const Ressource *orig);
    virtual ~Ressource();
    void doSomething();
    
    bool operator <( const Ressource & autre ) const;
    
private:
    std::string name;
};

typedef std::unique_ptr< Ressource > RessourcePtr;

#endif /* RESSOURCE_H */

