# Sémaphore de comptage

## Introduction

Le sémaphore de comptage est généralement utilisé pour deux choses telles que le comptage des événements et la gestion des ressources.

![les deux fonctions](/09_FreeRTOS/02_Synchronisation/semaphore_counting/Counting-Semaphore-types.webp)

La fonction  `xSemaphoreCreateCounting()` est utilisée pour créer des sémaphores de comptage. 
Noté que la même fonction est utilisée pour le comptage des événements et la gestion des ressources. Seule la façon dont nous utilisons les arguments d'entrée de xSemaphoreCreateCounting() l'initialise pour le comptage d'événements ou la gestion des ressources.

#### Comptage des événements

En cas de comptage d'événements, nous pouvons le considérer comme un compteur qui définit la valeur maximale et garde également une trace du nombre de fois où l'événement s'est produit. Habituellement, un gestionnaire d'événements est utilisé pour donner un accès au sémaphore et garder une trace de la valeur de comptage. Chaque fois qu'une tâche prend une valeur de sémaphore, la valeur de comptage est décrémentée de un.

####  La gestion des ressources

Dans le cas de la gestion des ressources, le sémaphore de comptage définit le  nombre de ressources partagées disponibles et pouvant être utilisées par des tâches en même temps.

Par exemple, imaginons qu'il existe deux tâches FreeRTOS qui souhaitent écrire des données sur la même liaison série  via le module de communication UART.  Par conséquent, nous devons gérer les ressources du moniteur série UART  entre les deux tâches en utilisant un sémaphore de comptage pour la gestion des ressources. Il faut d'abord initialiser le sémaphore de comptage égal au nombre de ressources (ici une). Après cela, une tâche qui veut utiliser la liaison série doit prendre le sémaphore en décrémentant la valeur de comptage du sémaphore.
Lorsque la valeur de comptage atteint zéro, toute autre tâche qui tente d'accéder au sémaphore,  entrera dans l'état de blocage jusqu'à ce que les autres tâches en cours d'exécution libèrent le sémaphore (c'est à dire libèrent la ressource).

## Exemple Barrière d'exécution

Nous allons développer une application simple où nous utiliserons un sémaphore de comptage comme barrière d'exécution.

Dans notre programme, la fonction de setup() lancera une quantité configurable de tâches, puis elle attendra sur un sémaphore pour que toutes les tâches soient terminées. Après le lancement des tâches, la fonction de setup() essayera de tenir un sémaphore autant de fois que le nombre des tâches lancées, et continuera son exécution seulement l'exécution après ce point.

Notez que lorsqu'une tâche essaie de prendre un sémaphore avec le compteur de sémaphore égal à 0, elle reste bloquée jusqu'à ce que le compte de sémaphore soit incrémenté par une autre tâche ou qu'un délai d'attente défini se produise.

Nous allons commencer notre code en déclarant une **variable globale** pour y enregistrer le nombre de tâches à lancer. Nous allons lancer notre exemple avec 4 tâches.

Ensuite, nous allons déclarer un **counting semaphore** comme une variable globale. Cette variable peut être consultée à la fois par la fonction de setup() et les tâches.

Nous créons le sémaphore avec la fonction xSemaphoreCreateCounting(). Cette fonction reçoit comme arguments d'entrée le nombre maximal que le sémaphore peut atteindre et sa valeur initiale.
Puisque nous l'utilisons à des fins de synchronisation, nous spécifierons un nombre maximum égal au nombre de tâches à lancer et l'initialiserons à 0
```c
int nTasks=4;
SemaphoreHandle_t barrierSemaphore = xSemaphoreCreateCounting(nTasks,0);
```
Dans le setup() nous écrivons une boucle pour lancer nos tâches. Notez que nous pouvons utiliser la même fonction de tâche pour lancer plusieurs tâches, nous n'avons donc pas besoin d'implémenter du code pour chaque nouvelle tâche.
Nous allons créer les tâches avec la priorité 0. La fonction de setup() s'exécute avec une priorité de 1. Etant donné que les tâches ont une priorité inférieure, elles ne fonctionneront que si la fonction de setup() est bloquée et nous nous attendons à ce qu'elle bloque sur notre sémaphore.

Pour différencier les tâches, nous allons passer le numéro de l'itération de la boucle comme un paramètre d'entrée, afin qu'ils puissent l'imprimer dans leur code..
Notez que nous allons passer un pointeur sur la position mémoire de la variable d'itération et non sur sa valeur réelle. Néanmoins, cela ne posera pas de problème puisque les tâches doivent s'exécuter et utiliser cette valeur avant que la fonction de setup() ne se termine pas , et ainsi, la mémoire de la variable sera toujours valide.


# Changelog

**07/01/2020 : ** Ajout Sémaphore de comptage. 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


