#include <Arduino.h>
#include <SPIFFS.h>
#include <driver/adc.h>
#include <biblio.h>
#include <HardwareSerial.h>
#include <Afficheur.h>
#include <Keypad.h>

HardwareSerial com(1); // Déclaration d'une liaison série controlée part UART 1
Afficheur *afficheur;

#define CONNECTEUR_HAUT   // Définit la position du connecteur clavier en haut ou bas

// Déclaration des caractères sur les touches
char keys[4][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '\n'}
};

//affectation des GPIO aux lignes L0, L1, L2, L3 du clavier
//affectation des GPIO aux colonnes C0, C1, C2 du clavier
#if defined(CONNECTEUR_BAS)  // connecteur en bas

byte rowPins[4]{32, 33, 25, 26};
byte colPins[3]{4, 5, 15};

#else   // connecteur en haut

byte rowPins[4]{26, 25, 33, 32};
byte colPins[3]{15, 5, 4};

#endif

Keypad clavier = Keypad((char *) keys, rowPins, colPins, 4, 3);

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
    com.println("Setup com série done");
    Serial.println("Setup com série done");
    
    afficheur = new Afficheur;
    afficheur->afficher("Liaision Série");
    
    envoyerFichier("/fableCorbeau.txt", Serial);

    // Création de la tâche blink 
    xTaskCreate( tacheBlink, "TacheBlink", 10000, NULL, 1, NULL); 
}

void loop() {
    
    char c = clavier.getKey();
    int t;

    if (c) {

        switch (c) {
            case '1':
                afficheur->afficher("Maître Corbeau");
                envoyerFichier("/fableCorbeau.txt", Serial);
                Serial.write(0x04);
                envoyerFichier("/fableCorbeau.txt", com);
                com.write(0x04);
                break;
            case '2':
                afficheur->afficher("Cigale & Fourmie");
                envoyerFichier("/fableCigale.txt", Serial);
                Serial.write(0x04);
                envoyerFichier("/fableCigale.txt", com);
                com.write(0x04);
                break;
            case '3':
                afficheur->afficher("la Grenouille");
                envoyerFichier("/fableGrenouille.txt", Serial);
                envoyerFichier("/fableGrenouille.txt", com);
                Serial.write(0x04);
                break;
            case '4':
                afficheur->afficher("la Tortue");
                envoyerFichier("/fableTortue.txt", Serial);
                envoyerFichier("/fableTortue.txt", com);
                Serial.write(0x04);
                break;
            case '5':
                afficheur->afficher("le loup");
                envoyerFichier("/fableLeLoup.txt", Serial);
                envoyerFichier("/fableLeLoup.txt", com);
                Serial.write(0x04);
                break;
            case '6':
                afficheur->afficher("C'est du chinois");
                envoyerFichier("/chinois.txt", Serial);
                envoyerFichier("/chinois.txt", com);
                Serial.write(0x04);
                break;
            case '7':
                afficheur->afficher("Chinois traduit");
                envoyerFichier("/chinois_traduit.txt", Serial);
                envoyerFichier("/chinois_traduit.txt", com);
                Serial.write(0x04);
                break;
            case '8':
                afficheur->afficher("Beauté");
                envoyerFichier("/Beaute.txt", Serial);
                envoyerFichier("/Beaute.txt", com);
                Serial.write(0x04);
                break;    
            case '9':
                afficheur->afficher("les hirondelles");
                envoyerFichier("/les_hirondelles.txt", Serial);
                envoyerFichier("/les_hirondelles.txt", com);
                Serial.write(0x04);
                break;      
                
            case '*':
                afficheur->afficher("trames NMEA");
                do{
                    envoyerFichier("/leMans.nmea", Serial);
                    envoyerFichier("/leMans.nmea", com);
                    c = clavier.getKey();
                }while(c == NO_KEY);
                
                Serial.write(0x04);
                break;    
            case '0':
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