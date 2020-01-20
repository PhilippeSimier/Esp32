# Sigfox

## La carte BRKWS01

Le breakout **BRKWS01** est une carte  SigFox , basée sur le module Wisol SFM10R1. Cette carte permet  d'utiliser le réseau SigFox LPWan  pour la transmission de données. Le réseau SigFox permet d'envoyer des messages de **12 octets** à raison de 140 messages par jours.

## Envoi de données via SigFox

Le module est controlé avec des commandes série AT envoyées sur des broches TX / RX. La communication série: se fait à 9600 bauds, avec 8 bits par caractères, 1 bit de stop, sans parité.

Test de Communication:	

    AT
    OK

Récupérer le Module ID:	

    AT$I=10

Récupérer le code PAC:	

    AT$I=11

Envoyer un message SIGFOX:	(Valeur Hexadécimal)

    AT$SF=XXXXXXXXXXXX


Envoyer un message SIGFOX avec trame de reception:	(Valeur Hexadécimal)

    AT$SF=XXXXXXXXXXXX,1 

## Classe pour esp32

[le code](https://github.com/adrien3d/IO_WSSFM10-Arduino) 

# Changelog

**08/01/2020 : ** Ajout du README . 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


