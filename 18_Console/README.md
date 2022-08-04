# Classe Console


La classe **Console** est utilisée pour analyser et gérer les commandes de l'interface de la console utilisateur basée sur différentes interfaces (port série, telnet, etc.).
 Elle implémente le format de ligne de commande suivant : 
 ```
  <commande>[ <arg1>[ <arg2>[ ...]]]
 ```
## Installation avec platformio

installation en tant que lib globale: 
```bash
pio pkg install --global --library akoro/Console@^1.2.1
```
 
  Avec NetBeans ajouter le chemin vers la library dans 
  Tools -> Options -> C/C++ ->  code assistance
 Pour mon PC la library se trouve dans 
 ```
   /home/philippe/.platformio/lib/Console/src 
 ``` 
 
 des informations sont disponibles sur le github de l'auteur
 https://github.com/akoro/Console
 
