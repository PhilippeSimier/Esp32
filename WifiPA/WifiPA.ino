#include "WiFi.h"
#include <WebServer.h>
 
const char *ssid = "ESP32AP";
const char *password = "totototo";

WebServer server(80);

void pageIndex() {
    Serial.println("requete GET /");
    server.send ( 200, "text/html", "this works as well" );

}

void setup() {
 
  Serial.begin(9600);
  WiFi.softAP(ssid, password);
 
  Serial.println();
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
  
  server.on ( "/",  pageIndex ); 
  server.begin();
 
}
 
void loop() {
  
server.handleClient();  
}
