# Serial

## Introduction

Il existe **trois interfaces série** prises en charge par le matériel sur l'ESP32, appelées **UART0**, **UART1** et **UART2**. 

Comme tous les périphériques, les broches des UART peuvent être mappées logiquement à l'une des broches disponibles sur l'ESP32. Cependant, les UART peuvent également avoir un accès direct, ce qui améliore légèrement les performances. Le tableau de mappage des broches  est le suivant.

 | UART	|   RX    |	  TX    | CTS   | RTS    |
 |------|---------|---------|-------|--------|
 | U0UXD | GPIO3  | GPIO1   | N/A   | N/A    |	
 | U1UXD | GPIO9  | GPIO10  | GPIO6 | GPIO11 |
 | U2UXD | GPIO16 | GPIO17  | GPIO8 | GPIO7  |	

**U0UXD** est utilisé pour communiquer avec l'ESP32 pour la programmation et pendant la réinitialisation / démarrage.

**U1UXD** n'est pas utilisé et peut être utilisé pour vos projets.

**U2UXD** n'est pas utilisé et peut être utilisé pour vos projets.

# Changelog

**08/01/2020 : ** Ajout du README . 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


