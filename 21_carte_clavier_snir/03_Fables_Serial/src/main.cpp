/* 
 * File:   main.cpp
 * Author: philippe SIMIER Touchard Washington
 * 
 * Programme Pour les TP sur la Liaison série
 * Ce programme écrit un texte sur la liaison série RS232
 * A Chaque touche du clavier correspond un texte différent
 * La touche # permet de tester le fonctionnement des 4 ledq RGB
 * La touche 0 permet de tester le capteur de température & LDR
 * La touche * permet de simuler des trames NMEA délivrées par un capteur GPS
 * 
 * Created on 14 février 2022, 12:05
 */

#include <Arduino.h>
#include <SPIFFS.h>
#include <driver/adc.h>
#include <biblio.h>
#include <HardwareSerial.h>
#include <Afficheur.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <driver/adc.h>




HardwareSerial com(1); // Déclaration d'une liaison série controlée part UART 1
Afficheur *afficheur; // Un afficheur Oled
Led *led;
#define ONE_WIRE_BUS 18   // Gpio 18 sur la carte clavier SNIR

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {

    // Démarre la liaison série 115200 bauds prise USB
    Serial.begin(115200);
    while (!Serial);

    // Démarre le système de fichier SPIFFS
    if (!SPIFFS.begin()) {
        Serial.println("Une errreur est apparue pendant le montage de SPIFFS");
        return;
    }

    // Démarre la deuxième liaison série RS232 9600 bauds Rx -> GPIO16 Tx -> GPIO17
    com.begin(9600, SERIAL_8N1, 16, 17);
    com.println("Setup com série done");
    Serial.println("Setup com série done");

    // Création d'un afficheur Oled
    afficheur = new Afficheur;
    afficheur->afficher("Liaision Série");

    // Création de 4 leds couleurs RVB
    led = new Led(NBLED); // quatre leds;

    // Démarre le temperature sensor
    sensors.begin();
    Serial.print("Trouvé ");
    Serial.print(sensors.getDeviceCount(), DEC);
    Serial.println(" capteur(s).");

    // Configure entrée Analogique pour LDR
    // plage de valeurs de 0 à 4095. (ADC_WIDTH_BIT_12)
    adc1_config_width(ADC_WIDTH_BIT_12);
    //11 dB pour une tension d’entrée de 0.15v à 3.6v sur l'entrée analogique
    adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);

    // Création des tâches blink & Clavier 
    createTaskBlink();
    createTaskClavier();
    createTaskLed1Led2();
}

void loop() {

    uint32_t c;
    float temperatureC;

    if (xTaskNotifyWait(0, ULONG_MAX, &c, 1000) == pdPASS) { // attente une notification de la tâche clavier

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
                afficheur->afficher("Hirondelles");
                envoyerFichier("/les_hirondelles.txt", Serial);
                envoyerFichier("/les_hirondelles.txt", com);
                Serial.write(0x04);
                break;

            case '*':
                afficheur->afficher("trames NMEA");
                do {
                    envoyerFichier("/leMans.nmea", Serial);
                    envoyerFichier("/leMans.nmea", com);
                    xTaskNotifyWait(0, ULONG_MAX, &c, 10);
                } while (c == NO_KEY);
                Serial.write(0x04);
                break;
            case '0':

                do {
                    sensors.requestTemperatures();
                    temperatureC = sensors.getTempCByIndex(0);
                    Serial.print(temperatureC);
                    Serial.println(" ºC : ");
                    afficheur->afficherFloat("Temp ", temperatureC, " °C");
                    delay(2000);
                    // Lecture de l'entrée analogique GPIO 36 => ADC1_CHANNEL_0
                    int value = adc1_get_raw(ADC1_CHANNEL_0);
                    // Mise à l'échelle
                    int y = map(value, 0, 4095, 0, 100);
                    afficheur->afficherFloat("Lum   ", y, " %");
                    delay(2000);
                    xTaskNotifyWait(0, ULONG_MAX, &c, 10);
                } while (c == NO_KEY);


                break;

            case '#':
                afficheur->afficher("test Leds");
                do {
                    chenillard();
                    xTaskNotifyWait(0, ULONG_MAX, &c, 10);
                } while (c == NO_KEY);
                break;

            case '\r':
            case '\n':
                Serial.write(0x04);
                break;
            default:
                Serial.println("Commande inconnue\n");
                Serial.write(0x04);
        }
        afficheur->afficher("Entrer code");
    }
}