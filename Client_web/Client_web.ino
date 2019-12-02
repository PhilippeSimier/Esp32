/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <WiFi.h>

// valeurs pour le WiFi
const char* ssid     = "Livebox-5648";
const char* password = "vz9Lcc2RnTTmnDuD4Y";

// valeurs pour le serveur Web
const char* host     = "Example.com";

void setup() {
  Serial.begin(9600);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.print("Connexion au WiFi ");
  Serial.println(ssid);
  
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
}


void loop() {
  Serial.print("Connexion au serveur : ");
  Serial.println(host);
  
  // On se place dans le rôle du  client en utilisant WifiClient
  WiFiClient client;

  // le serveur Web attend tradionnellement sur le port 80
  const int httpPort = 80;

  // Si la connexio échoue ca sera pour la prochaine fois
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  
  // La connexion a réussie on forme le chemin 
  String url = String("/");
  
  Serial.print("demande URL: ");
  Serial.println(url);
  
  // On l'envoie au serveur sur plusieurs lignes
  // GET / HTTP/1.1
  // Hosts: outils.plido.net
  // Connection: close
  // 
  // La première ligne précise à  la fin version du protocole attendu
  // La deuxième rappelle au serveur sous quel nom on l'appelle, en
  // effet,  une même adresse IP on peut avoire différents serveurs
  // repondant à  des noms différents.
  // La troisième ligne indique que le serveur doit fermer la 
  // connexion apres la réponse et ne pas attendre d'autres requêtes.
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");

  // On attend 10 mili-secondes
  delay(1000);
  
  // On lit les données reçues, s'il y en a
  while(client.available()){
    String line = client.readStringUntil('\r'); // découpe ligne par ligne
    Serial.print(line);
  }

   // plus de données
  Serial.println();
  Serial.println("connexion fermée");

  delay(30000);
}
