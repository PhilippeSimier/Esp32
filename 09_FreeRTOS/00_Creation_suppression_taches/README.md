# Tâche

## Introduction

Une tâche est une fonction C en cours d’exécution qui possède ses propres droits .
Cette fonction C comprend une boucle infinie. On ne peut donc pas en sortir  et il n'y a pas de RETURN.  Cependant on doit l'effacer si elle n'est plus utile en appelant **vTaskDelete(NULL)**. NULL est un paramètre que fait référence à la tâche elle même.

Une tâche est une instance indépendante composée :
 - De sa propre pile
 - De sa propre copie de toutes les variables locales à la tâche

Une seule définition de fonction tâche peut être utilisée pour créer plusieurs tâches.
Un prototype de la fonction tâche doit :

 - Avoir un paramètre de type  pointeur générique void *
 - pas de retour **void**
 
 Exemple de code
```c
void taskFunction (void *pvParameters)
{
/*
Les variables sont déclarées comme dans une fonction classique
Chaque instance de tâche créée utilisant la fonction aura sa propre copie de la variable i (sauf si déclarée en static) */

  int i=0 ;
  // une tâche est normalement implantée dans une boucle infinie
  For(;;) //ou while(1)
  {
    /*code de la tâche ici */
    i=i+3 ; //exemple
  }
 
  /* si pas de boucle infinie il faut effacer la tâche*/
  vTaskDelete(NULL) ;
  /* NULL est un paramètre que fait référence à la tâche elle même.
}
```

## Création

Lors de la création d'une tâche, le noyau alloue un espace mémoire TCB  (task control block) qui contient : l'identifiant, la priorité, les droits, l'état et la taille de la pile allouée.

La fonction de création de tâche  **xTaskCreate()** utilise 6 paramètres et
retourne une valeur de type "portBASE_TYPE" :

### Paramètres

 - **taskFunction** : pointeur sur la fonction implémentant la tâche

 - **''Tache 1''** : chaîne de caractères associée à la tâche (sauvée dans
   la TCB). Utilisé par des outils de trace.
 - **configMINIMAL_STACK_SIZE** : taille de la pile associée à la tâche.
   Cette macro est définie dans le fichier FreeRTOSConfig.h. Il s'agit   par défaut de la taille de la pile pour la tâche Idle. 
   Attention, cette taille est donnée en ''Words'' et non en octets. La taille d'un Word dépend de l'architecture matérielle utilisée. 
   
 - **pvParametersTask1** : pointeur permettant de passer un paramètre à la
   tâche NULL s’il n’y en a pas.

 - **tskIDLE_PRIORITY + 1** : priorité de la tâche. tskIDLE_PRIORITY ou
   ''0'' est la priorité minimale qui correspond à la priorité de la  tâche Idle. La priorité maximale vaut configMAX_PRIORITIES définie  dans FreeRTOSConfig.h.

 - **NULL** : pointeur de préemption sur les tâches Lorsque ce pointeur vaut
   "NULL" il pointe sur la tâche elle-même en cours de création. A
   manipuler avec précaution.

###  Valeur retournée
L'instruction **xTaskCreate()** retourne une valeur de type **portBASE_TYPE** qui
peut prendre 2 valeurs possibles :

 - **pdTRUE** : tout c’est bien passé
 - **errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY** : la tâche n'est pas créée car il manque de la place en mémoire.

##  Création de plusieurs instances d'une même fonction
Si on crée 2 instances de la même tâche on crée 2 zones TCB + pile. Chaque instance est indépendante : elles sont gérées indépendamment et ont leurs propres variables : ce sont des variables locales, sauf si on les déclare « **static** » auquel cas la variable est partagée entre les différentes instances de la tâche.

Exemple de création de 2 tâches totalement indépendantes utilisant la même
fonction taskFunction :
```c
xTaskCreate( taskFunction, "instance1DeTask1" , 1024, NULL, 2, NULL);
xTaskCreate( taskFunction, "instance2DeTask1" , 1024, NULL, 2, NULL);  
```

# Changelog

**31/12/2019 : ** Ajout du README . 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


