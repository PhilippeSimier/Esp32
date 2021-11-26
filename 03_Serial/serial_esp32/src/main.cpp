#include <Arduino.h>
#include <SPIFFS.h>
#include <driver/adc.h>
#include "biblio.h"

void setup() {

    pinMode(LED, OUTPUT);
    Serial.begin(9600);

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
                envoyerFichier("/les_hirondelles.txt");
                Serial.write(0x04);
                break;
            case 'e':
                envoyerFichier("/Beaute.txt");
                Serial.write(0x04);
                break;
            case 'f':
                envoyerFichier("/essai.txt");
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
            default:
                Serial.println("Commande inconnue\n");
                Serial.write(0x04);

        }
        
            
    }

}

