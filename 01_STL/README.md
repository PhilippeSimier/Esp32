#  C++ moderne avec ESP32

## Introduction

Comme nous le savons, C++ possède des fonctionnalités riches par rapport à C, mais combien de fonctionnalités C++ pouvons-nous utiliser dans la programmation du microcontrôleur ESP32 ?
Pour répondre à cette question, nous allons écrire des programmes tests. Sachez que la chaîne d'outils **Arduino 2.0.3 prend en charge C++17** !  Ainsi, vous pouvez commencer à utiliser le C++ moderne sans configuration supplémentaire. 
Le code a été testé en utilisant  l'IDE netbeans et [Platformio] . Dans tous les  cas, la version du noyau Arduino utilisée était **2.0.3** . (Juillet 2022)

## La librairie Template standard STL

La STL est une librairie qui est constituée principalement par des classes conteneurs (vecteurs, listes ...), ainsi que des fonctionnalités pour parcourir (iterateur) leur contenu et des algorithmes pour travailler sur leur contenu (parcourir, tri ...).
La STL définit les chaînes de caractères `stl::string` avec un **s** en lettre minuscule à ne pas confondre avec le type `String` du framework Arduino qui lui s'écrit avec une majuscule.

### Les conteneurs
Les conteneurs sont une abstraction de stockage. Il s'agit de structures permettant d'organiser un ensemble de données. Les classes de conteneurs définies par la STL admettent donc toutes un paramètre template, qui, lors de l'instanciation d'un conteneur, sert à indiquer le type des objets que contiendra cette instance de conteneur.
exemple :
```cpp
	list<int> liste; //une liste d'entiers
```

#### Conteneurs séquentiels


 | type          |  | détails |
 |---------------|--|---------|
 | **array**    | tableau statique contigu  | |
 | **vector**   | tableau dynamique contigu |accès direct aux éléments, ajout et suppression efficaces en fin, mais linéaire en temps ailleurs |
 | **deque**  | file d'attente à 2 bouts |accès direct, ajout et suppression efficace en début ou en fin, linéaire ailleurs |
 | **stack**| pile (LIFO) | |
 | **queue**| File d'attente (FIFO) | |
 | **priority_queue** | File d'attente avec priorité | |
 | **list** | liste (doublement) chaînée | accès séquentiel, ajout et suppression en temps constant n’importe où dans la liste |
 | **foward_list**| liste simplement chaînée | |

#### Conteneurs associatifs

| type          |  |détails |
|---------------|--|--------|
|**set**  | collection triée |éléments maintenus ordonnés : appartenance, insertion et suppressions efficaces|
|**multiset** | collection triée | avec possibilité de répétition |
|**map** | collection triée par une clé|accès aux valeurs via des clés ajout et suppressions efficaces |
|**multimap** | collection triée par une clé| autorisant des clés dupliquées |

#### Autres conteneurs

La paire d’éléments (pair)
Certains algorithmes de la STL (find par exemple) retournent des paires (position de l’élément trouvé et un booléen indiquant s’il a été trouvé).
```cpp
pair<char,int> c1 = make_pair(’B’, 2); // coordonnées type "bataille navale"
pair<char,int> c2 = make_pair(’J’, 1);
```



# Changelog

**27/07/2022 : ** Creation du README.md 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


