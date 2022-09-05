
/* 
 * File:   Ecran.h
 * Author: fmartin
 *
 * Created on 1 février 2022, 23:57
 */

#ifndef ECRAN_H
#define ECRAN_H

#include <SSD1306Wire.h>
#include "font.h"

class Ecran : public SSD1306Wire
{
public:
    Ecran();
    void AfficherMessage(const String _message, const int _ligne = 0);

};

#endif /* ECRAN_H */

