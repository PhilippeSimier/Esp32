/* 
 * File:   lora.cpp
 * Author: philippe SIMIER
 *
 * Created on 4 septembre 2022, 09:43
 * pio project init --ide netbeans --board ttgo-lora32-v21
 * https://github.com/sandeepmistry/arduino-LoRa
 * 
 * pio pkg install --library sandeepmistry/LoRa
 * 
 */

#include <Arduino.h>

#include <SPI.h>
#include <LoRa.h>


// LoRa pins
#define LORA_MISO 19
#define LORA_CS   18
#define LORA_MOSI 27
#define LORA_SCK   5
#define LORA_RST  23
#define LORA_IRQ  26 

// Green led 
#define LED 25 

int counter = 0;

void setup() {
    
    Serial.begin(115200);
    while (!Serial);
    pinMode(LED, OUTPUT);

    SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);
    LoRa.setPins(LORA_CS, LORA_RST, LORA_IRQ);
    
    Serial.println("LoRa Sender");

    if (!LoRa.begin(433775000)) { // Initialize LoRa with the specified frequency 433,775 Mhz.
        Serial.println("Starting LoRa failed!");
        while (1);
    }
    Serial.println("Setup done");
}

void loop() {
    Serial.print("Sending packet: ");
    digitalWrite(LED,1); // turn the LED
    Serial.println(counter);

    // send packet
    LoRa.beginPacket();   // Démarre la séquence d'envoi d'un paquet.
    LoRa.print("hello "); // Ecriture des données. Chaque paquet peut contenir jusqu'à 255 octets. 
    LoRa.print(counter);
    LoRa.endPacket();     // Termine la séquence d'envoi d'un paquet.

    counter++;
    digitalWrite(LED,0); // turn the LED
    delay(5000);
}




