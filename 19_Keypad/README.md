# Le clavier (Keypad)

Le clavier numérique est un ensemble de 12 boutons qui sont montés sous forme de matrice.
![le clavier](/19_Keypad/Keypad-Symbolic.png) 

## Raccordement

Vous n'aurez pas besoin de résistances  externes car la bibliothèque utilise les résistances de rappel internes de ESP32 et garantit en outre que toutes les broches de colonne inutilisées sont à haute impédance.

 ![le clavier](/19_Keypad/esp32_keypad.jpg) 

## Installation de la bibliothèque Keypad avec platformIO

**Keypad** est une bibliothèque permettant d'utiliser simplement les claviers de style matriciel.
Elle a été créée pour améliorer la lisibilité du code tout en masquant les appels pinMode et digitalRead pour l'utilisateur.

Sur platformIO  Keypad possède l'identifiant **165**. Elle s'installe en utilisant la commande suivante.
``` 
pio lib install 165
```
Dans votre programme principal vous pouvez inclure la bibliothèque
```
#include <Keypad.h>
```
Ne pas oublier de renseigner le répertoire src de la bibliothèque dans "code assistance" pour permettre la reconnaissance du "**#include <Keypad.h>**" et la complétion de code.
### Le constructeur
```cpp
const byte ROWS = 4; // Déclaration du nombre de lignes
const byte COLS = 3; // Déclaration du nombre de colonnes

// Déclaration des caractères sur les touches
char keys[ROWS][COLS] = {
{'1', '2', '3'},
{'4', '5', '6'},
{'7', '8', '9'},
{'*', '0', '#'}
};

//affectation des GPIO au R1,R2,R3,R4 du clavier
byte rowPins[ROWS] = {23, 22, 3, 21};
//affectation des GPIO au C1,C2,C3 du clavier
byte colPins[COLS] = {19, 18, 5};

Keypad clavier = Keypad((char *) keys, rowPins, colPins, ROWS, COLS);

``` 
 
### Les méthodes

```char getKey() ``` 
Renvoie le code de la  touche enfoncée, si aucune touche n'est enfoncée renvoie NO_KEY. Cette fonction est non bloquante.

```char waitForKey() ```
Cette méthode attendra indéfiniment jusqu'à ce que quelqu'un appuie sur une touche. Attention la méthode bloque tous le code de la tâche en cours d’exécution jusqu'à ce qu'une touche soit enfoncée.

