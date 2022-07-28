#  C++ moderne avec ESP32

## Introduction

Comme nous le savons, C++ possède des fonctionnalités riches par rapport à C, mais combien de fonctionnalités C++ pouvons-nous utiliser dans la programmation du microcontrôleur ESP32 ?
Pour répondre à cette question, nous allons écrire des programmes tests. Sachez que la chaîne d'outils **Arduino 2.0.3 prend en charge C++17** !  Ainsi, vous pouvez commencer à utiliser le C++ moderne sans configuration supplémentaire. 

## Utilisation du type vector de la STL

Mon premier test porte sur le conteneur **vector** avec **algorithm** pour le tri et **iostream** pour les flux de sortie.
Le programme vector.cpp se compile et s'exécute sur la cible ESP32 sans problème.
voir ci joint ma fiche "fiche vector.pdf"

## Utilisation du type map de la STL

Une map est un conteneur associatif qui stocke des éléments formés par une combinaison d'une **clé** et d'une **valeur mappée** , suivant un ordre spécifique . Les clés sur une map doivent être uniques.
La première chose que nous devons faire pour utiliser le conteneur map est :
`#include <map>`
Nous devons spécifier le type des clés et le type des valeurs mappées.
```cpp
	std::map<String, int> m;
```

Un programme exemple  montrant comment insérer des éléments dans la map.
```cpp
 // Quelques  possibilités pour insérer des éléments dans la map
    m.insert({"abc", 1});
    m.insert(std::make_pair("bcd", 2));
    m.insert(std::pair<String, int>("cde", 3));
    m["def"] = 4;
```
Il est important de noter que la méthode **insert** vérifie si chaque élément inséré a une clé équivalente à celle d'un élément déjà présent dans le conteneur et, si elle est trouvée, l'élément n'est pas inséré.

Maintenant que nous avons notre map avec des éléments, nous allons tous les parcourir  et imprimer à la fois leurs clés et leurs valeurs. la fonction afficher fait le travail avec un itérateur. 
Pour démarrer l'itération, nous devons appeler la méthode **begin** sur la map, qui renverra un itérateur faisant référence au premier élément du conteneur.  De même, pour obtenir une condition d'arrêt, nous devons appeler la méthode **end**, qui renvoie un itérateur faisant référence à l' élément _après la fin dans le conteneur_ .
Pour faire passer un itérateur à l'élément suivant du conteneur, nous devons utiliser l'opérateur ++. Si nous combinons le tout dans une boucle for, nous pouvons facilement parcourir tous les éléments de la map.
Étant donné que les éléments de la map sont exposés par paires, l'itérateur pointera vers une **paire** . Ainsi, nous pouvons accéder à la clé et à la valeur en utilisant respectivement les **it->first** et **it->second** variables membres.

# Changelog

**27/07/2021 : ** Creation du README.md 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


