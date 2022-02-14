/* 
 * File:   Afficheur.h
 * Author: philippe Simier Touchard Washington
 *
 * Created on 14 février 2022, 12:18
 */

#ifndef AFFICHEUR_H
#define AFFICHEUR_H

#include <Arduino.h>
#include <SSD1306Wire.h>


class Afficheur : public SSD1306Wire
{
public:
    
    Afficheur();
    virtual ~Afficheur();
    
    void afficher(const String message);
    void afficherFloat(const String message, const float valeur, const String unite);
    
private:

};

#endif /* AFFICHEUR_H */

