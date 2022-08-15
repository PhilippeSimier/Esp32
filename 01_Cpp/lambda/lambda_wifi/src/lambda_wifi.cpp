/* 
 * File:   lambda_wifi.cpp
 * Author: philippe SIMIER
 * 
 * Gestion des évènements WIFI avec une fonction lambda anonyme
 *
 * Created on 15 août 2022, 18:14
 */

#include <Arduino.h>
#include <WiFi.h>

const char* ssid = "Livebox-5648";
const char* password = "vz9Lcc2RnTTmnDuD4Y";

void setup() {
    Serial.begin(115200);
    while (!Serial)
        continue;

    WiFi.onEvent(
            [](WiFiEvent_t event, arduino_event_info_t info) -> void {
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
                        Serial.print("Wifi station has got IP : ");
                        Serial.println(WiFi.localIP());
                        break;
                    default:
                        break;
                }
            });

    WiFi.begin(ssid, password);
    Serial.println("Setup done ");
}

void loop() {
}




