# assert & static_assert

## Entête à inclure
```cpp
#include <cassert> // en C++
```
## Introduction
Une assertion est utilisée pour tester l'état d'une variable: si la valeur qui y est stockée est incohérente par rapport à ce que vous attendez, votre programme sera alors interrompu et un message d'erreur sera alors affiché sur la console. On peut penser que ce mécanisme est proche d'une levée d'exception. Ce n'est pas complètement faux, mais il faut noter deux différences : vous ne pouvez pas intercepter une assertion et le mécanisme d'assertion peut globalement être court-circuité pour votre programme exécutable  (par exemple, vous pouvez activer les assertions en mode debug et les couper en mode release).

Pour utiliser une assertion, invoquer la macro  `assert`  en lui passant en paramètre une expression (par exemple, une comparaison de pointeur avec  `nullptr`). Si le résultat de l'expression est vrai, le programme se poursuit. Si, au contraire l'expression est fausse l'assertion est levée et votre programme interrompu.

Pour désactiver le mécanisme d'assertions, sans commenter les appels à assert (bien entendu), il vous suffit de définir la macro  **`NDEBUG`**  avant la ligne  `#include <cassert>`. Une nouvelle compilation de l'intégralité du programme sera nécessaire. Si vous placez la définition de la macro à la suite de l'inclusion du module d'assertions, cela n'aura aucun effet.

Vous pouvez aussi définir cette macro  `NDEBUG`  directement lors du lancement de votre compilateur.  Ainsi aucune modification du code source ne sera nécessaire. Voici un petit exemple de contenu du fichier **platformio.ini** pour  compiler   avec la définition de la macro  `NDEUBG`  (l'option  `-D`  permettant cette définition).
```
[env:lolin32]
platform = espressif32
board = lolin32
framework = arduino
build_flags   = -DNDEBUG=1
```

##  _static_assert_
`static_assert` n'est pas une macro : c'est un mot clé réservé du langage C.
Une assertion statique est évaluée non pas durant exécution (comme pour la macro `assert`, mais **à la compilation**. Cela permet de vérifier que certains prérequis sont bien présents afin de poursuivre la compilation.

Exemple :
```cpp
static_assert( sizeof(int) == 2, "16 bits platform required" );
```
Voici ce que produira la tentative de compilation si vous êtes  sur une plate-forme esp32 
les entiers ne sont pas sur 16 bits.
```
Compiling .pio/build/lolin32/src/assert.cpp.o
src/assert.cpp: In function 'void setup()':
src/assert.cpp:29:32: error: static assertion failed: 16 bits platform required
     static_assert( sizeof(int) == 2, "16 bits platform required" );
                    ~~~~~~~~~~~~^~~~
*** [.pio/build/lolin32/src/assert.cpp.o] Error 1
========================== [FAILED] Took 5.77 seconds ==========================

BUILD FAILED (exit value 1, total time: 7s)
```

# Changelog

**08/08/2022 : ** Creation du README.md 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


