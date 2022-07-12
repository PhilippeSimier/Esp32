# ESP32 WIFI

La première chose que vous devez faire pour utiliser les fonctionnalités Wi-Fi de l'ESP32 est d'inclure la bibliothèque WiFi.h dans votre code, comme suit :
```cpp
#include <WiFi.h>
```
Un objet **WiFi** est créé par défaut.
La carte ESP32 peut servir de station Wi-Fi, de point d'accès ou les deux. Pour définir le mode Wi-Fi, utilisez la méthode **mode()** et définissez le mode souhaité comme argument :
```cpp
WiFi.mode(WIFI_STA);
```
Lorsque l'**esp32** est défini comme une station Wi-Fi, il peut se connecter à un réseau WiFi. Le routeur lui attribue une adresse IP unique. Vous pouvez communiquer avec l'esp32 en utilisant d'autres appareils également connectés au même réseau en vous référant à l'adresse IP  de l'esp32.

![WiFi station](/04_Wifi_Station/images/WIFI_station.png)

## Connection à un réseau Wi-Fi

Pour connecter l'ESP32 à un réseau Wi-Fi spécifique, il faut connaître son SSID et son mot de passe.

```cpp
void initWiFi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi ..");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        delay(1000);
    }
    Serial.println(""); // affichage des paramètres 
    Serial.println("WiFi connecté");
    Serial.print("Adresse IP du module ESP32 : ");
    Serial.println(WiFi.localIP());
    Serial.print("Adresse IP de la gateway : ");
    Serial.println(WiFi.gatewayIP());
    Serial.print("Adresse IP du DNS : ");
    Serial.println(WiFi.dnsIP());
}
```

