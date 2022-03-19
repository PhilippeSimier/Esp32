# Le bus I2C

## Présentation I2C
I²C signifie Inter Integrated Circuit (il se prononce I-squared-C). C'est un protocole de communication synchrone, multi-maître, multi-esclave. 
L'ESP32 prend en charge la communication I2C via ses deux interfaces de bus I2C qui peuvent servir de maître ou d'esclave I2C, selon la configuration de l'utilisateur.

Avec la communication I2C, chaque esclave sur le bus a sa propre adresse, un nombre hexadécimal qui permet à l'ESP32 de communiquer avec chaque appareil.
L'adresse I2C se trouve généralement sur la fiche technique du composant. Cependant, si elle est difficile à trouver, vous pouvez exécuter le programme scanner I2C présent dans ce dépot pour trouver l'adresse I2C.

## Présentation de l'objet Wire

L'objet Wire fait partie intégrante du framwork  Arduino, il est crée de base. Il suffit juste  d’importer le fichier Wire.h dans le programme que l’on écrit.

```cpp
 #include <Wire.h> 
 ```
L'objet Wire est une instance de la classe TwoWire.


## Câblage des capteurs

Deux fils  sont nécessaires pour la communication eet deux autres pour l'alimentation:

-   SDA (Serial Data Line)  D21
-   SCL (Serial Clock Line) D22
-   GND pour le commun entre les 2 appareils
-   3,3V ou 5V pour alimenter le périphérique

![raccordement](/07_I2C/Cablage_BME280_esp32.png)

Avec l'objet Wire, vous initialisez l'I2C comme suit : 

```cpp
    Wire.begin(I2C_SDA, I2C_SCL);
```
Il vous suffit donc de définir les broches SDA et SCL souhaités dans les variables I2C_SDA et I2C_SCL.

Cependant, si vous utilisez des bibliothèques pour communiquer avec vos capteurs, cela peut, ne pas fonctionner car il peut être  difficile de sélectionner d'autres broches. Cela se produit parce que ces bibliothèques peuvent écraser votre configuration, si vous ne transmettez pas votre propre instance TwoWire lors de l'initialisation de la bibliothèque. Dans ces cas, vous devez examiner de plus près les fichiers de bibliothèque .cpp et voir comment transmettre vos propres paramètres.

Rien ne vous interdit de créer votre propre instance de la classe TwoWire, comme le montre le code exemple suivant

```cpp
    #define I2C_SDA 33
    #define I2C_SCL 32

    TwoWire wire2 = TwoWire(0);
    
    wire2.begin(I2C_SDA, I2C_SCL, 100000);
    
    status = bme.begin(0x77, &wire2);  //démarrage du BME280 avec la référence du bus I2C
```

## Les différentes méthodes de Wire

La classe **TwoWire** hérite de **Stream** On retrouve donc toutes les méthodes de Stream dans Wire.  

 - read
 - available
 - readBytes

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

**requestFrom() (maître)**  
Cette fonction utilisée par le périphérique maître, sert à demander une information à un esclave.  L’argument de cette fonction est l’adresse de l’esclave à interroger.
```cpp
Wire.requestFrom(address, quantity, stop)
```    

Les deux premiers paramètres sont indispensables :

**Paramètre address**  
Comme son nom l’indique, l’adresse de l’esclave codée sur 7 bits.

**Paramètre quantity**  
Le nombre d’octets (bytes) que le maître demande de l’esclave dans sa réponse.

**Paramètre stop**  
Valeur booléenne, elle est par défaut à True.  
True : après la requête du maître, requestFrom() envoie un message stop sur le bus, le libérant.  
False : à contrario, le bus n’est ici pas libéré.

Cette fonction renvoie  le nombre d’octets retournés par l’esclave

## Exemple de programme
```cpp
// Lecture du registre de température

Wire.beginTransmission(i2c_device_address);
Wire.write(REG_ADDR_TEMP);
if (Wire.endTransmission())
   return error;

// Lecture du contenu du registre
if (Wire.requestFrom(i2c_device_address, 2)) {
    Wire.readBytes((uint8_t*) & i2c_received, 2);
} else {
// Erreur de lecture temperature
   return error;
}
....
```
