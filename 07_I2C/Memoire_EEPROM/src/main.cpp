/* 
 * File:   main.cpp
 * Author: philippe SIMIER
 *
 * Created on 17 octobre 2022, 14:55
 */

#include <Arduino.h>

#include <Wire.h>  // bibliothèque i2c

#define adresse_EEPROM 0x50    //Addresse i2c de l'EEPROM
#define adresseMax 128 // taille de l'EEPROM (nombre d'octets)

int adresse = 0;

void setup(void) {
    
    Serial.begin(115200);
    Wire.begin();
    delay(100);

    Serial.println("START WRITING"); //Writing to serial
    int address = 0; //Initializing Variable
    int loop = 0;
    int data = 0;
    
    for (loop = 0; loop < 1024; loop++) //Running cyclically writing 1024 memory location
    {

        Wire.beginTransmission(0x50); //Start sending control byte specifying write request  memory location
        Wire.write(highByte(address)); //Sending 2 byte containing address
        Wire.write(lowByte(address)); //Sending 2 byte containing address
        Wire.write(byte(data)); // Writing byte in memory location previously selected
        Wire.endTransmission(); //Ending Transmission
        data++; //Start value of data increment
        if (data == 256) //If data variable reaches to 256 reset its value to 0
            data = 0;
        address++; //Start increment address value
        delay(5); // Wait 5 miliseconds to end the operation writing to memory
    }

    Serial.println("WRITING END");
    delay(500); //Delayed to 1/2 second
    Serial.println("START READING");
    address = 0;

    for (loop = 0; loop < 1024; loop++) {

        Wire.beginTransmission(0x50); //Send control byte specifying write request to 0x50  memory
        Wire.write(highByte(address));
        Wire.write(lowByte(address));
        Wire.endTransmission();
        address++; //Start increment address value
        Wire.requestFrom(0x50, 1); // start request byte at 0x50
        while (Wire.available()) {
 
            Serial.print(":");
            byte c = Wire.read();
            Serial.println(c); // Sendind the data to the serial monitor 
        }
    }

    delay(1000);


}

void loop() {

}


