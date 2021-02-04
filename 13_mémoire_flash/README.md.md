# La Mémoire flash
## Introduction
Tout d'abord faisons un petit tour d'horizon des mémoires disponibles sur le micro-contrôleur Esp32.

L'Esp32 dispose  d'une mémoire de type  **RAM**. Cette memoire est extrêmement rapide, mais aussi extrêmement volatile, c'est a dire que les données stockées dessus on une durée de vie très courte. C'est ici que sont stockées les variables de notre programme par exemple. Il n'est pas possible de l'utiliser pour stocker sur une longue durée car elle est vidée à chaque reboot, en cas de plantage, et même en cas de mise en veille (deepsleep) de la puce.

L'Esp32 dispose aussi d'une mémoire  **RAM type RTC**. C'est a dire un espace mémoire qui est persistant au reboot, mais qui sera toujours perdu en cas de coupure de courant. Habituellement cet espace de stockage sert a conserver l'horloge interne entre les deepsleep, mais sur ESP on peut y stocker des données librement pendant un court laps de temps (quelques minutes).  Attention, en cas de plantage et/ou de coupure totale, cette mémoire est perdue, de plus la librairie rtcfifo ajoute d'autres limitations.

Enfin, la puce dispose aussi d'un module mémoire  **flash**. Cet espace de stockage est persistant, même en cas de coupure de courant. C'est d'ailleurs ici que l'on charge le code du programme qui sera exécuté. En contrepartie, ce type de mémoire est très long à accéder à la fois en lecture et en écriture. Autre bémol important, cette mémoire  **s'use à l'écriture**  (100.000 cycles environ).

https://techtutorialsx.com/2018/08/05/esp32-arduino-spiffs-writing-a-file/


# Changelog

**19/01/2021 : ** Ajout du README . 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#



