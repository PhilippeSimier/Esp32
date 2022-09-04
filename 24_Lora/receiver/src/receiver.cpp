/* 
 * File:   receiver.cpp
 * Author: philippe SIMIER Lycée Touchard Washington
 *
 * Created on 4 septembre 2022, 15:39
 *
 * Board
 * LILYGO® TTGO LoRa32 V2.1_1.6 Version 433/868/915Mhz 
 * ESP32 LoRa OLED 0.96 Inch 
 * SD Card 
 * Bluetooth WIFI Wireless Module ESP-32 
 * 
 * pio pkg search "header:LoRa.h"
 * pio pkg install --library sandeepmistry/LoRa
 * 
 */

#include <Arduino.h>
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

void initLoRa() {
    Serial.println("Initializing LoRa....");
    SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);
    LoRa.setPins(LORA_CS, LORA_RST, LORA_IRQ);
    // Start LoRa using the frequency
    int result = LoRa.begin(433775000);
    if (result != 1) {
        Serial.println("Failed to start LoRa network!");
        for (;;);
    }

    Serial.println("LoRa initialized");
    delay(2000);
}

void setup() {

    pinMode(LED, OUTPUT);
    Serial.begin(115200);

    initLoRa();
    Serial.println("Setup done");
}

void loop() {

    String data {""};
    
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
        //received a packet
        Serial.print("Received packet ");

        //read packet
        while (LoRa.available()) {
            data = LoRa.readString();
            Serial.print(data);
            int rssi = LoRa.packetRssi();
            Serial.printf(" RSSI : %d dBm", rssi);
            float snr = LoRa.packetSnr();
            Serial.printf(" SNR : %.2f dB\r\n", snr);
        }
    }
}    

