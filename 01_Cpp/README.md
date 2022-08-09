# C++ moderne avec ESP32

## Introduction

Comme nous le savons, C++ possède des fonctionnalités riches par rapport à C, mais combien de fonctionnalités C++ pouvons-nous utiliser dans la programmation du microcontrôleur ESP32 ? Pour répondre à cette question, nous allons écrire des programmes tests. Sachez que la chaîne d'outils  **Arduino 2.0.3 prend en charge C++17**  ! Ainsi, vous pouvez commencer à utiliser le C++ moderne sans configuration supplémentaire. Le code proposé a été testé en utilisant l'IDE netbeans et [Platformio] . Dans tous les cas, la version du noyau Arduino utilisée était  **2.0.3**  . (Juillet 2022)
Toutefois vous devez, Pour utiliser la syntaxe C++17,  ajouter les ligne suivantes dans le fichier platformio.ini  pour désactiver C++11 et activer l'option C++17.

```
	build_unflags = -std=gnu++11
	build_flags = -std=gnu++17
```
Pour vérifier la prise en compte de C++17 je propose un programme test qui utilise les `std::string_view`
 
## Initialisation uniforme


La manière moderne d'initialiser des objets en C++ consiste à utiliser une forme d'initialisation qui utilise des accolades : l' initialisation d'accolades est également appelée **initialisation uniforme**.
C'est sans doute l'une des fonctionnalités les plus importantes de C++11 que vous devez comprendre et utiliser.

Voici des exemples d'initialisation uniforme :
```cpp
	// Types intégrés 
	int width { 5 }; 
	// Tableaux 
	int arr1[3] { 1, 2, 3 };
	// Tableaux alloués dynamiquement :
	int* arr2 = new int[3]{ 1, 2, 3 };
    //  Conteneurs standards :
	std::vector<int> v { 1, 2, 3 }; 
	std::map<int, std::string> m { {1, "one"}, { 2, "two" }};
    // Chaîne de caratères
	char text[]{ "hello" };
    std::string_view sv{ "balloon" };
	
```
L'initialisation des accolades  interdit les "conversions restrictives". Cela signifie que si vous essayez d'initialiser une variable entre accolades en utilisant une valeur que la variable ne peut pas contenir en toute sécurité, le compilateur produira une erreur.
```cpp
	int i{ 1.2 }; // error
	int i{ static_cast<int>(1.2) }; //OK
	float f2{ 47/13 }; // OK
```
## String_view

C++17 introduit une autre façon d'utiliser les chaînes,  `std::string_view`
Contrairement à `std::string`, qui conserve sa propre copie de la chaîne,  `std::string_view` fournit une _vue_ d'une chaîne qui est définie ailleurs.
Contrairement aux chaînes de style C et `std::string`, `std::string_view`n'utilise pas de terminateurs nuls pour marquer la fin de la chaîne. Au contraire, il sait où se termine la chaîne car il garde une trace de sa longueur.
Dans une fonction, je vous conseille de passer des chaînes en utilisant `std::string_view`(par valeur) au lieu de `const std::string&`, sauf si votre fonction appelle d'autres fonctions qui nécessitent des chaînes de style C ou des paramètres std::string.

[Un cours sur les string_view](https://www.learncpp.com/cpp-tutorial/stdstring_view-part-2/) 

# Changelog

**08/08/2022 : ** Creation du README.md 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


