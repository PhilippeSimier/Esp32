# Carte ESP32 CIEL  
![le clavier](/21_carte_clavier_snir/carte_snir.jpg) 
## Description

Cette carte polyvalente, basée sur un **ESP32,** intègre directement plusieurs périphériques, éliminant ainsi la nécessité de tout câblage. Elle est également équipée de connecteurs permettant d'ajouter des composants externes tels que I2C, RS232, ruban LED RGB et servo-moteur. La carte est dotée de deux relais permettant le contrôle d'actionneurs alimentés en tension continue ou alternative de 12V à 24V.

Les fonctionnalités WiFi et Bluetooth de l'ESP32 sont accessibles, offrant la possibilité de créer un serveur Web pour contrôler la carte à distance.


## La carte intègre les périphériques :

 -  1 Écran OLED 128 x 64,  **SSD1306**
 -  1 Clavier matricé 12 touches,
 -  4 LED RGB, extensible sur connecteur
 -  1 Capteur de température **DS18B20**.
 -  1 Capteur de lumière LDR
 -  3 boutons poussoirs 
 -  1 interrupteur 
 -  1 Potentiomètre à glissière
 -  2 relais 
 -  1 Une horloge temps réel RTC **DS3231** 
 -  2 Connecteurs I2C 
 -  1 Connecteur DB9 - RS232 
 -  1 Connecteur servo-moteur

## Programmation en C++
  
Le framework Arduino-ESP32 constitue une plateforme de développement logiciel open-source spécifiquement conçue pour le microcontrôleur ESP32. 
Ce framework simplifie le processus de programmation en fournissant une bibliothèque riche en fonctionnalités, permettant aux développeurs d'accéder facilement aux ressources matérielles de l'ESP32. 

Avec le framework Arduino-ESP32, les utilisateurs peuvent exploiter les fonctionnalités de l'ESP32 de manière efficace, que ce soit pour des projets simples nécessitant une connectivité sans fil ou pour des applications plus complexes impliquant des capteurs, des actionneurs et des communications avancées. La polyvalence et la simplicité d'utilisation font du framework Arduino-ESP32 un choix privilégié pour les développeurs travaillant sur des projets variés, allant de l'Internet des Objets (IoT) aux dispositifs embarqués.

Il est recommandé d'utiliser un EDI plus avancé tels que Visual Studio Code, NetBeans ou Qtcreator avec le plug-in PlatformIO. 

Des travaux pratiques de programmation en C++ sont disponibles, comprenant quelques exemples tels que :

1.  Digicode pour le contrôle d'accès 
2.  Coffre-fort d'hôtel
3.  Simulation d'un capteur GPS

## Programmation en MicroPython

**MicroPython** est une implémentation du langage de programmation Python 3.x, conçue pour fonctionner sur des microcontrôleurs et des systèmes embarqués. Cette version allégée de Python permet aux développeurs d'écrire des scripts Python et de les exécuter directement sur des dispositifs matériellement limités, tels que le microcontrôleur ESP32.

MicroPython bénéficie d'une communauté active qui partage des ressources, des tutoriels et des bibliothèques, facilitant ainsi le développement de projets sur l'ESP32.

MicroPython sur l'ESP32 offre une solution puissante et accessible pour les projets IoT et l'informatique embarquée, ouvrant la voie à une programmation Python sur des dispositifs embarqués.

![EDI Thonny](/21_carte_clavier_snir/EDI_Thonny.png) 




# Changelog

**04/09/2022 : ** Creation du README.md 
**08/01/2023 : ** Actualisation de la présentation

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


