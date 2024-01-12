/* 
 * File:   main.cpp
 * Author: philippe SIMIER
 *
 * Created on 20 mars 2022, 12:24
 * 
 */

#include <Arduino.h>
#include <DateTimeManager.h>


DateTimeManager dtm;

void setup() {

    Serial.begin(115200);
       
    if (dtm.setCurrentTime(946684800) == 0)  // Unixtime for 2000-01-01 00:00:00, useful for initialization
        Serial.println("La mise à jour de la date et de l'heure a réussie");

}

void loop() {

    
    Serial.printf("%u ", dtm.getCurrentTime());
    dtm.printCurrentTime(); 
    
    delay(1000);
}

