# Bibliothèque Wire : I2C

## Présentation

Cette bibliothèque fait donc partie intégrante du framwork  Arduino, elle est installée de base. Il suffit juste de l’importer dans le programme que l’on écrit.
```cpp
 #include <Wire.h> 
 ```

## Câblage des capteurs

Quatre fils  sont nécessaires pour la communication :

-   SDA (Serial Data Line)  D21
-   SCL (Serial Clock Line) D22
-   GND pour un commun entre les 2 appareils
-   3,3V ou 5V pour alimenter le périphérique

![raccordement](/07_I2C/Cablage_BME280_esp32.png)

## Les différentes méthodes

**begin() (maître/esclave)**

Cette fonction accepte comme argument facultatif l’adresse. Si l'ESP32 rejoint le bus de communication sans adresse, il le rejoint comme maître. A noter qu’un seul maître est nécessaire et suffisant (il est unique). Mettre une adresse comme paramètre indique que le périphérique rejoint le bus comme un périphérique esclave.
```cpp
Wire.begin()        // en mode maitre
Wire.begin(adresse) // en mode esclave
```
**beginTransmission() (maître)**

Cette fonction commence la transmission vers un esclave sur le bus de communication. L’adresse de ce périphérique doit être passée en argument.
```cpp
Wire.beginTransmission(adresse)
```    

Cette fonction sera suivie dans le code de la fonction **write()** ainsi que de **endTransmission()** pour réaliser entièrement la séquence de communication.

**endTransmission() (maître)**  
Comme son nom l’indique, elle ferme la communication.

```cpp
 Wire.endTransmission(stop)
 ```
 
 Cette fonction retourne une valeur de type byte qui peut prendre 5 arguments :

-   **0** : succès quand la transmission est acquittée (ACK) par le récepteur

Sinon, quand une erreur est détectée la réponse est :

-   1 : données trop longues pour être contenues dans la mémoire tampon de l’envoi
-   2 : signifie NACK (no acknowledge / non acquittement) pour erreur sur l’adresse de transmission
-   3 : signifie NACK pour erreur sur la transmission des données
-   4 : autre erreur

