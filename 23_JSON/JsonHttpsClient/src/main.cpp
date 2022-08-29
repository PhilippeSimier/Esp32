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

bool networkOk {false};

void setup() {

    Serial.begin(115200);


    WiFi.onEvent(
            [&](WiFiEvent_t event, arduino_event_info_t info) mutable -> void {
                switch (event) {
                    case ARDUINO_EVENT_WIFI_READY:
                        Serial.println("Wifi ready");
                        break;
                    case ARDUINO_EVENT_WIFI_STA_START:
                        Serial.println("Wifi station start");
                        break;
                    case ARDUINO_EVENT_WIFI_STA_CONNECTED:
                        Serial.println("Wifi station connected");
                        break;
                    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
                        Serial.print("Wifi station has got IP  : ");
                        Serial.println(WiFi.localIP());
                        Serial.print("Adresse IP de la gateway : ");
                        Serial.println(WiFi.gatewayIP());
                        networkOk = true;
                        break;
                    default:
                        break;
                }
            });


    WiFi.begin(ssid, password); // On se connecte


}

void loop() {
    // On se place dans le rôle du  client en utilisant HTTPClient
    HTTPClient http;
    
    if (networkOk) {
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
                    auto temp = mesure["TemperatureC"].as<const char*>();
                    Serial.println(temp);
                } else {
                    Serial.println("Problème capteur BME280");
                }
            }


        } else {
            Serial.printf("Error on HTTP request code : %d\n", httpCode);
        }

        http.end();
    }else{
            Serial.println("Pas de réseau");
    }
    delay(10000);

}





