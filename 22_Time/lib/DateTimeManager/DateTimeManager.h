/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   DateTimeManager.h
 * Author: psimier
 *
 * Created on 11 janvier 2024, 17:40
 */

#ifndef DATETIMEMANAGER_H
#define DATETIMEMANAGER_H

#include <Arduino.h>

class DateTimeManager {

public:
    
    DateTimeManager();
    virtual ~DateTimeManager();
    
    int setCurrentTime(unsigned long epoch);
    unsigned long getCurrentTime() const;
    void printCurrentTime(const time_t _time , Stream &flux = Serial) const;
    

private:
    

};

#endif /* DATETIMEMANAGER_H */

