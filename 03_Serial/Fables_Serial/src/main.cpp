#include <Arduino.h>
#include <SPIFFS.h>
#include <driver/adc.h>
#include "biblio.h"
#include <HardwareSerial.h>

HardwareSerial com(1); // Déclaration d'une liaison série controlée part UART 1

void setup() {

    pinMode(LED, OUTPUT);
    Serial.begin(115200);
    delay(500);
    // Démarre le système de fichier SPIFFS
    if (!SPIFFS.begin()) {
        Serial.println("Une errreur est apparue pendant le montage de SPIFFS");
        return;
    }
    
    com.begin(9600, SERIAL_8N1, 16, 17); // Rx -> GPIO16 Tx -> GPIO17
    com.println("Setup com done");
    Serial.println("Setup com done");

    envoyerFichier("/fableCorbeau.txt", Serial);

    // Création de la tâche blink 
    xTaskCreate( tacheBlink, "TacheBlink", 10000, NULL, 1, NULL); 
}

void loop() {
    char c = 0;
    int t;

    if (Serial.available() > 0) {
        c = Serial.read();
        switch (c) {
            case 'a':
                envoyerFichier("/fableCorbeau.txt", Serial);
                Serial.write(0x04);
                envoyerFichier("/fableCorbeau.txt", com);
                break;
            case 'b':
                envoyerFichier("/fableCigale.txt", Serial);
                Serial.write(0x04);
                break;
            case 'c':
                envoyerFichier("/fableGrenouille.txt", Serial);
                Serial.write(0x04);
                break;
            case 'd':
                envoyerFichier("/fableTortue.txt", Serial);
                Serial.write(0x04);
                break;
            case 'e':
                envoyerFichier("/fableLeLoup.txt", Serial);
                Serial.write(0x04);
                break;
            case 'f':
                envoyerFichier("/chinois.txt", Serial);
                Serial.write(0x04);
                break;
            case 'g':
                envoyerFichier("/chinois_traduit.txt", Serial);
                Serial.write(0x04);
                break;
            case 'h':
                envoyerFichier("/Beaute.txt", Serial);
                Serial.write(0x04);
                break;    
            case 'i':
                envoyerFichier("/les_hirondelles.txt", Serial);
                Serial.write(0x04);
                break;      
                
            case 'n':
                while(Serial.available() == 0){
                    envoyerFichier("/leMans.nmea", Serial);
                }    
                Serial.write(0x04);
                break;    
            case 't':
                t = hall_sensor_read();
                Serial.printf("H = %d\r\n", t);
                Serial.write(0x04);
                break;
            case '\r':
            case '\n':
                Serial.write(0x04);
                break;
            default:
                Serial.println("Commande inconnue\n");
                Serial.write(0x04);
        }          
    }
}