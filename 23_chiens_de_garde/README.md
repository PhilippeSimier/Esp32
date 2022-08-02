# Chien de garde 


## Introduction
La fonctionnalité de surveillance (WDT) est une fonctionnalité importante pour les puces tels que l'ESP32  qui doivent se rétablir automatiquement de toutes sortes de pannes logicielles inattendues.
ESP32 prend en charge un chien de **garde d'interruption IWDT** et une **API de minuterie de chien de garde de tâche. TWDT**
Sa fonction est de s'assurer que l'ESP32 ne reste pas bloqué à une étape particulière du traitement qu'il effectue. 
Le chien de garde d'interruption est responsable de la détection des instances où la commutation de tâches FreeRTOS est bloquée pendant une période prolongée. Le TWDT est responsable de la détection des instances de tâches n'est pas exécutées   pendant une période prolongée.
Autrement dit, c'est une protection destinée  à redémarrer le programme, si une tâche est bloquée. Cela peut être un indicateur d'un code  qui tourne en boucle sur un périphérique ou d'une tâche bloquée dans une boucle infinie.

## Usage

L' en-tête `esp_task_wdt.h` doit être inclus
```cpp
	#include <esp_task_wdt.h>
```
Dans la fonction **setup**, appeler les deux fonctions :

```cpp
	esp_task_wdt_init(uint32_t timeoutSeconds, bool panic)
```
et
```cpp
	esp_task_wdt_add(TaskHandle_t handle)
```

-   _esp_task_wdt_init_ est utilisé pour initialiser WDT avec un délai d'attente de _timeoutSeconds_ et avec un mode _panique_ défini. Si _panic_ est défini sur _true_ , lorsque WDT expire, celà déclenche une panique matérielle et le redémarrage du programme.
-   _esp_task_wdt_add_ est utilisé pour ajouter une tâche à WDT. Si _handle_ est _NULL,_ la tâche en cours est utilisée.

Dans la fonction **loop** de la tâche surveillée, la minuterie du chien de garde doit être réinitialisée _AVANT_ qu'elle n'expire ! Cela se fait avec

```cpp
	esp_task_wdt_reset ()
```





# Changelog

**02/08/2022 : ** Creation du README.md 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


