/*
 * Programme test Ecran OLED SSD1306
 * pio lib -g install 2978
*/

#include <Arduino.h>
#include <SSD1306Wire.h>
#include <Keypad.h>

const int sda = 4;
const int scl = 15;

SSD1306Wire display(0x3c, sda , scl, GEOMETRY_128_64);

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
byte rowPins[ROWS] = {23, 22, 3, 21};

//affectation des GPIO au C1,C2,C3 du clavier
byte colPins[COLS] = {19, 18, 5};

Keypad clavier = Keypad((char *) keys, rowPins, colPins, ROWS, COLS);

String code;
String secret = "1234#";

void afficher(String message);

void setup() {
    Serial.begin(115200);
    pinMode( 2, OUTPUT);   // led builtin
    display.init();
    display.setFont(ArialMT_Plain_24);
    afficher("Setup done");

}

void loop() {

    char key = clavier.getKey();

    if (key) {
        Serial.print(key);
        code.concat(key);
        afficher(code);

        if (key == '#'){
            if (!code.compareTo(secret)) {
                Serial.println("\nLa porte s'ouvre");
                afficher("La porte s'ouvre");
                code = "";
                digitalWrite(2, HIGH);
                delay(2000);
                digitalWrite(2, LOW);
                afficher("Entrez le code");

            } else {
                Serial.println("\nCode faux !!!");
                afficher("Code faux!");
                code = "";
                delay(2000);
                afficher("Entrez le code");
            }
        }
        if (key == '*'){
            code = "";
            afficher(code);
        }
    }

}

void afficher(String message){
    display.clear();
    display.drawStringMaxWidth(0, 0, 110, message);

    display.display();
}
