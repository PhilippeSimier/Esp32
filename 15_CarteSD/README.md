#  Carte SD

## Introduction
Cette classe permet l'intégration des cartes  SD (Secure Digital) avec ESP32.


## Câblage avec carte adaptateur (5V)
La carte d'adaptation possède un régulateur de tension 5V -> 3.3V
Les entrées sorties de la carte SD sont amplifiées (74VHC125 Quad Buffer) 

![Câblage Module SD](/15_CarteSD/documentation/Cablage.png)

Avec l'affectation des broches standard de la liaison SPI de l'esp32 (carte ruche)
-  SCK		**18**
 - MISO   **19**
 - MOSI	**23**
 - CS		**5**

## Câblage direct (3.3V)
Il est possible de connecter directement la carte SD

![Câblage Module SD](/15_CarteSD/documentation/Cablage_direct.png)


## Diagramme de classes
Plusieurs classes sont proposées pour gérer les fichiers sur une carte SD.
Nous avons la classe SDFS qui dérive de la classe FS (File System). Cette classe possède des méthodes pour ouvrir un fichier, renommer, supprimer, créer et supprimer un répertoire.
La méthode open de FS renvoie un fichier (objet de type File) sur lequel on peut lire écrire des données.
La classe File  dérive de la classe Stream qui dérive elle même de la classe Print.

![Diagramme de classe](/15_CarteSD/documentation/diagramme_SD.png)

