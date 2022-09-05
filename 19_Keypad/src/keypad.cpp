/* 
 * File:   keypad.cpp
 * Author: Philippe Simier Lycée touchard Washington Le Mans
 *
 * Created on 1 septembre 2022, 10:50
 */

#include <Arduino.h>
#include <Keypad.h>

#define CONNECTEUR_BAS   // Définit la position du connecteur clavier en haut ou bas

// Déclaration des caractères sur les touches
char keys[4][3]{
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};

#if defined(CONNECTEUR_BAS)  // connecteur en bas

//affectation des GPIO aux lignes L0, L1, L2, L3 du clavier 
byte rowPins[4]{32, 33, 25, 26};
//affectation des GPIO aux colonnes C0, C1, C2 du clavier 
byte colPins[3]{4, 5, 15};

#else   // connecteur en haut

byte rowPins[4]{26, 25, 33, 32};
byte colPins[3]{15, 5, 4};

#endif

Keypad clavier = Keypad( (char *) keys, rowPins, colPins, 4, 3);

String code;
String secret{"1234#"};

void setup() {

    Serial.begin(115200);
    pinMode(2, OUTPUT); // led builtin
    delay(500);
    Serial.println("\nSetup done");

}

void loop() {
    char key = clavier.getKey();

    if (key) {
        Serial.print(key);
        code.concat(key);
        if (key == '#') {
            if (!code.compareTo(secret)) {
                Serial.println("\nLa porte s'ouvre");
                code = "";
                digitalWrite(2, HIGH);
                delay(2000);
                digitalWrite(2, LOW);

            } else {
                Serial.println("\nCode faux !!!");
                code = "";

            }
        }
    }

}