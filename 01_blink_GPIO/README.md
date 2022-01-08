# Premier programme

## Présentation

Pour un premier test, nous allons faire clignoter la LED intégrée.
Sur la carte de développement ESP-WROOM la LED intégrée se trouve sur le port GPIO2. Elle est de couleur bleu.

## Structure des dossiers

Le fichier `platformio.ini` contient toutes les informations du projet utiles pour PlatformIO. Le type de carte, le framework, la plateforme utilisée.

Le repertoire `src`  contient le code source dans le fichier `main.cpp`.
Vous remarquerez `#include  <Arduino.h>` en début de fichier, chose que l'on n'a pas lorsqu'on utilise l'IDE Arduino. 
PlatformIO permet de développer sur différent framework, Arduino y compris. Et donc pour utiliser les classes usuelles d'Arduino il est nécessaire d'inclure la librairie. **Arduino.h**. L'objet **Serial** est créé par le code du framework Arduino. On peut donc utiliser directement ses méthodes begin et println.

Les autres dossiers/fichiers ne seront pas utilisés pour ce test. Nous aurons l'occasion d'y revenir lors d'une utilisation plus poussée.

## Le programme
``` cpp
#include <Arduino.h>

int LED = 2;

void setup()
{
    pinMode(LED, OUTPUT);
    Serial.begin(115200);
    Serial.println("Setup done");
}

void loop()
{
    digitalWrite(LED, digitalRead(LED) ^1); // turn the LED
    delay(200); // wait for 0.2 second
    digitalWrite(LED, digitalRead(LED) ^1); // turn the LED 
    delay(2000); // wait for 2 seconds
}
```
Rien de bien compliqué !
Il est maintenant temps de compiler le code puis d'uploader l’exécutable afin  de vérifier que tout fonctionne.
 


