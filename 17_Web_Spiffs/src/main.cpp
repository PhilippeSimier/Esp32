/* 
 * File:   main.cpp
 * Author: philippe
 *
 * Created on 11 novembre 2021, 20:12
 */

#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include "definition.h"

// Replace with your network credentials
const char* ssid = SSID;
const char* password = PSWD;

// Création d'un serveur web asynchrone (écoute sur le port 80)
AsyncWebServer server(80);

// Remplace le champ STATE par l'état de la led On ou Off

String processor(const String& var) {

    String retour = "Off";
    Serial.print(var);
    Serial.print(" : ");

    if (var == "STATE") {
        if (digitalRead(LED)) 
            retour = "On";       
    }
    Serial.println(retour);
    return retour;
}

void setup() {

    Serial.begin(115200);
    pinMode(LED, OUTPUT);

    // Initialise SPIFFS
    if (!SPIFFS.begin(true)) {
        Serial.println("Une erreur est apparue pendant le montage SPIFFS");
        return;
    }

    // Connection du Wi-Fi
    WiFi.begin(ssid, password);
    Serial.print("Tentative de connexion...");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println("\n");
    Serial.println("Connexion établie!");

    Serial.print("Adresse IP: ");
    Serial.println(WiFi.localIP());

    // Request GET /  -> envoie du fichier /index.html 
    server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
        request->send(SPIFFS, "/index.html", String(), false, processor);
    });

    // Request GET /style.css -> envoie du fichier /style.css
    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
        request->send(SPIFFS, "/style.css", "text/css");
    });

    // Request GET /on -> allumage led & envoie du fichier /index.html
    server.on("/on", HTTP_GET, [](AsyncWebServerRequest * request) {
        digitalWrite(LED, HIGH);
        request->send(SPIFFS, "/index.html", String(), false, processor);
    });

    // Request GET /off -> extinction led & envoie du fichier /index.html
    server.on("/off", HTTP_GET, [](AsyncWebServerRequest * request) {
        digitalWrite(LED, LOW);
        request->send(SPIFFS, "/index.html", String(), false, processor);
    });

    // Démarrage du serveur
    server.begin();
}

void loop() {

}

