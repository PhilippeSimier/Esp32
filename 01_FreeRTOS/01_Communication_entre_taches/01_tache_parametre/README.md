﻿# Communication entre deux tâches

## Variables globales comme arguments
Les fonctions associées aux tâches peuvent recevoir un paramètre, un pointeur générique `void *` 
Voici le code  de création de la tâche task1 où param est  une variable globale, est passée comme paramètre. Noté que c'est un pointeur sur la variable param1 caster en `void *` qui est passé.

```cpp
xTaskCreate(
    task1,                
    "tache_1",            
    10000,                
    static_cast<void *>(&param1),
    1,                    
    NULL);                
```

Dans le code de la fonction task1, nous allons interpréter le paramètre reçu comme un pointeur sur int, ce qui correspond à (int *).
Donc, la première chose à faire est un static_cast à (int *).

```cpp
    static_cast<int *>(parameter);
```

Maintenant, nous avons un pointeur sur la position de la mémoire d'un entier. Pour accéder au contenu actuel de la position de la mémoire. (la valeur de la position de la mémoire à laquelle pointe notre pointeur). il faut utiliser l'opérateur de déréférencement, qui est * , ce qui donne 

en lecture
```cpp
    int nb = *(static_cast<int *>(parameter));
```
ou en écriture :
```cpp
    *(static_cast<int *>(parameter)) = 10; 
```
# Changelog

**27/12/2019 : ** Ajout du README . 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


