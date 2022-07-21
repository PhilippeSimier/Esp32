/**
 * 
 * File:   main.cpp
 * Author: philippe
 * 
 * Attention 
 * non compilable après les version 3.5.0 d'espressif
 * platformio.ini doit contenir
 * 
 * platform = espressif32 @ ~3.5.0
 * 
 * Created on 5 novembre 2021, 17:42
 */
 
#include <Arduino.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <WebServer.h>

const char *ssid = "ESP32AP";
const char *password = "touchard72";

WebServer server(80);

void pageIndex() {
    Serial.println("requete GET /");
    server.send(200, "text/html", "<h1>Cela fonctionne tres bien</h1>");
}

void afficherListeClients(WiFiEvent_t event, WiFiEventInfo_t info) {
    delay(500); // permet d'attendre un peu l'attribution d'une adresse par dhcp
    wifi_sta_list_t wifi_sta_list;
    tcpip_adapter_sta_list_t adapter_sta_list;

    memset(&wifi_sta_list, 0, sizeof (wifi_sta_list));
    memset(&adapter_sta_list, 0, sizeof (adapter_sta_list));

    esp_wifi_ap_get_sta_list(&wifi_sta_list);
    tcpip_adapter_get_sta_list(&wifi_sta_list, &adapter_sta_list);

    for (int i = 0; i < adapter_sta_list.num; i++) {

        tcpip_adapter_sta_info_t station = adapter_sta_list.sta[i];

        Serial.print("station nr ");
        Serial.println(i);

        Serial.print("MAC: ");

        for (int i = 0; i < 6; i++) {

            Serial.printf("%02X", station.mac[i]);
            if (i < 5)Serial.print(":");
        }

        Serial.print("\nIP: ");
        Serial.println(ip4addr_ntoa(&(station.ip)));
        Serial.println("-----------");
    }
}

void afficherDeconnexion(WiFiEvent_t event, WiFiEventInfo_t info) {
    Serial.println("Déconnexion station");
    Serial.print("MAC: ");
    for (int i = 0; i < 6; i++) {
        Serial.printf("%02X", info.sta_connected.mac[i]);
        if (i < 5)Serial.print(":");
    }
    Serial.println("\n------------");
}

void setup() {

    Serial.begin(115200);
    WiFi.softAP(ssid, password);
    WiFi.onEvent(afficherListeClients, SYSTEM_EVENT_AP_STACONNECTED);
    WiFi.onEvent(afficherDeconnexion, SYSTEM_EVENT_AP_STADISCONNECTED);

    Serial.println();
    Serial.print("IP address: ");
    Serial.println(WiFi.softAPIP());

    server.on("/", pageIndex);
    server.begin();

}

void loop() {
    server.handleClient();
}