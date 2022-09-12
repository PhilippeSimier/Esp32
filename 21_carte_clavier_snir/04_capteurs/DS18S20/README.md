# Capteur de température

La carte ESP32 SNIR, intègre directement un capteur de température One Wire **DS18B20**. Ce capteur est assez précis et ne nécessite qu'une résistance externe pour fonctionner. Il peut mesurer des températures de **-55°C à +125°C** avec une précision de ±0,5°C.
L'avantages du DS18B20 est que plusieurs DS18B20 peuvent coexister sur le même bus One-Wire. Chaque DS18B20 possède un **code série 64 bits** unique gravé en usine qui permet de les différencier.

Sur la carte, le capteur est connecté sur la broche Gpio 18.

## Installation des bibliothèques

Vous devez installer la librairie **One Wire** de Paul Stoffregen et la librairie **Dallas Temperature**. Suivez les étapes suivantes pour installer ces bibliothèques avec platformIO. Dans le répertoire de votre projet exécutez les commandes suivantes :
```bash
pio pkg install --library "paulstoffregen/OneWire@^2.3.7"
pio pkg install --library "milesburton/DallasTemperature@^3.11.0"
```
Le fichier platfomIO.ini est complété avec les dépendances
```ini
[env:lolin32]
platform = espressif32
board = lolin32
framework = arduino
lib_deps =
	paulstoffregen/OneWire@^2.3.7
	milesburton/DallasTemperature@^3.11.0
```
## Le code
```cpp
#include <OneWire.h>  
#include <DallasTemperature.h>
```
Créez les instances nécessaires
```cpp
#define  ONE_WIRE_BUS  18  // Gpio 18 sur la carte clavier SNIR
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
```
Démarrer le capteur
```cpp
sensors.begin();
```
Lire la température
```cpp
sensors.requestTemperatures();
float temperatureC = sensors.getTempCByIndex(0);
```
Parce que nous n'utilisons qu'un seul capteur, son index est 0.

# Changelog

**08/08/2022 : ** Creation du README.md 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


