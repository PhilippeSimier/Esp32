#include <Arduino.h>
#include <Wire.h>
#include <BME280.h>
#include <BME280I2C.h>
#include <BH1750.h>
#define SERIAL_BAUD 115200

BME280I2C::Settings parametrage(
   BME280::OSR_X1,
   BME280::OSR_X1,
   BME280::OSR_X1,
   BME280::Mode_Forced,
   BME280::StandbyTime_1000ms,
   BME280::Filter_Off,
   BME280::SpiEnable_False,
   BME280I2C::I2CAddr_0x77 // I2C address pour BME 280 Adafruit.
);

BME280I2C bme(parametrage);    
BH1750 eclairement;

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
  
  while(!eclairement.begin()){
    Serial.println("Could not find BH1750 sensor!");
    delay(1000);
  }
  eclairement.configure(BH1750::CONTINUOUS_HIGH_RES_MODE_2);
  
  
}


void loop()
{
   printBME280Data(&Serial);
   delay(500);
}

void printBME280Data( Stream* client)
{
   float temp(NAN), hum(NAN), pres(NAN), lux(NAN);

   BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
   BME280::PresUnit presUnit(BME280::PresUnit_Pa);

   bme.read(pres, temp, hum, tempUnit, presUnit);
   lux = eclairement.readLightLevel();

   client->print("Temp: ");
   client->print(temp);
   client->print(" °C");
   client->print("\tHumidité: ");
   client->print(hum);
   client->print("%");
   client->print("\tPression: ");
   client->print(pres/100);
   client->print(" hPa");
   client->print("\tEclairement: ");
   client->print(lux);
   client->println(" Lux");

   delay(1000);
}