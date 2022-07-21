# Afficheurs 6 chiffres 7 segments  



L'utilisation d'un afficheur à 7 segments avec le circuit d'interface **TM1637** réduit la charge sur le contrôleur ESP32 car tout le multiplexage est géré sur la puce d'interface.  Seulement 2 GPIO sont nécessaires pour contrôler un afficheur à 6 chiffres. la communication avec le TM1637 se fait au moyen d'une interface de bus à deux fils qui à première vue,  ressemble à une interface I2C mais le circuit ne respecte pas la norme I2C. L'ordre des bits est inversé ! et il n'y a pas d'adresse de composant !

![ordre des bits](/20_Afficheur_TM1637/img/TM1637_bit_ordering.png)

L'alimentation peut se faire en 3.3V sauf pour les afficheurs de couleur bleu.

Connecter les broches CLK sur GPIO 14 et DIO sur GPIO 27. 

![Câblage](/20_Afficheur_TM1637/img/cablage.jpg)

Il existe une bibliothèque pour ce CI, vous pouvez l'obtenir à partir de [github](https://github.com/jasonacox/TM1637TinyDisplay)

**TM1637TinyDisplay6** est une classe  pour module d'affichage LED à 7 segments à  6 chiffres basée sur la puce TM1637. 

Dans votre projet inclure la dernière version de la bibliothèque dans l'option **lib_deps** du fichier **platformIO.ini**.
```
[env:lolin32]
platform = espressif32
board = lolin32
framework = arduino
lib_deps = https://github.com/jasonacox/TM1637TinyDisplay
```

Dans votre programme instancier un objet TM1637TinyDisplay 
```
TM1637TinyDisplay6 display(CLK, DIO);
```
et appelez les méthodes comme showNumber(), showString(), showLevel() et showAnimation(). 
L'affichage fera défiler le texte pour les chaînes plus grandes que 6 caractères.

```cpp
#include <Arduino.h>
#include <TM1637TinyDisplay6.h>       // Include 6-Digit Display Class Header


// Define Digital Pins
#define CLK 14
#define DIO 27
#define LED 2

TM1637TinyDisplay6 display(CLK, DIO); // 6-Digit Display Class
float val = 10.0;

void setup() {

    pinMode(LED, OUTPUT);
    Serial.begin(115200);
    Serial.println("Setup done");

    display.setBrightness(BRIGHT_HIGH); 
    display.clear();
    display.showString("HELLO F4KMN");
    delay(1000);
    display.showNumber(421);
    
}

void loop() {

    digitalWrite(LED, digitalRead(LED) ^1); // turn the LED 
    delay(100); // wait for 0.1 second
    digitalWrite(LED, digitalRead(LED) ^1); // turn the LED 
    delay(100); // wait for 0.1 second
    display.showNumber(val);
    val += 0.01;
}
```


 
