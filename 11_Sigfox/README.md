# Sigfox

## La carte SNOC BRKWS01

Le breakout **BRKWS01** est une carte  SigFox , basée sur le module Wisol SFM10R1. Cette carte permet  d'utiliser le réseau SigFox LPWan  pour la transmission de données. Le réseau SigFox permet d'envoyer des messages de **12 octets** à raison de 140 messages par jour.

## Activer le module sur le site SigFox

Avant de permettre l’accès au réseau SigFox, il est nécessaire créer un compte utilisateur. 
Le compte utilisateur permet d'activer des modules. l'identifiant ID et le code PAC  de la carte SNOC sont nécessaires pour créer une nouvelle activation. Cette activation autorise le module à émettre et recevoir des données sur le réseau SigFox . La carte SNOC est vendu avec un an d’abonnement découverte inclus.
Quand votre inscription est terminée. Il reste à la valider en suivant le lien que vous avez reçu dans un mail à l’adresse que vous avez fournie. Cliquez sur le lien dans le message pour terminer votre inscription.  Vous devrez alors définir un mot de passe.

[lien vers la page d'activation d'un module](https://buy.sigfox.com/activate)

## Envoi de données via SigFox

Le module est controlé avec des commandes série AT envoyées sur des broches TX / RX. La communication série: se fait à **9600** bauds, avec **8 bits par caractères**, 1 bit de stop, **sans parité** écho local.
Les commandes AT se font en **majuscules**

Test de Communication:	

    AT
    OK

Récupérer le Module ID:	

    AT$I=10

Récupérer le code PAC:	

    AT$I=11

Envoyer un message SIGFOX:	(Valeur Hexadécimal) donc un nombre de caractères paire

    AT$SF=001122AABBEEFF


Envoyer un message SIGFOX avec trame de reception:	(Valeur Hexadécimal)

    AT$SF=XXXXXXXXXXXX,1 

## Lire les messages reçus sur l'aggrégator SigFox

Les messages émis par les devices sont stockés sur l'aggrégator SigFox. Il est possible de les consulter en se connectant sur le site Sigfox côté **backend**.

[Lien vers le backend SigFox](https://backend.sigfox.com/auth/login)

Cliquer sur l'onglet **DEVICE** un tableau des devices activés s'affiche. 
Cliquer sur le **Device ID**  puis sur **MESSAGES** pour afficher la liste des messages envoyés par le module sélectionné.
Chaque message est horodaté.

## Activation du callback

A réception du message, le serveur SigFox va transférer les données vers un serveur désigné par l’utilisateur. C’est ce qu’on appelle un “**callback**”.
Dans l’onglet “**DEVICE TYPE**” du site SigFox, cliquer sur le nom de la carte, pour faire apparaître dans la colonne de gauche un menu comportant l’option **CALLBACKS**.
Pour créer un nouveau callback cliquer sur le bouton new (en haut à droite)
Choisir l'option **Custom callback**

to do

## Diagramme de classe Sigfox pour esp32

![Diagramme de classe](/11_Sigfox/class_Sigfox.png)


[le code](https://github.com/PhilippeSimier/Esp32/tree/master/11_Sigfox/Sigfox_Demo) 

# Changelog

**08/01/2020 : ** Ajout du README . 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#
example : https://github.com/adrien3d/IO_WSSFM10-Arduino

