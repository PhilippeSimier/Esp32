## Circuit RTC DS3231 avec un ESP32 

### Introduction
Le circuit RTC DS3231 est un composant électronique largement utilisé pour fournir des informations de temps précises dans divers projets électroniques. Voici une description détaillée de ses caractéristiques principales :

1.  **Horloge temps réel (RTC) :** Le DS3231 est spécifiquement conçu comme un circuit RTC, ce qui signifie qu'il est capable de suivre le temps en continu, même en l'absence d'alimentation externe.
    
2.  **Précision :** L'une des caractéristiques les plus remarquables du DS3231 est sa grande précision. Il est capable de maintenir une précision dans l'ordre de quelques secondes par mois, ce qui le distingue de certains autres RTC moins précis.
    
3.  **Capteur de température intégré :** En plus de la fonction d'horloge, le DS3231 est équipé d'un capteur de température interne. Cela permet de mesurer la température ambiante, ce qui peut être utile dans certaines applications.
    
4.  **Interface de communication I2C :** Le DS3231 communique avec d'autres composants électroniques via le bus I2C. Cette interface facilite l'intégration avec une variété de microcontrôleurs, y compris l'ESP32 dans notre cas.
    
5.  **Alimentation basse consommation :** Le DS3231 est conçu pour fonctionner avec une faible consommation d'énergie, ce qui le rend adapté à une utilisation dans des applications sur batterie.
    
6.  **Correction automatique de la dérive de fréquence :** Le DS3231 est équipé d'un mécanisme de compensation de la dérive de fréquence, assurant une précision à long terme en ajustant automatiquement la fréquence interne du cristal en fonction de la température.
    
7.  **Boîtier compact :** Physiquement, le DS3231 est souvent disponible dans un boîtier compact, généralement de type DIP (Dual Inline Package) ou SOIC (Small Outline Integrated Circuit), ce qui facilite son intégration dans des projets électroniques.
    

En résumé, le DS3231 est un circuit RTC  précis  ce qui en fait un choix bien adapté pour des applications variées, notamment les horloges électroniques, les enregistreurs de données et d'autres dispositifs nécessitant une référence temporelle précise.

### Code C++ pour ESP32
Ce code constitue une base simple pour commencer à travailler avec le RTC DS3231 et l'ESP32 en utilisant le langage de programmation C++, avec platformIO. Vous pouvez étendre ce code en ajoutant des fonctionnalités supplémentaires telles que la gestion d'alarmes, l'enregistrement des données temporelles, ou l'intégration avec d'autres capteurs ou modules.
```ini
[env:lolin32]
platform = espressif32
board = lolin32
framework = arduino
lib_deps = 
	Wire
	SPI
	adafruit/Adafruit BusIO@^1.14.5
	adafruit/RTClib@^2.1.3
```
 
Dans ce code, nous utilisons la bibliothèque `Wire.h` pour la communication I2C et la bibliothèque `RTClib.h` pour interagir avec le module RTC DS3231.   

```cpp
void setup() {
    Serial.begin(115200);
    if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
        Serial.flush();
        while (1) delay(10);
    }
    if (rtc.lostPower()) {
        Serial.println("RTC lost power, let's set the time!");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
}
```

Le programme démarre en initialisant la communication série et en vérifiant la présence du module RTC. Si le module RTC est introuvable, le programme restera bloqué dans une boucle infinie.

Ensuite, le programme vérifie si le module RTC a perdu l'énergie et si c'est le cas, ajuste le temps avec la date et l'heurs de l'ordinateur ayant compilé le programme . 

```cpp
void loop() {
    
    DateTime now = rtc.now(); 
    char date[13];
    snprintf(date, sizeof(date), "%02d:%02d:%4d", dateTime.day(), dateTime.month(), dateTime.year());
    char time[11];
    snprintf(time, sizeof(time), "%02d:%02d:%02d", dateTime.hour(), dateTime.minute(), dateTime.second());
    char message[26];
    snprintf(message, sizeof(message), "%s\n%s", date, time);
    
    Serial.println(message);
        
    delay(1000);
}
```
La boucle principale lit ensuite la date et l'heure actuelles du RTC et les affiche via la communication série. 

La fonction `delay(1000)` introduit une pause d'une seconde entre chaque lecture pour éviter une utilisation excessive des ressources.
    
    

