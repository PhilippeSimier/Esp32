/* 
 * File:   Battery.h
 * Author: philippe
 *
 * Created on 12 mars 2022, 16:53
 */

#ifndef BATTERY_H
#define BATTERY_H

#include <Wire.h>
#include <Adafruit_INA219.h>


class Battery : public Adafruit_INA219
{
public:
    Battery();
    Battery(const Battery& orig);
    
    void  init(const float _charge);
    float obtenirCharge();
    
private:
    unsigned long t0;
    unsigned long t1;
    float i0;
    float i1;
    float charge;
    float capacite;
    

};

#endif /* BATTERY_H */

