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


