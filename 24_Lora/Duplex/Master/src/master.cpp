/* 
 * File:   duplex.cpp
 * Author: philippe SIMIER Lycée Touchard Le Mans
 * 
 * Created on 28 octobre 2022, 09:46
 * 
 * Envoie un message à interval régulier 
 * et interroge continuellement les nouveaux messages entrants. 
 * Implémente un schéma d'adressage à un octet, avec 0xFF comme adresse de diffusion.
 * 
 * +------------+--------+----+--------+-------------------------+
 * | detination | source | ID | length |       payload           |
 * +------------+--------+----+--------+-------------------------+
 * 
 * pio pkg install --library sandeepmistry/LoRa
 */

#include <Arduino.h>

#include <SPI.h>
#include <LoRa.h>
#include <Afficheur.h>


// LoRa pins
#define LORA_MISO 19
#define LORA_CS   18
#define LORA_MOSI 27
#define LORA_SCK   5
#define LORA_RST  23
#define LORA_IRQ  26 

// Green led 
#define LED 25 

Afficheur *afficheur;


byte id = 0; // count of outgoing messages
byte localAddress = 0x00; // address of this device Master
byte broadcast = 0xFF; // destination to send to broadcast
SemaphoreHandle_t xMutex;

void sendMessage(String outgoing, byte destination);
void onReceive(void * parameter);


void setup() {

    Serial.begin(115200);
    while (!Serial);
    pinMode(LED, OUTPUT);

    SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);
    LoRa.setPins(LORA_CS, LORA_RST, LORA_IRQ);

    afficheur = new Afficheur;

    Serial.println("LoRa Master");

    if (!LoRa.begin(433775000)) { // Initialize LoRa with the specified frequency 433,775 Mhz.
        Serial.println("Starting LoRa failed!");
        while (1);
    }

    LoRa.setSpreadingFactor(12);
    LoRa.setCodingRate4(8);

    Serial.println("Lora Master Setup done");
    afficheur->afficher("Lora", "Master");
    
    xMutex = xSemaphoreCreateMutex();
    xTaskCreate(onReceive, "onReceive", 10000, NULL, 2, NULL);
}

void loop() {

    String requete = "QSA?";
    byte destination = 0x99; // address of slave

    
    afficheur->afficher(String(destination, HEX) + " << " + String(localAddress, HEX), requete);
    Serial.println(String(destination, HEX) + " << " + String(localAddress, HEX) + " : " + requete);
    sendMessage(requete, destination);
    delay(5000);
    
    destination++;
    
    afficheur->afficher(String(destination, HEX) + " << " + String(localAddress, HEX), requete);
    Serial.println(String(destination, HEX) + " << " + String(localAddress, HEX) + " : " + requete);
    sendMessage(requete, destination);
    delay(5000);

}

void sendMessage(String outgoing, byte destination) {

    xSemaphoreTake(xMutex, portMAX_DELAY);
    
    digitalWrite(LED, 1);
    LoRa.beginPacket(); // start packet
    LoRa.write(destination); // add destination address
    LoRa.write(localAddress); // add sender address
    LoRa.write(id); // add message ID
    LoRa.write(outgoing.length()); // add payload length
    LoRa.print(outgoing); // add payload
    LoRa.endPacket(); // finish packet and send it
    id++; // increment message ID
    digitalWrite(LED, 0);
    
    xSemaphoreGive(xMutex);
}

void onReceive(void * parameter) {

    for (;;) {
        xSemaphoreTake(xMutex, portMAX_DELAY);
        if (LoRa.parsePacket()) {
            
            
            // read packet header bytes:
            int recipient = LoRa.read(); // recipient address
            byte sender = LoRa.read(); // sender address
            byte incomingMsgId = LoRa.read(); // incoming msg ID
            byte incomingLength = LoRa.read(); // incoming msg length

            String incoming = "";

            while (LoRa.available()) {
                incoming += (char) LoRa.read();
            }
            
            
            if (incomingLength != incoming.length()) { // check length for error
                Serial.println("error: message length does not match length");
                return; // skip rest of function
            }

            // if the recipient isn't this device or broadcast,
            if (recipient != localAddress && recipient != 0xFF) {
                Serial.println("This message is not for me.");
                return; // skip rest of function
            }

            // if message is for this device, or broadcast, print details:
            
           
            Serial.println("\r\nMessage ID: " + String(incomingMsgId));
            Serial.println("Message length: " + String(incomingLength));
            Serial.println(String(sender, HEX) + " >> " + String(localAddress, HEX) + " : " + incoming);
            Serial.println("RSSI: " + String(LoRa.packetRssi()));
            Serial.println("Snr: " + String(LoRa.packetSnr()));
            Serial.println();
            
            afficheur->afficher(String(sender, HEX) + " >> " + String(localAddress, HEX), incoming);
        }
        xSemaphoreGive(xMutex);
        delay(1);
    }
    vTaskDelete(NULL);
}

