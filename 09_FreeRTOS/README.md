# Programmation temps réel avec FreeRTOS 

## 1 Introduction
**FreeRTOS** est un système d’exploitation temps réel (RTOS) open source de faible empreinte et portable. Il fonctionne en mode préemptif. Il a été porté sur dizaines d’architectures différentes. Créé en 2003 par Richard Barry et la FreeRTOS Team, il est aujourd’hui parmi les plus utilisés dans le marché des systèmes d'exploitation temps réel.

FreeRTOS est disponible gratuitement sous une licence GPL modifiable et utilisable sans paiement de redevances, cette licence n’oblige pas les développeurs à publier le code de leurs logiciels applicatifs mais impose de garder le noyau de FreeRTOS Open Source.

L’unité d’exécution contrôlée par FreeRTOS est une **tâche**. Le nombre de tâches exécutées simultanément et leur priorité ne sont limités que par le matériel.
L'ordonnancement est un système de file d'attente basé sur les **Sémaphores** et les **Mutex**. Il fonctionne selon le modèle **Round-Robin** avec gestion des priorités. Conçu pour être très compact, il n'est composé que de quelques fichiers en langage C, et n'implémente aucun driver matériel.

Les domaines d'applications sont assez larges, car les principaux avantages de FreeRTOS sont l’exécution temps réel, un code source ouvert et une taille très faible. Il est donc utilisé principalement pour les systèmes embarqués qui ont des contraintes d'espace pour le code, mais aussi pour des systèmes de traitement vidéo et des
applications réseau qui ont des contraintes "temps réel".

Bien évidement parmi les application les plus récentes et le plus exigeantes par rapport à la gestion des activités en temps réel sont les architectures d’objets connectés dans l’IoT (Internet of Things).

## 2 L’ordonnanceur
L’ordonnanceur (scheduler) des tâches a pour but principal de décider parmi les tâches qui sont dans l'état **prêt**, laquelle exécuter. Pour faire ce choix, l'ordonnanceur de FreeRTOS se base uniquement sur la priorité des tâches. Les tâches en FreeRTOS se voient assigner à leur création, un **niveau de priorité** représenté par un nombre entier. Le niveau le plus bas vaut zéro et il doit être strictement réservé pour la tâche **Idle**. Plusieurs tâches peuvent appartenir à un même niveau de priorité.

Dans FreeRTOS Il n'y a aucun mécanisme automatique de gestion des priorités (cas du système Linux) . La priorité d'une tâche ne pourra être changée qu'à la demande explicite du développeur. Les tâches sont de simples fonctions qui généralement , mais pas exclusivement, s’exécutent en boucle infinie.

Dans le cas d'un micro-contrôleur possédant un seul coeur (AVR,ARM-Cortex4,ESP12,..) , il y aura à tout moment **une seule tâche en exécution**. L’ordonnanceur garantira toujours que la tâche de plus haute priorité pouvant s’exécuter sera sélectionnée pour entrer dans **l'état d’exécution**. Si deux tâches partagent le même niveau de priorité et sont toutes les deux capables de s'exécuter, alors les deux tâches s'exécuteront **en alternance** par rapport aux **réveils de l’ordonnanceur (tick)**.

Afin de choisir la tâche à exécuter, l'ordonnanceur doit lui-même s'exécuter et préempter la tâche en état d'exécution. Afin d'assurer le réveil de l'ordonnanceur, FreeRTOS définit une interruption périodique nommé la "tick interrupt". Cette interruption s'exécute infiniment selon une certaine fréquence qui est définie dans le fichier FreeRTOSConfig.h par la constante :
```c
configTICK_RATE_HZ // tick frequency interrupt" in Hz
```
Cette constante décrit alors la période de temps allouée au minimum pour chaque tâche ou expliqué autrement, l'intervalle séparant deux réveils de l’ordonnanceur.

Principalement FreeRTOS utilise un ordonnancement **préemptif** pour gérer les tâches.

## 3 La tâche IDLE
Un micro-contrôleur doit toujours avoir quelque chose à exécuter. En d'autres termes, il doit toujours y avoir une tâche en exécution. FreeRTOS gère cette situation en définissant la **tâche IDLE** qui est créée au lancement de l’ordonnanceur. La plus petite priorité du noyau est attribué à cette tâche. Malgré cela, la tâche IDLE peut avoir plusieurs fonctions à remplir dont:

 - libérer l'espace occupé par une tâche supprimée ;
 - placer le micro-contrôleur en veille afin d'économiser l'énergie du système lorsque aucune tâche applicative n'est en exécution ;
 - mesurer le taux d'utilisation du processeur.

# Changelog

**27/12/2019 : ** Ajout du README . 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


