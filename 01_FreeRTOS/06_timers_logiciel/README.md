# Timers logiciel 


## Introduction

Les temporisateurs logiciels (_timers_) sont utilisés pour planifier l’exécution d’une fonction après un temps défini ou périodiquement avec une période fixe. La fonction exécutée est appelée fonction de rappel (_callback_) du temporisateur logiciel.

_Remarque :_  les temporisateurs logiciels sont implémentés par FreeRTOS et sont sous son contrôle. Ils ne nécessitent pas de prise en charge matérielle et ne sont pas liés aux temporisateurs ou compteurs matériels.

## Principe de fonctionnement
Le schéma suivant donne un aperçu de la manière dont les timers logiciels dans FreeRTOS sont implémentés :

![freestos-software-timers](/01_FreeRTOS/06_timers_logiciel/freertos-software-timers.webp)

Une tâche dédiée au service des timers **Tmr Svc** est chargée de gérer tous les timers logiciels FreeRTOS du système.
Elle maintient une liste ordonnée des timers logiciels,  La tâche Timer Service ne s'exécute pas en continu car à partir de la liste des timers, elle connaît l'heure à laquelle elle doit se réveiller (correspondant à l'expiration d'un timer). Lorsqu'un timer a expiré, la tâche du service des timers appelle sa fonction callback.

Une file d'attente est utilisée pour la communication inter-processus. Ainsi d'autres tâches peuvent envoyer des commandes à la tâche de minuterie, par exemple pour démarrer ou arrêter un timer.

## Type de timer

Les timers logiciels FreeRTOS prennent en charge deux types de timers logiciels différents, configurés au moment de la création du minuteur :

-   **One-Shot** : lorsque le timer expire, il n'est pas redémarré automatiquement. Toutefois on peut toujours le redémarrer par programme ultérieurement.
-   **Redémarrage automatique** : ce timer sera automatiquement redémarré lorsqu'il expirera, ce qui le rend idéal pour effectuer des actions périodiques.

![freestos-software-timers](/01_FreeRTOS/06_timers_logiciel/timers_state.png)
 
## Usage
####  Création d'un timer logiciel
Les temporisateurs sont référencés par des variables de type `TimerHandle_t` et créés par la fonction `xTimerCreate()`.
La fonction **xTimerCreate()** crée uniquement le timer, elle ne le démarre pas.

Exemple de code
```cpp
TimerHandle_t  timerPeriodique;

// Création du timer périodique 1 seconde
    timerPeriodique = xTimerCreate(
            "AutoReload", 
            pdMS_TO_TICKS(1000), 
            pdTRUE, 
            (void*)2, 
            autoReloadTimerCallback);
    if (timerPeriodique==NULL) { 
	    for(;;); /* échec! */  
	}        
```
Le premier paramètre est une chaîne pour le nom du timer, suivi de la période (initiale) du temporisateur en ticks. 
Le paramètre suivant avec 'pdTRUE' demande un timer avec 'rechargement automatique', ce qui signifie que le timer est un timer périodique. 
Ensuite,  un ID de timer (pointeur vers void) et enfin la chose la plus importante : le callback du timer. Le callback est la fonction qui sera appelée à l'expiration du délai.
Étant donné qu'une création de timer peut échouer (par exemple, manquer de mémoire), il est vivement recommandé de vérifier le descripteur de temporisateur renvoyé.

####  La fonction de callback
Comme les callback de timer sont appelés à partir de la tâche du service de timer, il est important que la fonction de callback ne se bloque pas (par exemple, attend un certain temps ou attend un sémaphore), car sinon toutes les autres minuteries seront retardées. Ainsi, la règle générale pour une fonction de rappel de temporisateur (comme pour les routines de service d'interruption) est la suivante : soyez bref et simple !
```cpp
void autoReloadTimerCallback(TimerHandle_t xTimer) {
   
    TickType_t xTimeNow = xTaskGetTickCount();
    digitalWrite(LED, digitalRead(LED) ^1);   // turn the LED 
    Serial.printf("autoReloadTimerCallback - %d\r\n", xTimeNow);
}
```
#### Démarrage d'une minuterie

Un timer précédemment créé avec xTimerCreate() démarre avec **xTimerStart()**

```cpp
	if (xTimerStart(timerPeriodique, 0)!=pdPASS) {
		for(;;); /* échec!?! */
    }
```
0 spécifie combien de temps l'appelant doit attendre si la file d'attente des timers est déjà pleine.

#### Réinitialiser un timer
On réinitialise un timer avec **xTimerReset()**. Un tmer peut être réinitialisé. Et si ce timer n'a pas déjà été démarré, il démarrera.


#### Conclusion 

Les temporisateurs logiciels sont très utiles : on peux implémenter plusieurs temporisateurs périodiques ou ponctuels pour gérer un délai d'expiration avec une seule tâche de temporisateur (démon). De cette façon, on n'a pas besoin de minuteries matérielles supplémentaires et on utilise moins de ressources que d'utiliser une tâche pour chaque action périodique.
# Changelog

**02/08/2022 : ** Creation du README.md 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


