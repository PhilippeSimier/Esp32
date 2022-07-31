# Bits d'événement (ou _flags_ ) et groupes d'événements

Notez que  les "notifications de tâche" peuvent fournir une alternative légère aux groupes d'événements dans de nombreuses situations.

## Introduction

Les événements dans FreeRTOS sont utiles pour 

 -  synchroniser plusieurs tâches, créant ainsi ce que l'on appelle souvent un "rendez-vous" de tâche. Un point de synchronisation de tâche est un endroit dans le code de l'application où une tâche attendra dans l'état Bloqué (ne consommant pas de temps CPU) jusqu'à ce que toutes les autres tâches participant à la synchronisation aient également atteint leur point de synchronisation. 

Un « indicateur » ou « bit » d’événement est une valeur booléenne (1 ou 0) dans une variable de type  `EventBits_t`  utilisée pour indiquer si un événement s’est produit ou non. Un groupe d’événements est un ensemble de bits d’événements. Les groupes d’événements sont référencés à l’aide de variables de type  `EventGroupHandle_t`.

Le nombre de bits d’événement dans un groupe d’événements dépend de la constante de configuration de temps de compilation  `configUSE_16_BIT_TICKS`  dans  `FreeRTOSConfig.h`  :

-   Si  `configUSE_16_BIT_TICKS`  vaut 1, alors chaque groupe d’événements contient 8 bits d’événement utilisables.
-   Si  `configUSE_16_BIT_TICKS`  vaut 0, alors chaque groupe d’événements contient 24 bits d’événement utilisables.

La fonction  `xEventGroupCreate()`  est utilisée pour créer un groupe d’événements.

La fonction  `xEventGroupSetBits()`  ou  `xEventGroupSetBitsFromISR()`  définit un ou plusieurs bits dans un groupe d’événements et est généralement utilisée pour notifier à une tâche que les événements représentés par le ou les bits en cours de définition se sont produits.

La fonction  `xEventGroupWaitBits()`  permet à une tâche de lire la valeur d’un groupe d’événements et d’attendre éventuellement à l’état Bloqué qu’un ou plusieurs bits d’événements du groupe d’événements deviennent définis, si les bits d’événements ne sont pas déjà définis.

La condition de déblocage est spécifiée par une combinaison des valeurs des paramètres  `uxBitsToWaitFor`  et  `xWaitForAllBits`  :

-   `uxBitsToWaitFor`  spécifie les bits d’événement du groupe d’événements à tester
-   `xWaitForAllBits`  spécifie s’il faut utiliser un OU (`pdFALSE`) ou un ET (`pdTRUE`) au niveau des bits d’événement


# Changelog

**31/07/2022 : ** Creation du README.md 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


