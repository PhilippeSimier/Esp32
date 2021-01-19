# Serial

## Introduction

Un récepteur / émetteur asynchrone universel (UART) est une fonctionnalité matérielle qui gère la communication série.
Il existe **trois contrôleur série** prises en charge par le matériel sur l'ESP32, appelées **UART0**, **UART1** et **UART2**. 
Chaque contrôleur UART est configurable indépendamment avec des paramètres tels que la vitesse de transmission, le nombre de bits de données, l'ordre des bits, le nombre de bits d'arrêt, le bit de parité, etc.

Comme tous les périphériques, les broches des UART peuvent être mappées logiquement à l'une des broches disponibles sur l'ESP32. Cependant, les UART peuvent également avoir un accès direct, ce qui améliore légèrement les performances. Le tableau de mappage par défaut des broches  est le suivant.

 | UART	|   RX    |	  TX    | CTS   | RTS    |
 |------|---------|---------|-------|--------|
 | U0UXD | GPIO3  | GPIO1   | N/A   | N/A    |	
 | U1UXD | GPIO9  | GPIO10  | GPIO6 | GPIO11 |
 | U2UXD | GPIO16 | GPIO17  | GPIO8 | GPIO7  |	

**U0UXD** est utilisé pour communiquer avec l'ESP32 pour la programmation et pendant la réinitialisation / démarrage.

**U1UXD** n'est pas utilisé et peut être utilisé pour vos projets.

**U2UXD** n'est pas utilisé et peut être utilisé pour vos projets.

## Attribuer les broches à une liaison série
Les broches des liaisons séries sont attribuées par défaut, mais il est possible de les réaffecter.

```cpp
	#include <HardwareSerial.h>  // la bibliothèque HardwareSerial.h
	HardwareSerial MaSerie(1);	 // Déclaration d'un controleur lié à UART 1
	
	// Configuration de la vitesse du nombre de bits par caratère
	// GPIO25 -> RX
	// GPIO26 -> TX
	
	MaSerie.begin(9600,SERIAL_8N1,25,26);  
```



# Changelog

**19/01/2021 : ** Ajout du README . 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#



