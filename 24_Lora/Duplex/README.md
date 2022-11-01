# Lora en Half Duplex

## Introduction

Dans ce protocole, les données sont envoyées par blocs (packet). L'émetteur (Master) envoie un bloc de données  puis se met en attente d'une réponse. De son côté, le récepteur (Slave) traite les données et renvoie à l'émetteur un bloc de données pour signaler qu'il a bien reçu le bloc de données précédent et qu'il est prêt à recevoir de nouveau des données. Le récepteur peut dans certains cas renvoyer le caractère ASCII 0x15 (appelé NACK pour Negative ACKnowledge) pour signaler qu'il a détecté une erreur dans la transmission.
Seul le Master est à l'initiative de la transmission. Les Nœuds slave ne font que répondent aux requêtes. 

## Structure d'un bloc de communication

Chaque bloc de communication est composé d'un entête et d'un payload
L'entête de liaison  est une suite de 7 octets qui se décomposent comme suit :

 - L'adresse Mac de destination (un octet)
 - L'adresse  Mac de l’émetteur  (un octet)
 - Un identifiant de Packet (un octet)
 - La longueur du Paylaod
 

| byte | byte | byte | unsigned int | String |
|------------|--------|----|--------|-------------------------|
| destination | source | ID | length | payload |

L'adresse 0xFF correspond à l'adresse de diffusion.

## Protocole d'échange 
Le dialogue est basé sur une structure hiérarchisée entre un maître et plusieurs esclaves.
Le maître gère les échanges de données avec les autres  par une cyclique (polling).  Au  cours d‘un cycle, des données sont échangés. Le temps de cycle dépend du nombre d'esclaves et de la taille des données échangées

![protocol](/24_Lora/Duplex/protocol.png) 

-   Le maître envoie une **demande** et attend une **réponse**.
-   Deux esclaves ne peuvent dialoguer ensemble.
-   Le dialogue maître – esclave peut être schématisé sous une forme successive de liaisons point à point.
-   Mode de communication : **half-duplex**
-   le maître parle à l'ensemble des esclaves, sans attente de réponse (en utilisant l'adresse 0xFF de diffusion générale).

Il ne peut y avoir sur le canal radio qu'un seul équipement en train d'émettre. Aucun esclave ne peut envoyer un message sans une demande préalable du maître. Le dialogue direct entre les esclaves est impossible. Ainsi, pas de risque de collision.

Les abonnés sont identifiés par des adresses attribuées par l'utilisateur.  Deux abonnés ne peuvent avoir la même adresse.
