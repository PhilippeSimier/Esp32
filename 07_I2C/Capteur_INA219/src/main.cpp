/* 
 * File:   main.cpp
 * Author: philippe SIMIER Touchard Le Mans
 *
 * Created on 12 mars 2022, 07:56
 * 
 * Bibliothèque :  INA219 Current Sensor
 * installation :  pio lib -g install 160
 */

#include <Arduino.h>
#include <Wire.h>
#include <Battery.h>

Battery *laBatterie; 
float  charge  = 0.0;

void setup(void) {
    Serial.begin(115200);
    laBatterie = new Battery(3000); //  instanciation d'une batterie de 120 mAh
    laBatterie->init(3000);         //  déclaration de la charge initiale 
    laBatterie->setCalibration_32V_1A();   
}

void loop(void) {  
    
    float busvoltage = laBatterie->getBusVoltage_V();
    float i1 = laBatterie->getCurrent_mA();
    float power_mW = laBatterie->getPower_mW();
    

    Serial.print("Bus Voltage:   ");
    Serial.print(busvoltage);
    Serial.println(" V");
    
    Serial.print("Current:       ");
    Serial.print(i1);
    Serial.println(" mA");
    
    Serial.print("Power:         ");
    Serial.print(power_mW);
    Serial.println(" mW");
     
    Serial.print("Charge:        ");
    Serial.print(laBatterie->getCharge());
    Serial.println(" mAh");
    
    delay(1000);
    
    Serial.print("Taux:          ");
    Serial.print(laBatterie->getSOC());
    Serial.println(" %");
    
    delay(1000);

}

