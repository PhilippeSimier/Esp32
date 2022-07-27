#  C++ moderne avec ESP32

## Introduction

Comme nous le savons, C++ possède des fonctionnalités riches par rapport à C, mais combien de fonctionnalités C++ pouvons-nous utiliser dans la programmation du microcontrôleur ESP32 ?
Pour répondre à cette question, nous allons écrire des programmes tests. Sachez que la chaîne d'outils **Arduino 2.0.3 prend en charge C++17** !  Ainsi, vous pouvez commencer à utiliser le C++ moderne sans configuration supplémentaire. 

## Utilisation de la STL

Mon premier test porte sur le conteneur **vector** avec **algorithm** pour le tri et **iostream** pour les flux de sortie.
Le programme vector.cpp se compile et s'exécute sur la cible ESP32 sans problème.
voir ci joint ma fiche "fiche vector.pdf"

## Utilisation du type std::optional

Depuis C++ 17, un type `std::optional` est offert pour représenter le fait d'avoir **peut-être quelque chose**. Un optional<T> modélise donc un possible T. Par exemple :
```cpp
#include <optional>  
#include <iostream>  

using  namespace  std; 

optional<int> division_entiere(int num, int denom) { 
if (denom == 0) return {}; // optional vide  
return { num / denom }; // optional non vide 
} 

int main() { 
	if (int num, denom; cin >> num >> denom) 
	if (auto quotient = division_entiere(num, denom); quotient) // si on a un résultat...  
	cout << quotient.value() << endl; // ... alors on l'affiche 
}

```
# Changelog

**27/07/2021 : ** Creation du README.md 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


