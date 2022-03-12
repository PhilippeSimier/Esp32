/* 
 * File:   main.cpp
 * Author: philippe SIMIER Touchard Le Mans
 *
 * Created on 12 mars 2022, 07:56
 * 
 * Bibliothèque :  INA219 Current Sensor
 * installation :  pio lib -g install 160
 */

#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

void setup(void) {
    Serial.begin(115200);

    Serial.println("Recherche de la puce INA219 !");
    while (!ina219.begin()) {
        delay(3000);
    }
    Serial.println("Puce INA219 trouvée");


}

void loop(void) {

    float shuntvoltage = ina219.getShuntVoltage_mV();
    float busvoltage = ina219.getBusVoltage_V();
    float current_mA = ina219.getCurrent_mA();
    float power_mW = ina219.getPower_mW();
    float loadvoltage = busvoltage + (shuntvoltage / 1000);

    Serial.print("Bus Voltage:   ");
    Serial.print(busvoltage);
    Serial.println(" V");
    Serial.print("Shunt Voltage: ");
    Serial.print(shuntvoltage);
    Serial.println(" mV");
    Serial.print("Load Voltage:  ");
    Serial.print(loadvoltage);
    Serial.println(" V");
    Serial.print("Current:       ");
    Serial.print(current_mA);
    Serial.println(" mA");
    Serial.print("Power:         ");
    Serial.print(power_mW);
    Serial.println(" mW");
    Serial.println("");

    delay(2000);

}

