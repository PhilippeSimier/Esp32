# Lora 
**LoRa signifie Long Range** c'est une modulation étendue à faible puissance.  Cette modulation est  utilisée sur les gammes de fréquences radio qui sont des bandes ISM (bande sans licence pour les applications industrielles, scientifiques et médicales)

-   **868MHz** en Europe
-   **915 MHz** en Australie et en Amérique du Nord 
-   **433 Mhz**  de 433,050 MHz à 434,790 MHz (dans la bande 70cm 430 440Mhz des radio-amateurs)

LoRa est  efficace, cette modulation peut transmettre des paquets de données sur une longue distance (plus de 10 km dans les zones rurales).

La communication **Peer to Peer** permet à deux appareils équipés de radios LoRa de se parler d'une manière similaire à la façon dont deux appareils Bluetooth communiquent, la principale différence étant  la portée augmentée.
L'exemple utilise deux cartes **LILYGO® TTGO LoRa32 V2.1_1.6 Version 433Mhz **.  Ce  sont des cartes ESP32 avec un chipset SX1276 qui gère la communication LoRa et un écran LCD SSD1306. Dans platformIO, la carte est référencée  **ttgo-lora32-v21**

le projet  comprendra deux appareils, l'un configuré comme émetteur et l'autre comme récepteur.

### Configuration d'un projet pour netbeans avec platformIO 
```
pio project init --ide netbeans --board ttgo-lora32-v21
```
### Recherche de la bibliothèque LoRa
```bash
pio pkg search "header:LoRa.h"
Found 3 packages (page 1 of 1)

sandeepmistry/LoRa
Library • 0.8.0 • Published on Sat Dec  5 15:38:41 2020
An Arduino library for sending and receiving data using LoRa radios. Supports Semtech SX1276/77/78/79 based boards/shields.
```
### Installation de la bibliothèque sandeepmistry/LoRa
```bash
pio pkg install --library sandeepmistry/LoRa
```
Cette commande modifie le fichier de configuration du projet platformio.ini
```
[env:ttgo-lora32-v21]
platform = espressif32
board = ttgo-lora32-v21
framework = arduino
lib_deps = sandeepmistry/LoRa@^0.8.0
```

## Le Programme sender
vous devez inclure les entêtes suivants
```cpp
#include <SPI.h>
#include <LoRa.h>
``` 
Un objet `Lora` de type `LoraClass` est créé par défaut. Ensuite,  initialisez le module LoRa SX1276 avec les méthodes `setPins` et `begin`. 
La classe `LoraClass` dérive de la classe `Stream` 
```cpp
    SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);
    LoRa.setPins(LORA_CS, LORA_RST, LORA_IRQ);
    if (!LoRa.begin(433775000)) { // with the specified frequency 433,775 Mhz.
        Serial.println("Starting LoRa failed!");
        while (1);
    }
```
**Envoi d'un paquet LoRa**

 - Démarrez la séquence d'envoi d'un paquet.
 - Ecrire des données dans le paquet. Chaque paquet peut contenir jusqu'à 255 octets.
 - Terminer la séquence d'envoi d'un paquet.

```cpp
    // send packet
    LoRa.beginPacket();   // Démarre la séquence d'envoi d'un paquet.
    LoRa.print("hello "); // Ecriture des données. Chaque paquet peut contenir jusqu'à 255 octets. 
    LoRa.print(counter);
    LoRa.endPacket();     // Termine la séquence d'envoi d'un paquet.
```
**Réception d'un paquet LoRa**
Une méthode  consiste à lire les paquets LoRa dans la boucle loop(). Premièrement, nous devons vérifier si un nouveau paquet est disponible, si un nouveau paquet est prêt, nous pouvons le lire :
```cpp
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
        //received a packet
        Serial.print("Received packet ");

        //read packet
        while (LoRa.available()) {
            data = LoRa.readString();
            Serial.print(data);
            int rssi = LoRa.packetRssi();
            Serial.printf(" RSSI : %d dBm", rssi);
            float snr = LoRa.packetSnr();
            Serial.printf(" SNR : %.2f dB\r\n", snr);
        }
    }
```
## Paramètres radio
### RSSI de paquet
```
int rssi = LoRa.packetRssi();
```

Renvoie le RSSI moyen du dernier paquet reçu (dBm).

### SNR de paquet
```
float snr = LoRa.packetSnr();
```

Renvoie le SNR estimé du paquet reçu en dB.

### RSSI

```
int rssi = LoRa.rssi();
```

Renvoie le RSSI actuel de la radio (dBm). RSSI peut être lu à tout moment (pendant la réception des paquets ou non)
### La fréquence

Changer la fréquence de la radio.
```
LoRa.setFrequency(frequency);
```

-   `frequency`- fréquence en Hz ( `433E6`, `868E6`, `915E6`)

### Facteur d'étalement

Modifier le facteur d'étalement de la radio.
```
LoRa.setSpreadingFactor(spreadingFactor);
```

-   `spreadingFactor`- facteur d'étalement, par défaut à`7`

Les valeurs prises en charge sont comprises entre `6`et `12`. Si un facteur d'étalement de `6`est défini, le mode d'en-tête implicite doit être utilisé pour transmettre et recevoir des paquets.

### Bande passante des signaux

Modifier la bande passante du signal de la radio.
```
LoRa.setSignalBandwidth(signalBandwidth);
```

-   `signalBandwidth`- bande passante du signal en Hz, par défaut à `125E3`.

Les valeurs prises en charge sont `7.8E3`, `10.4E3`, `15.6E3`, `20.8E3`, `31.25E3`, `41.7E3`, `62.5E3`, `125E3`, `250E3`et `500E3`.

### Taux de codage

Modifier le taux de codage de la radio.

```
LoRa.setCodingRate4(codingRateDenominator);

```

-   `codingRateDenominator`- dénominateur du taux de codage, par défaut à`5`

Les valeurs prises en charge sont comprises entre `5`et `8`, elles correspondent aux taux de codage de `4/5`et `4/8`. Le numérateur du taux de codage est fixé à `4`.

### Longueur du préambule

Modifiez la longueur du préambule de la radio.

```
LoRa.setPreambleLength(preambleLength);

```

-   `preambleLength`- longueur du préambule en symboles, par défaut à`8`

Les valeurs prises en charge sont comprises entre `6`et `65535`.

### Mot de synchronisation

Modifiez le mot de synchronisation de la radio.

```
LoRa.setSyncWord(syncWord);

```

-   `syncWord`- valeur d'octet à utiliser comme mot de synchronisation, par défaut à`0x12`

### [](https://github.com/sandeepmistry/arduino-LoRa/blob/master/API.md#crc)CRC

Activer ou désactiver l'utilisation du CRC, par défaut un CRC n'est pas utilisé.

```
LoRa.enableCrc();

LoRa.disableCrc();

```

### Inverser les signaux IQ

Activer ou désactiver l'inversion les signaux LoRa I et Q, par défaut un invertIQ n'est pas utilisé.

```
LoRa.enableInvertIQ();

LoRa.disableInvertIQ();

```

### Gain LNA

Réglez le gain LNA pour une meilleure sensibilité RX, par défaut AGC (Automatic Gain Control) est utilisé et le gain LNA n'est pas utilisé.

```
LoRa.setGain(gain);

```

-   `gain`- Gain LNA

Les valeurs prises en charge sont comprises entre `0`et `6`. Si le gain est de 0, l'AGC sera activé et le gain LNA ne sera pas utilisé. Sinon, si le gain est compris entre 1 et 6, l'AGC sera désactivé et le gain LNA sera utilisé.

### Mode inactif

Mettre la radio en mode inactif.
```
LoRa.idle();
```
### Mode veille

Mettre la radio en mode veille.

```
LoRa.sleep();
```


# Changelog

**04/09/2022 : ** Creation du README.md 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


