# Notifications de tâche

Des événements peuvent être envoyés à une tâche à l'aide d'un objet intermédiaire, comme par exemple les files d'attente, les sémaphores, les mutex et les groupes d'événements.
Les **"notifications de tâche"**  fournissent une alternative légère aux groupes d'événements dans de nombreuses situations.

## Introduction

Les notifications de tâche sont une méthode d'envoi d'un événement directement à une tâche sans avoir besoin d'un tel objet intermédiaire. Le déblocage d'une tâche  avec une notification directe est **45 % plus rapide** et **utilise moins de RAM** que le déblocage d'une tâche à l'aide d'un objet intermédiaire tel qu'un sémaphore binaire.
Toutefois  les notifications de tâche  ne peuvent être utilisées que lorsqu'une seule tâche doit être le destinataire de l'événement. Cette condition est cependant remplie dans la majorité des cas d'utilisation du monde réel, comme une interruption débloquant une tâche qui traitera les données reçues par l'interruption.

Les notifications de tâche peuvent être utilisées pour envoyer des données à une tâche. Une notification envoyée à une tâche restera en attente jusqu'à ce qu'elle soit effacée par la tâche en appelant la fonction `xTaskNotifyWait()`

Une tâche peut utiliser `xTaskNotifyWait()` pour passer à l'état bloqué et attendre qu'une notification lui soit envoyée *(La tâche ne consomme pas de temps CPU tant qu'elle est à l'état Bloqué)*

## Envoyer une notification

Les notifications sont envoyées à l'aide des fonctions `xTaskNotify()`  ou `xTaskNotifyGive()`

Exemple d'utilisation:
Envoie une notification à la tâche référencée par xTask2Handle, supprimant potentiellement la tâche de l'état Bloqué, mais sans mettre à jour la  valeur de notification de la tâche. `xTaskNotify( xTask2Handle, 0, eNoAction );`

Définit la valeur de notification de la tâche référencée par loopTaskHandle sur receivedValue,  même si la tâche n'a pas lu sa valeur de notification précédente. 
`xTaskNotify(loopTaskHandle, receivedValue , eSetValueWithOverwrite);`

la fonction `xTaskNotifyGive()`  est utilisée lorsqu'une notification de tâche est utilisée comme alternative de sémaphore binaire. la tâche notifiée doit attendre la notification à l'aide de la fonction API `ulTaskNotifyTake()`

## Recevoir une notification
Les notifications sont reçues à l'aide des fonctions `xTaskNotifyWait()` ou son alternative `ulTaskNotifyTake()`

```cpp
if (xTaskNotifyWait(0, ULONG_MAX, &receivedValue, 1000) == pdPASS) {

   Serial.printf("Notification pour Tache 2 : Valeur reçue = %d\r\n", receivedValue);
}
```

| parametre |  signification |
|-----|------|
|**0**| Index dans le tableau de valeurs de notification | 
| **ULONG_MAX** |La définition de ulBitsToClearOnEntry sur 0xffffffff (ULONG_MAX) effacera tous les bits de la valeur de notification de la tâche, effaçant ainsi la valeur|
|**&receivedValue**| Utilisé pour transmettre la valeur de notification de la tâche.|
|**1000**| Le temps d'attente maximal dans l'état Bloqué pour qu'une notification soit reçue |

**Valeur de retour  : **
`pdTRUE` si une notification a été reçue ou si une notification était déjà en attente lorsque xTaskNotifyWait() a été appelée.


`pdFALSE` si l'appel à xTaskNotifyWait() a expiré avant la réception d'une notification.

**Autre Exemple d'utilisation :**
```cpp
void tache3( void *pvParameters ) 
{ 
uint32_t ulNotifiedValue; 

    for( ;; ) 
    { 
        /* Bloquer indéfiniment (sans délai, donc pas besoin de vérifier la 
        valeur de retour de la fonction) pour attendre une notification. 

        Les bits de la valeur de notification de cette tâche RTOS sont définis par les tâches de notification 
        et les interruptions pour indiquer les événements qui se sont produits. */ 
        xTaskNotifyWaitIndexed( 0,          /* Attendre la 0ème notification. */
                                0x00,       /* N'efface aucun bit de notification à l'entrée. */ 
                                ULONG_MAX, /* Réinitialise la valeur de notification à 0 à la sortie. */ 
                                &ulNotifiedValue, /* La valeur notifiée passe dans 
                                                     ulNotifiedValue. */ 
                                portMAX_DELAY );  /* Bloquer indéfiniment. */ 

        /* Traite tous les événements qui ont été verrouillés dans la valeur notifiée. */
 
        if( ( ulNotifiedValue & 0x01 ) != 0 ) 
        { 
            /* Le bit 0 a été défini - traite l'événement représenté par le bit 0. */ 
            prvProcessBit0Event(); 
        }

        if( ( ulNotifiedValue & 0x02 ) != 0 ) 
        { 
            /* Le bit 1 a été défini - traite l'événement représenté par le bit 1. */ 
            prvProcessBit1Event(); 
        } 

        if( ( ulNotifiedValue & 0x04 ) != 0 ) 
        { 
            /* Le bit 2 a été défini - traite l'événement représenté par le bit 2. */ 
            prvProcessBit2Event(); 
        } 

        /* Etc. */ 
    } 
}
```


# Changelog

**31/07/2022 : ** Creation du README.md 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


