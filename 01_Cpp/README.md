# Les chaînes de caractères 


## Introduction

Il y a différentes façons de définir une chaîne de caractères dans un programme pour ESP32.

 - avec un tableau (ou array) de caractères de type char
 ```cpp 
	 const char *a1 = "hello";
	 const char b1[] = "hello";
 ```
Bien que les deux écritures semble équivalentes, il y a une différence, 
Pour la première écriture a1 est un pointeur sur la chaîne littérale "hello", 
dans la seconde écriture `b1[]`la chaîne littérale "hello" est recopiée, cette ligne occupe donc deux fois plus de place de mémoire RAM que la première.

 - type **String** (avec un S majuscule) défini dans le noyau d’Arduino
```cpp
	const String d1 = "hello"; 
```
- type string (avec un s minuscule) défini par la STL
```cpp
	const std::string e1 = "hello";
```
## Le mot clé   **`const`**

Le mot clé   **`const`**  spécifie que la  valeur d’une variable est constante et indique au compilateur d’empêcher le programmeur de  modifier sa valeur. Le compilateur garantit que l’objet constant n’est jamais modifié.

En C++, vous pouvez spécifier la taille d’un tableau de char avec une variable **`const`**  comme suit :
```cpp
	const  int maxarray = 255; 
	char store_char[maxarray]; // allowed in C++; not allowed in C
```


## Quelques fonctions à utiliser

les fonctions à utiliser pour une chaîne de style C terminée par un caractère nul sont :
-   `sizeof(b1)` pour connaitre la taille du tableau b1 
-   `strlen(b1)` pour connaitre la longueur de la chaîne dans le tableau b1 
-   `strcat(b1, str1)` ajoute str1 à la fin de la chaîne dans le tableau b1 
-   `strcopy(b1, str)` copie str dans le tableau b1
-   `strcmp(b1,str1)` pour comparer deux tableaux de caractères

les méthode et opérateurs qui peuvent être utiliser pour les **String** ou **std::string** sont nombreuses: citons par exemple

 - `d1.length()` pour connaitre la longueur du String d1
 - `sizeof(d1)` donne la taille de la variable d1
 - l'opérateur `+` permet la concaténation de deux objets string
 - les opérateurs usuels `=` et `==`  pour l'affectation et la comparaison.
 - `d1.c_str()` pour convertir le contenu d'une variable de type String en une chaîne de style C terminée par un caractère nul. Notez que cela donne un accès direct au tampon String interne et doit être utilisé avec précaution.

## L'optimisation « string interning » 


 ```cpp
	 char b1[] = "hello";
	 if ( !strcmp(b1, "hello")){
			 //....
	 }

 ```
 Comme vous pouvez le voir, il y a dans le programme source deux fois la chaîne littérale `"hello"`, cela signifie-t-il que l' exécutable contient deux copies de "hello" ? Plus important encore, cela signifie-t-il que l'exécutable charge deux copies dans la RAM ?

Heureusement, la réponse est non aux deux questions. Grâce à l'optimisation réalisée par le compilateur sur  l'internement des chaînes , **une seule copie de chaque littéral ** est stockée dans le programme (c'est-à-dire dans la mémoire Flash), et donc une seule est chargée dans la RAM. Le « string interning »  est une optimisation qui consiste à ne stocker qu'une seule copie d'un littéral, quel que soit le nombre de fois où le programme y fait référence.
Pour démontrer que l'internalisation de chaîne ne stocke qu'une seule copie de deux littéraux de chaîne identiques est simple : nous avons juste besoin de comparer les pointeurs. Si les pointeurs se réfèrent à la même adresse, cela signifie qu'il n'y a qu'une seule copie dans la RAM.  Le programme de démonstration **string_interning** montre les cas ou cela fonctionne. 
```cpp
const char *a1 = "hello";
const char *a2 = "hello";
```
a1 et a2 pointe sur la même adresse donc ça marche bien avec `const char*`, 
Si à la place, nous changeons le type en `char[]`, le programme fait une copie du littéral lorsqu'il crée les variables b1 et b2 : et donc b1 et b2 pointe sur des adresses différentes.
```cpp
const char b1[] = "hello";
const char b2[] = "hello";
```
De même, si nous changeons le type en `String`, le constructeur fait une copie du littéral 
```cpp
const String d1 = "hello";
const String d2 = "hello";
```
d1 et d2 occupe deux emplacements différents en mémoire.

## PROGMEM & F()

PROGMEM est une fonctionnalité Arduino AVR qui a été portée sur ESP32 pour assurer la compatibilité avec les bibliothèques Arduino existantes. 
la macro PROGMEM fait partie de la bibliothèque `pgmspace.h`

 - pour Arduino AVR la macro est défini de la façon suivante

```cpp
	#define 	PROGMEM   __ATTR_PROGMEM__
```
pour Arduino ESP32 la macro est vide (ligne 22 du fichier pgmspace.h)
```cpp 
	#define PROGMEM
```
PROGMEM sur un ESP32 n'est en fait qu'une macro qui ne fait rien, elle est conservé pour la compatibilité du code. 
Dans vos programme, il n'est pas nécessaire d'ajouter PROGMEM, car toutes les variables  déclarées `const` sont de toute façon conservées dans la mémoire Flash. 
Notez que les tableaux const sont stockés dans la mémoire du programme  puis mappés directement de la mémoire flash dans la mémoire selon les besoins. Ainsi, aucun __FlashStringHelper n'est nécessaire. Vous pouvez oublier F().

# Changelog

**08/08/2022 : ** Creation du README.md 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


