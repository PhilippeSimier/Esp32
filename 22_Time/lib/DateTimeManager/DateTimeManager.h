/* 
 * File:   DateTimeManager.h
 * Author: Philippe SIMIER Lycée Touchard le Mans
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
    bool synchroniser();
    

private:
    
    String ntpServerName;
    String timeZone;
    

};

#endif /* DATETIMEMANAGER_H */

