# Communication entre deux tâches
## Files d'attente

Dans l’exemple suivant nous allons exploiter le capteur de la température/humidité/pression BME280.

L'exemple met en oeuvre trois tâches :

 - Une tâche **sensorTask()** chargé de placer, à intervalle de temps régulier, dans une file les valeurs mesurées par le capteur BME280.  
 - Une tâche arduino **loop()** consomme les valeurs placées dans la liste afin de les afficher sur la console.
 - Une tâche blinkTask() chargé de faire clignoter la led intégrée.
 
 ![enter image description here](/09_FreeRTOS/01_Communication_entre_taches/05_Exemple_BME280_2_Coeurs/schema.JPG) 

# Changelog

**27/12/2019 : ** Ajout du README . 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


