/* 
 * File:   main.cpp
 * Author: philippe
 *
 * Created on 14 février 2022, 12:05
 */

#include <Arduino.h>
#include <Keypad.h>
#include <Afficheur.h>          // Afficheur SSD1306
#include <Led.h>


const byte ROWS = 4; // Déclaration du nombre de lignes
const byte COLS = 3; // Déclaration du nombre de  colonnes

// Déclaration des caractères sur les touches
char keys[ROWS][COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};

//affectation des GPIO au R1,R2,R3,R4 du clavier
byte rowPins[ROWS] = {32, 33, 25, 26};

//affectation des GPIO au C1,C2,C3 du clavier
byte colPins[COLS] = {4, 5, 15};

Keypad clavier = Keypad((char *) keys, rowPins, colPins, ROWS, COLS);

String code;
String secret = "1234#";
Afficheur *afficheur;
Led *leds;

void setup() {

    Serial.begin(115200);
    pinMode(2, OUTPUT); // led builtin
    delay(500);
    afficheur = new Afficheur;
    leds = new Led(4);  // quatre leds
    
    
    afficheur->afficher("Setup done");
    leds->allumer(BLEU, 3);  // led 3  bleu
}

void loop() {
    char key = clavier.getKey();

    if (key) {
        
        code.concat(key);
        afficheur->afficherMdp(code);

        if (key == '#') {
            if (!code.compareTo(secret)) {
                afficheur->afficher("La porte s'ouvre");
                code = "";
                leds->allumer(VERT); // led 0 verte
                delay(3000);
                leds->eteindre();
                afficheur->afficher("Entrez le code");

            } else {
                afficheur->afficher("Code faux!");
                code = "";
                leds->allumer(ROUGE);  // led 0 rouge
                delay(2000);
                leds->eteindre();
                afficheur->afficher("Entrez le code");
            }
        }
        if (key == '*') {
            code = "";
            afficheur->afficher("Entrez le code");
            // leds->eteindre(3); 
        }
        
    }


}
