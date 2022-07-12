#include <WiFi.h>
#include <WebServer.h>
#include <Timer.h>
#include <header.h>

const char* ssid = SECRET_SSID;
const char* password = SECRET_PASS;

WebServer server(80);
Timer tempo(false);
bool etat = false;

String construirePage() {
    int value = analogRead(InAna);
    String page = "<html><head>";
    page += "<title>Site ESP32</title></head>";
    page += "<body><h1>Valeur : ";
    page += value;
    page += "</h1>";
    page += "</body></html>";
    return page;
}

void pageIndex() {
    Serial.println("requete GET /");
    server.send(200, "text/html", construirePage());

}

void pageInLine() {
    Serial.println("requete GET /inline");
    server.send(200, "text/plain", "it's works as well");
}

void handleNotFound() {

    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    for (uint8_t i = 0; i < server.args(); i++) {
        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    server.send(404, "text/plain", message);
}

void setup() {
    Serial.begin(115200);
    pinMode(LED, OUTPUT);

    delay(100);

    Serial.print("Connexion au WiFi ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password); // connection 

    while (WiFi.status() != WL_CONNECTED) { // On attend
        delay(500);
        Serial.print(".");
    }

    Serial.println(""); // affichage des paramètres 
    Serial.println("WiFi connecté");
    Serial.print("Adresse IP du module EPC: ");
    Serial.println(WiFi.localIP());
    Serial.print("Adresse IP de la gateway : ");
    Serial.println(WiFi.gatewayIP());

    server.on("/", pageIndex); // associe une fonction pour la méthode http GET /
    server.on("/inline", pageInLine);
    server.onNotFound(handleNotFound);

    server.begin();
    Serial.println("Serveur HTTP en fonction");
    tempo.lancer(1000);
}

void loop() {

    server.handleClient();
    if (tempo.scruter()) {
        if (etat == false) {
            digitalWrite(LED, HIGH);
            etat = true;
        } else {
            digitalWrite(LED, LOW);
            etat = false;
        }
    }


}

