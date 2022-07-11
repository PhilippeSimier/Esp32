#include <Arduino.h>
#include <SPIFFS.h>
#include <driver/adc.h>
#include "biblio.h"

void setup() {

    pinMode(LED, OUTPUT);
    Serial.begin(115200);

    // Démarre le système de fichier SPIFFS
    if (!SPIFFS.begin()) {
        Serial.println("Une errreur est apparue pendant le montage de SPIFFS");
        return;
    }

    envoyerFichier("/fableCorbeau.txt");

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
                envoyerFichier("/fableCorbeau.txt");
                Serial.write(0x04);
                break;
            case 'b':
                envoyerFichier("/fableCigale.txt");
                Serial.write(0x04);
                break;
            case 'c':
                envoyerFichier("/fableGrenouille.txt");
                Serial.write(0x04);
                break;
            case 'd':
                envoyerFichier("/fableTortue.txt");
                Serial.write(0x04);
                break;
            case 'e':
                envoyerFichier("/fableLeLoup.txt");
                Serial.write(0x04);
                break;
            case 'f':
                envoyerFichier("/chinois.txt");
                Serial.write(0x04);
                break;
            case 'g':
                envoyerFichier("/chinois_traduit.txt");
                Serial.write(0x04);
                break;
            case 'h':
                envoyerFichier("/Beaute.txt");
                Serial.write(0x04);
                break;    
            case 'i':
                envoyerFichier("/les_hirondelles.txt");
                Serial.write(0x04);
                break;      
                
            case 'n':
                while(Serial.available() == 0){
                    envoyerFichier("/leMans.nmea");
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