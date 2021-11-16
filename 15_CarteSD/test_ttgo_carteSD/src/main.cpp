/* 
 * File:   main.ino.cpp
 * Author: philippe SIMIER Touchard Washington 
 *
 * Created on 30 octobre 2021, 14:13
 * 
 * Attention retirer la carte SD pour uploader le programme
 */
#include <Arduino.h>

#include <SPI.h>
#include <SD.h>
#include <FS.h>

#include <MsdCard.h>

// Affectation des broches SPI carte SD pour TTGO-T1
static const uint8_t SD_SS    = 13;
static const uint8_t SD_MOSI  = 15;
static const uint8_t SD_MISO  = 2;
static const uint8_t SD_SCK   = 14;


MsdCard carteSD(SD_SCK, SD_MISO, SD_MOSI, SD_SS);  

void setup() {

    Serial.begin(115200);
    while (!Serial) {}
    carteSD.begin();
 
}

void loop(void) {

    char c = 0;
    
    if (Serial.available() > 0) {
        c = Serial.read();
        switch (c) {
            case 'l':
                carteSD.ls("/");
                break;
                
            case 'w':
                Serial.println("Write");
                
                carteSD.fwrite("/unFichier", "une ligne de texte\r\n"); 
                break;
                
            case 'a':
                Serial.println("Append");
                
                carteSD.fputs("/unFichier", "une autre ligne de texte\r\n"); 
                break;    
            
            case 'm':
                carteSD.mkdir("/repertoire");
                break;
                
            case 'r':
                carteSD.rmdir("/repertoire");
                break;
                
            case 'n':
                Serial.println("Write dans repertoire");
                
                carteSD.fwrite("/repertoire/unFichier", "une ligne de texte\r\n"); 
                break;  
                
            case 'v':
                carteSD.mv("/repertoire/unFichier", "/unAutreFichier2");
                break;
                
            case 'b':
                carteSD.fread("/main.ino.cpp");
                break;
                
            
        }
    }
}
