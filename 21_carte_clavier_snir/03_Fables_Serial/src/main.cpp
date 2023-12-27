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
#include <esp32_snir.h>



HardwareSerial com(1); // Déclaration d'une liaison série controlée part UART 1
Afficheur *afficheur; // Un afficheur Oled
Led *led;


OneWire oneWire(TEMP);
DallasTemperature sensors(&oneWire);
String message;

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
    com.begin(9600, SERIAL_8N1, RX_RS232, TX_RS232);
    Serial.println("Setup com série done");

    // Configure Le SW en entrée
    pinMode(SW, INPUT);
    // Création d'un afficheur Oled
    afficheur = new Afficheur;

    if (digitalRead(SW))
        afficheur->afficher("Liaision Série");
    else
        afficheur->afficher("Clavier Série");

    // Création de 4 leds couleurs RVB
    led = new Led(NB_PIXELS); // quatre leds RGB;
    led->setDelay(DELAY);

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
    message = "";
}

void loop() {

    uint32_t c;
    float temperatureC;

    if (xTaskNotifyWait(0, ULONG_MAX, &c, 10) == pdPASS) { // attente une notification de la tâche clavier
        if (digitalRead(SW)) {
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
                    Serial.write(0x04);
                    envoyerFichier("/fableGrenouille.txt", com);
                    com.write(0x04);
                    break;
                case '4':
                    afficheur->afficher("la Tortue");
                    envoyerFichier("/fableTortue.txt", Serial);
                    Serial.write(0x04);
                    envoyerFichier("/fableTortue.txt", com);
                    com.write(0x04);
                    break;
                case '5':
                    afficheur->afficher("le loup");
                    envoyerFichier("/fableLeLoup.txt", Serial);
                    Serial.write(0x04);
                    envoyerFichier("/fableLeLoup.txt", com);
                    com.write(0x04);
                    break;
                case '6':
                    afficheur->afficher("C'est du chinois");
                    envoyerFichier("/chinois.txt", Serial);
                    Serial.write(0x04);
                    envoyerFichier("/chinois.txt", com);
                    com.write(0x04);
                    break;
                case '7':
                    afficheur->afficher("Chinois traduit");
                    envoyerFichier("/chinois_traduit.txt", Serial);
                    Serial.write(0x04);
                    envoyerFichier("/chinois_traduit.txt", com);
                    com.write(0x04);
                    break;
                case '8':
                    afficheur->afficher("Beauté");
                    envoyerFichier("/Beaute.txt", Serial);
                    Serial.write(0x04);
                    envoyerFichier("/Beaute.txt", com);
                    com.write(0x04);
                    break;
                case '9':
                    afficheur->afficher("Hirondelles");
                    envoyerFichier("/les_hirondelles.txt", Serial);
                    Serial.write(0x04);
                    envoyerFichier("/les_hirondelles.txt", com);
                    com.write(0x04);
                    break;

                case '*':
                    afficheur->afficher("trames NMEA");
                    do {
                        envoyerFichier("/leMans.nmea", Serial);
                        envoyerFichier("/leMans.nmea", com);
                        xTaskNotifyWait(0, ULONG_MAX, &c, 10);
                    } while (c == NO_KEY);
                    Serial.write(0x04);
                    com.write(0x04);
                    break;
                case '0':

                    do {
                        sensors.requestTemperatures();
                        temperatureC = sensors.getTempCByIndex(0);

                        Serial.print(temperatureC);
                        Serial.print(" ºC : ");
                        com.print(temperatureC);
                        com.print(" °C : ");

                        afficheur->afficherFloat("Temp ", temperatureC, " °C");
                        delay(1000);
                        // Lecture de l'entrée analogique GPIO 36 => ADC1_CHANNEL_0
                        int value = adc1_get_raw(ADC1_CHANNEL_0);
                        // Mise à l'échelle
                        int y = map(value, 0, 4095, 0, 100);
                        afficheur->afficherFloat("Lum   ", y, " %");
                        Serial.print(y);
                        Serial.print(" %\n");
                        com.print(y);
                        com.print(" %\n");

                        delay(1000);
                        xTaskNotifyWait(0, ULONG_MAX, &c, 10);
                    } while (c == NO_KEY);


                    break;

                case '\n':
                    afficheur->afficher("Test Leds");
                    do {
                        chenillard(NB_PIXELS + 1);
                        xTaskNotifyWait(0, ULONG_MAX, &c, 10);
                    } while (c == NO_KEY);
                    break;

                default:
                    Serial.println("Commande inconnue\n");
                    Serial.write(0x04);
            }
            afficheur->afficher("Entrer code");
        }else{
            com.write(c);
            Serial.write(c);
            afficheur->afficher(c);
        }
    }

    // Affichage sur l'ecran OLED des caratères reçus sur Serial
    // Bridge entre com et Serial
    char car;

    if (Serial.available() > 0) {
        car = Serial.read();
        afficheur->afficher(car);
        com.write(car);
    }

    if (com.available() > 0) {
        car = com.read();
        Serial.write(car);
    }

}