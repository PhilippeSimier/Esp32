#include <Arduino.h>
#include <Wire.h>
#include "BME280I2C.h"
#define SERIAL_BAUD 115200

BME280I2C bme;    

void printBME280Data(Stream* client);
                  
void setup()
{
  Serial.begin(SERIAL_BAUD);

  while(!Serial) {} // Wait

  Wire.begin();

  while(!bme.begin())
  {
    Serial.println("Could not find BME280 sensor!");
    delay(1000);
  }

  switch(bme.chipModel())
  {
     case BME280::ChipModel_BME280:
       Serial.println("Found BME280 sensor! Success.");
       break;
     case BME280::ChipModel_BMP280:
       Serial.println("Found BMP280 sensor! No Humidity available.");
       break;
     default:
       Serial.println("Found UNKNOWN sensor! Error!");
  }
}


void loop()
{
   printBME280Data(&Serial);
   delay(500);
}

void printBME280Data( Stream* client)
{
   float temp(NAN), hum(NAN), pres(NAN);

   BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
   BME280::PresUnit presUnit(BME280::PresUnit_Pa);

   bme.read(pres, temp, hum, tempUnit, presUnit);

   client->print("Temp: ");
   client->print(temp);
   client->print(" °"+ String(tempUnit == BME280::TempUnit_Celsius ? 'C' :'F'));
   client->print("\tHumidité: ");
   client->print(hum);
   client->print("%");
   client->print("\tPression: ");
   client->print(pres/100);
   client->println(" hPa");

   delay(1000);
}