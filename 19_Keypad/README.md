# Le clavier (Keypad)

Le clavier numérique est un ensemble de 12 boutons qui sont montés sous forme de matrice.
![le clavier](/19_Keypad/Keypad-Symbolic.png) 

## Raccordement

Vous n'aurez pas besoin de résistances  externes car la bibliothèque utilise les résistances de rappel internes de ESP32 et garantit en outre que toutes les broches de colonne inutilisées sont à haute impédance.

 ![le clavier](/19_Keypad/esp32_keypad.jpg) 

## Installation de la bibliothèque Keypad avec platformIO

**Keypad** est une bibliothèque permettant d'utiliser simplement les claviers de style matriciel.
Elle a été créée pour améliorer la lisibilité du code tout en masquant les appels pinMode et digitalRead pour l'utilisateur.

Sur platformIO  Keypad possède l'identifiant **chris--a/Keypad**. Elle s'installe en tant que bibliothèque globale en utilisant la commande suivante.
``` 
pio pkg search "header:Keypad.h"
chris--a/Keypad
Library • 3.1.1 • Published on Fri Mar  4 14:20:03 2016
Keypad is a library for using matrix style keypads with the Arduino. As of version 3.0 it now
supports mulitple keypresses. This library is based upon the Keypad Tutorial. It was created to
promote Hardware Abstraction. It improves readability of the code by hiding the pinMode and
digitalRead calls for the user.

pio pkg install --library chris--a/Keypad

```
Dans votre programme principal vous devez inclure la bibliothèque
```
#include <Keypad.h>
```
Ne pas oublier de renseigner le répertoire src de la bibliothèque dans "code assistance" pour permettre la reconnaissance du "**#include <Keypad.h>**" et la complétion de code.

### Le constructeur
```cpp
#define CONNECTEUR_BAS   // Définit la position du connecteur en haut ou bas

#if defined(CONNECTEUR_BAS)  // connecteur en bas
	//affectation des GPIO aux lignes L0, L1, L2, L3 du clavier 
	byte rowPins[4]{32, 33, 25, 26};
	//affectation des GPIO aux colonnes C0, C1, C2 du clavier 
	byte colPins[3]{4, 5, 15};

#else   // connecteur en haut

	byte rowPins[4]{26, 25, 33, 32};
	byte colPins[3]{15, 5, 4};

#endif

// Déclaration des caractères sur les touches
char keys[4][3]  {
{'1', '2', '3'},
{'4', '5', '6'},
{'7', '8', '9'},
{'*', '0', '#'}
};

Keypad clavier = Keypad((char *) keys, rowPins, colPins, 4, 3);

``` 
 
### Les méthodes

```char getKey() ``` 
Renvoie le code de la  touche enfoncée, si aucune touche n'est enfoncée renvoie NO_KEY. Cette fonction est non bloquante.

```char waitForKey() ```
Cette méthode attendra indéfiniment jusqu'à ce que quelqu'un appuie sur une touche. Attention la méthode bloque tous le code de la tâche en cours d’exécution jusqu'à ce qu'une touche soit enfoncée.

