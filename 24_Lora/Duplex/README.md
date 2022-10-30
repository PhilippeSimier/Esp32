# Lora en Half Duplex

## Introduction

Dans ce protocole, les données sont envoyées par blocs (packet). L'émetteur (Master) envoie un bloc de données  puis se met en attente d'une réponse. De son côté, le récepteur (Slave) traite les données et renvoie à l'émetteur un bloc de données pour signaler qu'il a bien reçu le bloc de données précédent et qu'il est prêt à recevoir de nouveau des données. Le récepteur peut dans certains cas renvoyer le caractère ASCII 0x15 (appelé NACK pour Negative ACKnowledge) pour signaler qu'il a détecté une erreur dans la transmission.
Seul le Master est à l'initiative de la transmission. Les Noeuds slave ne font que répondent aux requêtes. 

## Structure d'un packet de donnée

Chaque bloc de communication est composé d'un entête
L'en-tête de liaison  est une suite de 7 octets qui se décomposent comme suit :

 - L'adresse Mac de destination (un octet)
 - L'adresse  Mac de l’émetteur  (un octet)
 - Un identifiant de Packet (un octet)
 - La longueur du Paylaod
 

| byte | byte | byte | unsigned int | String |
|------------|--------|----|--------|-------------------------|
| destination | source | ID | length | payload |

L'adresse 0xFF correspond à l'adresse de diffusion.

