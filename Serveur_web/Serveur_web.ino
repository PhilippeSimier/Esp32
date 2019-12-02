
#include <WiFi.h>
#include <WebServer.h>
#include "timer.h"

#define InAna 34
#define LED 13

const char* ssid     = "SNIR03";        // Nom du réseau
const char* password = "totototo";      // clé 

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
    server.send ( 200, "text/html", construirePage() );

}

void pageInLine() {
   Serial.println("requete GET /inline");
   server.send(200, "text/plain", "this works as well");
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
  Serial.begin(9600);
  pinMode(LED, OUTPUT);

  delay(10);

  Serial.print("Connexion au WiFi ");
  Serial.println(ssid);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);    // On se connecte
  
  while (WiFi.status() != WL_CONNECTED) { // On attend
    delay(500);
    Serial.print(".");
  }

  Serial.println("");  // on affiche les paramètres 
  Serial.println("WiFi connecté");  
  Serial.print("Adresse IP du module EPC: ");  
  Serial.println(WiFi.localIP());
  Serial.print("Adresse IP de la gateway : ");
  Serial.println(WiFi.gatewayIP());
  
  server.on ( "/",  pageIndex );   // associe une fonction pour la méthode http GET /
  server.on ( "/inline", pageInLine);
  server.onNotFound(handleNotFound);
  
  server.begin();
  Serial.println ( "Serveur HTTP en fonction" );
  tempo.Lancer(500);
}


void loop() {
  
  server.handleClient();
  if (tempo.Scruter())
  {
    if (etat == false){
      digitalWrite(LED, HIGH);
      etat = true;
    }
    else{
      digitalWrite(LED, LOW);
      etat = false;      
    } 
  }

 
 
}
