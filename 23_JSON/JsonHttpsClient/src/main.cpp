/* 
 * File:   main.cpp
 * Author: philippe SIMIER Lycée touchard Le Mans
 * 
 * This example shows how to parse a JSON document in an https response.
 *
 * Created on 28 août 2022, 18:13
 */

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "constantes.h"

void setup() {

    Serial.begin(115200);

    Serial.print("Connexion au WiFi ");
    Serial.println(ssid);

    WiFi.begin(ssid, password); // On se connecte
    while (WiFi.status() != WL_CONNECTED) { // On attend
        delay(500);
        Serial.print(".");
    }

    // Affichage des paramètres  
    Serial.println("\r\nWiFi connecté");
    Serial.print("Adresse IP du module ESP32 : ");
    Serial.println(WiFi.localIP());
    Serial.print("Adresse IP de la gateway : ");
    Serial.println(WiFi.gatewayIP());





}

void loop() {
    // On se place dans le rôle du  client en utilisant HTTPClient
    HTTPClient http;

    http.begin("https://philippes.ddns.net/cgi-bin/bme280Json", root_ca); //Specify the URL and certificate
    int httpCode = http.GET(); //Make the request

    if (httpCode == 200) { // le code de status doit être OK 200

        String mesureJson = http.getString();
        // Serial.println(payload);

        const size_t capacity = 256;
        DynamicJsonDocument mesure(capacity);

        DeserializationError error = deserializeJson(mesure, mesureJson);
        // Serial.printf("Memory usage : %d\n", mesure.memoryUsage()); 
        if (error) {
            Serial.print("deserializeJson() failed: ");
            Serial.println(error.f_str());
        } else {
            bool ok = mesure["OK"];
            if (ok) {
                auto temp  = mesure["TemperatureC"].as<const char*>();
                Serial.println(temp);
            }else{
                Serial.println("Problème capteur BME280");
            }
        }


    } else {
        Serial.printf("Error on HTTP request code : %d\n", httpCode);
    }

    http.end();
    delay(10000);

}





