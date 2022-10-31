/* 
 * File:   duplex.cpp
 * Author: philippe SIMIER Lycée Touchard Le Mans
 * 
 * Created on 28 octobre 2022, 09:46
 * 
 * écoute les messages et répond aux requetes  
 * pour ce faire interroge continuellement les nouveaux messages entrants. 
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

String payload = "ok ";
byte id = 0; // count of outgoing messages
byte localAddress = 0x99; // address of this device Slave
byte broadcast = 0xFF; // destination to send to broadcast
byte destination = 0x00; // address of Master
long lastSendTime = 0; // last send time
int interval = 6000; // interval between sends

void sendMessage(String outgoing, byte destination);
void onReceive();

void setup() {

    Serial.begin(115200);
    while (!Serial);
    pinMode(LED, OUTPUT);

    SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);
    LoRa.setPins(LORA_CS, LORA_RST, LORA_IRQ);

    afficheur = new Afficheur;
    afficheur->afficher("Lora", "Slave");

    

    if (!LoRa.begin(433775000)) { // Initialize LoRa with the specified frequency 433,775 Mhz.
        Serial.println("Starting LoRa failed!");
        while (1);
    }

    LoRa.setSpreadingFactor(12);
    LoRa.setCodingRate4(8);
    
    Serial.println("LoRa Slave: " + String(localAddress, HEX));
}

void loop() {
    
    // parse for a packet, and call onReceive with the result:
    if (LoRa.parsePacket()){
        onReceive();
    }
    
}

void sendMessage(String outgoing, byte destination) {
    
    digitalWrite(LED,1);
    
    LoRa.beginPacket(); // start packet
    LoRa.write(destination); // add destination address
    LoRa.write(localAddress); // add sender address
    LoRa.write(id); // add message ID
    LoRa.write(outgoing.length()); // add payload length
    LoRa.print(outgoing); // add payload
    LoRa.endPacket(); // finish packet and send it
    id++; // increment message ID
    digitalWrite(LED,0);
}

void onReceive() {
   
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
    Serial.println("\r\nPacket recu");
    Serial.println("Message ID: " + String(incomingMsgId));
    Serial.println("Message length: " + String(incomingLength));
    Serial.println(String(sender, HEX) + " >> " + String(localAddress, HEX) + " : " + incoming);
    afficheur->afficher(String(sender, HEX) + " >> " + String(localAddress, HEX), incoming);
    Serial.println("RSSI: " + String(LoRa.packetRssi()));
    Serial.println("Snr: " + String(LoRa.packetSnr()));
    Serial.println();
    
    // Send réponse to master
    sendMessage(String(LoRa.packetRssi()) + " dBm", sender );
    
    Serial.println("RSSI " + String(LoRa.packetRssi()) + " dBm");
        
    afficheur->afficher(String(sender, HEX) + " << " + String(localAddress, HEX), String(LoRa.packetRssi()) + " dBm");
    Serial.println(String(sender, HEX) + " << " + String(localAddress, HEX) + " : " + String(LoRa.packetRssi()) + " dBm");
}


