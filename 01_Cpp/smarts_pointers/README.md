#  Les smarts pointers

**Remarque** : les smarts pointers proviennent du projet [Boost](https://www.boost.org/doc/libs/1_80_0/libs/smart_ptr/doc/html/smart_ptr.html#scoped_ptr).
Une des principales problématiques quand on code en C++ réside dans la libération de la mémoire (et plus généralement des ressources). Le constat est sans appel : les développeurs passent beaucoup trop de temps à chasser les fuites mémoires. Il serait préférable d'utiliser ce temps pour plutôt travailler l'aspect fonctionnel des applications. Pour ce faire, il faudrait automatiser la libération des ressources.

**RAII (Resource Acquisition Is Initialization)** est une technique utilisée en C++ pour relâcher automatiquement les ressources devenues inutilisées. Cette technique a été introduite par Bjarne Stroustrup (le père de C++).

## Introduction
En **C++ moderne**, la bibliothèque standard comprend des _smarts pointers_.  Les pointeurs bruts sont utilisés uniquement dans les petits blocs de code à portée limitée.
Un smart pointer est un objet de classe template que vous déclarez **dans la pile** et que vous initialisez en utilisant un pointeur brut qui pointe vers un objet alloué dans le tas (heap). Une fois le smart pointer créé, celui ci possède le pointeur brut. Cela signifie que **le smart pointer est chargé de supprimer la mémoire que le pointeur brut spécifie**. Le destructeur du smart pointer contient l'appel à supprimer, et comme le pointeur intelligent est déclaré sur la pile, son destructeur est appelé lorsque le pointeur intelligent sort de son étendue, **même si une exception est levée à un emplacement situé plus haut dans la pile**.

Vous accédez au pointeur encapsulé en utilisant les opérateurs de pointeur familiers, `->` et `*`, que la classe de pointeur intelligent surcharge pour retourner un pointeur brut encapsulé.

## Un exemple avec unique_ptr

les pointeurs `unique_ptr` sont accessible via l'entête `<memory>`
ils garantissent que la durée de vie de votre pointeur et de la zone de mémoire associée sont liés à la durée de vie de l'instance de pointeur intelligent.

**unique_ptr**  est destiné à des cycles de vie court. Il est le seul à pointer l’objet. Son cycle de vie est généralement dans un scope de code.

L'exemple illustre les étapes essentielles suivantes pour utiliser un pointeur intelligent.

 - Déclarez le pointeur intelligent comme variable automatique (locale).
 - Dans le paramètre de type, spécifiez le type pointé du pointeur encapsulé.
 - Passer un pointeur brut obtenu avec **`new`** dans le constructeur du pointeur intelligent.
```cpp
  #include <memory>
  typedef std::unique_ptr< Ressource > RessourcePtr;
  
  RessourcePtr r1( new Ressource("Demo") );
```
 - Utilisez les opérateurs  `->`  et  `*`  surchargés pour accéder à
   l'objet.     
```cpp
	r1->doSomething();
```
 - Laissez le pointeur intelligent supprimer l'objet. (pas de delete)

Les pointeurs intelligents sont conçus pour être aussi efficaces que possible, aussi bien en termes de mémoire que de performances. Par exemple, la seule donnée membre dans `unique_ptr` est le pointeur encapsulé.
Les pointeurs intelligents ont leurs propres fonctions membres, accessibles à l’aide de la notation « point ». Par exemple, certains pointeurs intelligents de bibliothèque standard C++ ont une fonction membre de réinitialisation qui libère la propriété du pointeur. C'est utile lorsque vous souhaitez libérer la mémoire possédée par le pointeur intelligent avant que celui-ci ne passe hors de portée.
```cpp
	r1.reset();
```

## shared_ptr 

Le **shared_ptr**  est destiné au cas suivant : un objet alloué sur le tas serait pointé par plusieurs smarts pointers. Plus ambitieux que l’`unique_ptr` il possède un compteur référence et implémente le constructeur par copie et l’opérateur d'affectation `=`.
Le pointeur brut n'est pas supprimé tant que tous les propriétaires de`shared_ptr` ne sont pas hors de portée ou n'ont pas abandonné l'objet pointé.
L’opérateur **!** (not) retourne la validité ou pas du shared_ptr.

# Changelog

**15/08/2022 : ** Creation du README.md 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


