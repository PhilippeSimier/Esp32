#include <Arduino.h>
#include <Keypad.h>



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


void setup() {
    Serial.begin(115200);
    pinMode( 2, OUTPUT);   // led builtin
    delay(500);
    Serial.println("\nSetup done");
}

void loop() {
    char key = clavier.getKey();

    if (key) {
        Serial.print(key);
        code.concat(key);
        if (key == '#'){
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
