# Généralités sur les sémaphores

## Présentation

Un sémaphore est un mécanisme empêchant deux processus ou plus d’accéder simultanément à une ressource partagée. Sur les voies ferrées, un sémaphore empêche deux trains d’entrer en collision sur un tronçon de voie commun.
Sur les voies ferrées comme dans les ordinateurs, les sémaphores ne sont qu’indicatifs :

 - Si un machiniste ne voit pas le signal ou ne s’y conforme pas, le sémaphore ne pourra éviter la collision.

 - De même si un processus ne teste pas un sémaphore avant d’accéder à
   une ressource partagée, le chaos peut en résulter.

Un sémaphore binaire n’a que deux états :

 - 0 verrouillé (ou occupé),
 - 1 déverrouillé (ou libre).

Un sémaphore général peut avoir un très grand nombre d’états car il s’agit d’un compteur dont la valeur initiale peut être assimilée au nombre de ressources disponibles.
Par exemple, si le sémaphore compte le nombre d’emplacements libres dans un tampon et qu’il y en ait initialement 5 on doit créer un sémaphore général dont la valeur initiale sera 5. Ce compteur :

 - Décroît d’une unité quand il est acquis (” verrouillé ”).
 - Croît d’une unité quand il est libéré (” déverrouillé ”).

Quand il vaut zéro, un processus tentant de l’acquérir doit attendre qu’un autre processus ait augmenté sa valeur car il ne peut jamais devenir négatif.

L’accès à un sémaphore se fait généralement par deux opérations :

 - **P** : pour l’acquisition
 - **V** : pour la libération

Un moyen mnémotechnique pour mémoriser le P et le V est le suivant :

 - P(uis-je) accéder à une ressource.
 - V(as-y) la ressource est disponible.

## Un mécanisme fourni par le noyau
La notion de sémaphore est implémentée dans la plupart des systèmes d’exploitation. Il s’agit d’un concept fondamental car il permet une solution à la plupart des problèmes d’exclusion.
Ce concept nécessite la mise en œuvre d’une variable, le sémaphore, et de deux opérations atomiques associées P et V.
Soit **sema** la variable, elle caractérise les ressources et permet de les gérer. Lorsqu’on désire effectuer un exclusion mutuelle entre tous les processus par exemple, il n’y a virtuellement qu’une seule ressource
et on donnera à **sema** la valeur initiale de 1.
P(sema) correspond à une prise de ressource et V(sema) à une libération de ressource.

## Manipulation de sémaphores freeRTOS:

 - Opération P : 
 
 `xSemaphoreTake(descripteur, nbrTicksAttente)` .
   Décrémente ou ferme le sémaphore désigné par son descripteur, cette opération est bloquante jusqu’à ce que le sémaphore puisse être décrémenté ou fermé. La valeur de retour est pdPASS si le sémaphore a bien été modifié et pdFAIL s’il ne l’a pas été à la fin du délai d’attente. Le délai d’attente est défini par nbrTicksAttente en  unités de temps (5 ms) ou infini si ce paramètre vaut portMAX_DELAY,    dans ce cas la valeur de retour ne pourra être que pdPASS puisque  sinon la tâche est bloquée.
   
 - Opération V : 
 
  `xSemaphoreGive(descripteur)
   xSemaphoreGiveFromISR(descripteur, NULL) `
   Incrémente ou ouvre le   sémaphore désigné par son descripteur, cette opération peut être   bloquante pour un sémaphore compteur qui a atteint sa valeur    maximale. La valeur de retour est pdPASS si le sémaphore a bien été    incrémenté ou ouvert et pdFAIL s’il ne l’a pas été parce que la tâche  ne l’avait pas fermé (pour les Mutex seulement).
   
 - Suppression : 

    `vSemaphoreDelete(descripteur)`
  Supprime le sémaphore   désigné par son descripteur

 - Etat : 
   `xSemaphoreGetCount(descripteur) `
   Renvoie la valeur actuelle   du sémaphore


# Changelog

**08/01/2020 : ** Ajout du README . 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


