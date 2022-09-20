# Carte ESP32 SNIR 
![le clavier](/21_carte_clavier_snir/carte_snir.jpg) 
## Description

Cette carte multi usage sur la base d’un ESP32, intègre directement un certains nombres de périphériques, sans avoir aucun câblage à effectuer. Elle dispose également de connecteurs pour ajouter des composants externes (I2C, RS232, ruban DEL RGB, servo moteur). La carte possèdent deux relais qui permettent de contrôler des actionneurs alimentés en tension continu ou alternatif 12V, 24V. 

Les connectivités WiFi et Bluetooth de l’ESP32 sont  accessibles et permettent de créer un serveur Web pour contrôler la carte à distance.

## Programmation en C++
La carte est programmable en C++ avec l’EDI arduino. Pour des développements plus ambitieux, les EDI plus évolués tel que Visual Studio Code, NetBeans ou Qtcreator avec le plug-in PlatformeIO seront préférés. 
Des activités pratiques de programmation en C++ sont proposés. Vous trouverez  quelques exemples :

 - **Digicode** pour le contrôle d'accès 
 - **Coffre-fort d'hôtel**
 - **Simulation d'un capteur GPS**

## Programmation en MicroPython

La carte est programmable en langage MicroPython avec EDI Thonny.
![EDI Thonny](/21_carte_clavier_snir/EDI_Thonny.png) 

## La carte dispose  des périphériques :

 -  1 Écran OLED 128 x 64,
 -  1 Clavier matricé 12 touches,
 -  4 LED RGB, extensible
 -  1 Capteur de température OneWire 
 -  1 Capteur de lumière LDR
 -  3 boutons poussoirs 
 -  1 interrupteur 
 -  1 Potentiomètre à glissière
 -  2 relais 
 -  1 RTC 
 -  1 Connecteur I2C 
 -  1 Connecteur DB9 - RS232 
 -  1 Connecteur servo-moteur

# Changelog

**04/09/2022 : ** Creation du README.md 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


