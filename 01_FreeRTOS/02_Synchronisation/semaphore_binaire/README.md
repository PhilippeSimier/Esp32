# Sémaphores

## Introduction

Les sémaphores permettent de construire les schémas de **synchronisation** et de **protection pour les sections partagées** (critiques) du code.
Dans cette section nous allons présenter plusieurs types de sémaphores :

 - sémaphore binaire
 -  mutex
 - sémaphore de comptage

Les sémaphores binaires et mutex  sont très similaires mais présentent quelques différences subtiles: le mutex inclue un mécanisme d'héritage prioritaire, le sémaphore binaire non. 
Cela fait des **sémaphores binaires** le meilleur choix pour implémenter la **synchronisation** (entre les tâches ou entre les tâches et une interruption), et **mutex** le meilleur choix pour implémenter une **exclusion mutuelle simple**.


## Sémaphore binaire

Les fonctions de l'API Sémaphore permettent de spécifier un temps d'attente. Le temps de blocage indique le nombre maximal de «ticks» qu'une tâche doit attendre dans l'état Bloqué lorsqu'elle tente de «prendre» un sémaphore, si le sémaphore n'est pas immédiatement disponible. 
Si plusieurs tâches bloquent sur le même sémaphore, alors la tâche avec la priorité la plus élevée sera la tâche qui sera débloquée la prochaine fois que le sémaphore sera disponible.
Considérez un **sémaphore binaire** comme une file d'attente qui ne peut contenir qu'un seul élément. La file d'attente ne peut donc être que vide ou pleine (donc binaire). Les tâches et les interruptions utilisant la file d'attente ne se soucient pas de ce que la file d'attente contient - elles veulent seulement savoir si la file d'attente est vide ou pleine. Ce mécanisme peut être exploité pour synchroniser (par exemple) une tâche avec une interruption.
Prenons le cas où une tâche est utilisée pour lire un périphérique. L'interrogation du périphérique serait une perte de ressources CPU et empêcherait l'exécution d'autres tâches. Il est donc préférable que la tâche passe la plupart de son temps à l'état Bloqué (permettant à d'autres tâches de s'exécuter) et ne s'exécute que lorsqu'elle a réellement quelque chose à faire. Ceci est réalisé en utilisant un sémaphore binaire. Une routine d'interruption est alors écrite pour le périphérique qui «donne» simplement le sémaphore lorsque le périphérique nécessite une lecture. 
La tâche «prend» toujours le sémaphore (lit dans la file d'attente pour rendre la file d'attente vide), mais ne la «donne» jamais. L'interruption «donne» toujours le sémaphore (écrit dans la file d'attente pour le remplir) mais ne le prend jamais.

![enter image description here](/09_FreeRTOS/02_Synchronisation/semaphore_binaire/binary-semaphore.gif)


# Changelog

**31/12/2019 : ** Ajout du README . 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


