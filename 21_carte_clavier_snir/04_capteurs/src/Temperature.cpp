/* 
 * File:   Temperature.cpp
 * Author: Philippe SIMIER Lycée Touchard Washington Le Mans
 * 
 * pio pkg install --library "paulstoffregen/OneWire@^2.3.7"
 * pio pkg install --library "milesburton/DallasTemperature@^3.11.0"
 *
 * Created on 12 septembre 2022, 10:52
 */

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 18   // Gpio 18 sur la carte clavier SNIR
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// arrays to hold device address
DeviceAddress insideThermometer;
// prototype
void printAddress(DeviceAddress deviceAddress);


void setup() {

    // Démarre la liaison série 115200 bauds prise USB
    Serial.begin(115200);
    while (!Serial);

    sensors.begin();
    Serial.print("Trouvé ");
    Serial.print(sensors.getDeviceCount(), DEC);
    Serial.println(" capteur(s).");
    if (!sensors.getAddress(insideThermometer, 0))
        Serial.println("Unable to find address for Device 0");
    else {
        Serial.print("Device 0 Address: ");
        printAddress(insideThermometer);
        Serial.println();
    }

}

void loop() {

    sensors.requestTemperatures();
    float temperatureC = sensors.getTempCByIndex(0);
    float temperatureF = sensors.getTempFByIndex(0);
    Serial.print(temperatureC);
    Serial.print(" ºC : ");
    Serial.print(temperatureF);
    Serial.println(" ºF");
    delay(5000);

}

// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

