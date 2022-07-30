/* 
 * File:   main.cpp
 * Author: philippe SIMIER Touchard Washington
 * 
 * Digicode pour le contrôle d'accès d'un immeuble 
 * 
 * Created on 14 février 2022, 12:05
 */

#include <Arduino.h>
#include <HardwareSerial.h>
#include <Keypad.h>
#include <Afficheur.h>          // Afficheur SSD1306
#include <Led.h>                // Les quatre Leds RGB



// Déclaration des caractères sur les touches
char keys[4][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '\n'}
};

//affectation des GPIO aux lignes L0, L1, L2, L3 du clavier
byte rowPins[4] = {32, 33, 25, 26};

//affectation des GPIO aux colonnes C0, C1, C2 du clavier
byte colPins[3] = {4, 5, 15};

Keypad clavier = Keypad((char *) keys, rowPins, colPins, 4, 3);

String code;
String secret = "1234\n";
Afficheur *afficheur;
Led *led;

HardwareSerial com(1); // Déclaration d'une liaison série controlée part UART 1

void blinkLedBleu(void * parameter);   // Tâche pour faire clignoter la led bleu en position 3
void boutonPoussoir(void * parameter); // Tâche pour ouvrir la porte avec les boutons poussoirs 

void setup() {

    Serial.begin(115200);
    com.begin(9600, SERIAL_8N1, 16, 17); // Rx -> GPIO16 Tx -> GPIO17
    com.println("Setup com done");

    afficheur = new Afficheur;
    led = new Led(4); // quatre leds
    
    // Création des tâches blink et BP
    xTaskCreate(blinkLedBleu, "blinkLedBleu", 10000, NULL, 1, NULL);
    xTaskCreate(boutonPoussoir, "boutonpoussoir", 10000, NULL, 1, NULL);

    afficheur->afficher("Setup done");

}

void loop() {
    char key = clavier.getKey();

    if (key) {

        code.concat(key);
        afficheur->afficherMdp(code);

        if (key == '\n') {
            if (!code.compareTo(secret)) {
                afficheur->afficher("La porte s'ouvre");
                com.println("La porte s'ouvre");
                code = "";
                led->allumer(VERT); // led 0 verte
                delay(3000);
                led->eteindre();
                afficheur->afficher("Entrez le code");

            } else {
                afficheur->afficher("Code faux!");
                com.println("Code faux " + code);
                code = "";
                led->allumer(ROUGE); // led 0 rouge
                delay(2000);
                led->eteindre();
                afficheur->afficher("Entrez le code");
            }
        }
        if (key == '*') {
            code = "";
            afficheur->afficher("Entrez le code");
        }

    }


}

// Tâche pour faire clignoter la led bleu en quatrième position

void blinkLedBleu(void * parameter) {

    while (1) {
        led->allumer(BLEU, 3);
        delay(200);
        led->eteindre(3);
        delay(1000);
        vTaskDelay(1); //indispensable car sinon guru ?!
    }

    vTaskDelete(NULL);
}

// Tâche scrutation des Boutons Pousoirs dans le couloir (Automate)
// La porte s'ouvre si bp1 actionné ou bp2 et bp3 actionnés simultanément

void boutonPoussoir(void * parameter) {

    // setup    
    pinMode(39, INPUT); // BP1
    pinMode(34, INPUT); // BP2
    pinMode(35, INPUT); // BP3

    // loop
    while (1) {
        // traitement Préliminaire lecture des boutons poussoirs
        bool bp1 = !digitalRead(39);
        bool bp2 = !digitalRead(34);
        bool bp3 = !digitalRead(35);
        
        // Traitement combinatoire  
        
        bool porte = (bp1 || (bp2 && bp3));
        
        // traitement postérieur Ecriture des sorties
        if (porte){
            com.println("La porte s'ouvre");
            led->allumer(VERT); // led 0 verte
            delay(3000);
            led->eteindre();
            
        }
        vTaskDelay(1); //indispensable car sinon guru ?!
    }
    
    vTaskDelete(NULL);

}
