# Les fonctions lambdas


## Introduction
Une lambda est une fonction,  **potentiellement anonyme**, destinée à être utilisée pour des  **opérations locales**. Détaillons ces différentes caractéristiques.

-   Une lambda est  **une fonction**, c’est-à-dire un regroupement de plusieurs instructions. Rien de bien nouveau.
-   Une lambda peut être  **anonyme**. Contrairement aux fonctions classiques qui portent obligatoirement un nom, un identificateur, une lambda peut être utilisé  **sans qu’on lui donne de nom**.
-   Une lambda s’utilise pour des  **opérations locales**. Cela signifie qu’une lambda peut être directement écrite dans une fonction ou un algorithme, au plus près de l’endroit où elle est utilisée, au contraire d’une fonction qui est à un endroit bien défini, à part.

## Syntaxe

La syntaxe pour déclarer une lambda a des points communs avec celles des fonctions classiques, mais aussi quelques différences. 

```c++
[zone de capture](paramètres de la lambda) -> type de retour { instructions }

```

-   La  **zone de capture** : par défaut, une lambda est en totale isolation et ne peut manipuler aucune variable de l’extérieur. Grace à cette zone, la lambda va pouvoir modifier des variables extérieures.
-   Les  **paramètres de la lambda** : exactement comme pour les fonctions, les paramètres de la lambda peuvent être présents ou non, avec utilisation de références et/ou  `const`  possible.
-   Le  **type de retour** : encore un élément qui nous est familier. Il est écrit après la flèche  `->`. Il peut être omis dans quelques cas, mais nous allons l’écrire à chaque fois dans une volonté d’écrire un code clair et explicite.
-   Les  **instructions** : 

## Quelques exemples simples

#### Déclaration d'une lambda
On peut,  utiliser la syntaxe de C++ moderne, à base d’accolades `{}`, 
```cpp
auto lambda { [](std::string const & message) -> void { std::cout << "Message reçu : " << message << std::endl; }};
```
ou bien utiliser l’initialisation héritée du C à base de égal `=`. Tout est une question de goût.
```cpp
auto lambda = [](std::string const & message) -> void { std::cout << "Message reçu : " << message << std::endl; };
```
#### Utilisation
```cpp
// S'utilise comme une fonction classique, de façon totalement transparente.
lambda("Hello !");
lambda("Philippe");
std::vector<std::string> const chaines { "Un mot", "Autre chose", "Du blabla", "Du texe", "Des lettres" };
    
std::for_each( std::begin(chaines), std::end(chaines), lambda );
```
##  Paramètres génériques (C++14)

A partir de C++14, tout comme il est possible de laisser le compilateur deviner le type de retour, on peut lui laisser le soin de **déduire les paramètres de la lambda**, en utilisant `auto` à la place du type explicite des paramètres.
```cpp
auto lambda { [](auto const & parametre) -> void { std::cout << "Paramètre reçu : " << parametre << std::endl; }};

std::vector<std::string> const chaines { "Un mot", "Autre chose", "Du blabla", "Du texe", "Des lettres" };
std::for_each( std::begin(chaines), std::end(chaines), lambda );
    
std::vector<int> const nombres { 3, 1, 25, 7, 51 };
std::for_each( std::begin(nombres), std::end(nombres), lambda );
```
Une même lambda peut afficher deux collections de types différents.
# Changelog

**15/08/2022 : ** Creation du README.md 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


