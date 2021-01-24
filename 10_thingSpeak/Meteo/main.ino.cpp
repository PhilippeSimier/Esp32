#include <WiFi.h>
#include "secrets.h"
#include <ThingSpeak.h> 
#include <Wire.h>
#include <BME280I2C.h>
#include <BH1750.h>


char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

BME280I2C::Settings parametrage(
   BME280::OSR_X1,
   BME280::OSR_X1,
   BME280::OSR_X1,
   BME280::Mode_Forced,
   BME280::StandbyTime_1000ms,
   BME280::Filter_Off,
   BME280::SpiEnable_False,
   BME280I2C::I2CAddr_0x76 // I2C address pour BME 280 Adafruit.
);

BME280I2C bme(parametrage);    
BH1750 eclairement;

// Initialize our values
float temp(NAN), hum(NAN), pres(NAN), lux(NAN);

void setup() {
  // Initialisation liaison série UART0
  Serial.begin(115200);  //Initialize serial
  while (!Serial) {
    ; 
  }
  
  // Initialisation WIFI
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  
  // Initialisation BME280
  Wire.begin();
  while(!bme.begin())
  {
    Serial.println("Could not find BME280 sensor!");
    delay(1000);
  }
  
  // Initialisation BH1750
  while(!eclairement.begin()){
    Serial.println("Could not find BH1750 sensor!");
    delay(1000);
  }
  eclairement.configure(BH1750::CONTINUOUS_HIGH_RES_MODE_2);
  
}

void loop() {

  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }
  
  // Lecture des capteurs
  BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
  BME280::PresUnit presUnit(BME280::PresUnit_hPa);
  
  bme.read(pres, temp, hum, tempUnit, presUnit);
  lux = eclairement.readLightLevel();
  
  
  // set the fields with the values
  ThingSpeak.setField(1, temp);
  ThingSpeak.setField(2, pres);
  ThingSpeak.setField(3, hum);
  ThingSpeak.setField(4, lux);
  
  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  delay(600000); // Wait 600 seconds to update the channel again
}

