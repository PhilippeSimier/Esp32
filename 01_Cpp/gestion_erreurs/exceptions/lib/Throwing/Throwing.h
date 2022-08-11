/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   Throwing.h
 * Author: philippe
 *
 * Created on 11 août 2022, 18:35
 */

#ifndef THROWING_H
#define THROWING_H

#include <iostream>

class Throwing {
    
public:
    Throwing(int _arg);
    Throwing(const Throwing& orig);
    virtual ~Throwing();
    
private:
    
    int arg;

};

#endif /* THROWING_H */

