# Sémaphore de comptage

## Description
Les sémaphores sont généralement utilisés à la fois pour la synchronisation et l'exclusion mutuelle dans l'accès aux ressources. Nous allons développer une application simple où nous utiliserons un sémaphore de comptage comme barrière d'exécution.

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


