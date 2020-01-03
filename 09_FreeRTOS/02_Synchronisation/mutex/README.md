# Mutex

## Introduction
Un sémaphore de type **mutex** est comme une clé associée à la ressource. La tâche qui contient la clé, verrouille la ressource, la traite, puis déverrouille et restitue la clé pour que d'autres tâches puissent l'utiliser.
Ce mécanisme est similaire au sémaphore binaire sauf que la tâche qui prend la clé **doit libérer la clé**.

Le mutex est le **meilleur choix pour implémenter une exclusion mutuelle simple**.
La priorité d'une tâche qui «prend» un mutex sera temporairement augmentée si une autre tâche de priorité plus élevée tente d'obtenir le même mutex. La tâche qui possède le mutex «hérite» de la priorité de la tâche qui tente de «prendre» le même mutex. Cela signifie que le mutex doit toujours être «rendu» - sinon la tâche de priorité supérieure ne pourra jamais obtenir le mutex, et la tâche de priorité inférieure ne «déshéritera» jamais la priorité.

Les mutex sont créés en utilisant **xSemaphoreCreateMutex()** , chaque mutex nécessite une petite quantité de RAM qui est utilisée pour maintenir l'état du mutex.
Les mutex sont pris en utilisant **xSemaphoreTake()** et donnés en utilisant **xSemaphoreGive()** .

Les mutex ne peuvent pas être utilisés dans les routines de service d'interruption.


## Exemple 
Dans  l'exemple proposé, nous créons 2 tâches:  une tâche de faible priorité et une tâche de haute priorité. La tâche de faible priorité conservera la clé et bloquera la tâche de haute  priorité.

# Changelog

**31/12/2019 : ** Ajout du README . 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


