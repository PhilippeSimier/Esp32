/* 
 * File:   main.ino.cpp
 * Author: philippe SIMIER Touchard Washington 
 *
 * Created on 30 octobre 2021, 14:13
 */
#include <Arduino.h>

#include <SPI.h>
#include <SD.h>
#include <FS.h>

#include <MsdCard.h>

MsdCard carteSD;  // Avec l'affectation des broches standard de la liaison SPI de l'esp32 (carte ruche)

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