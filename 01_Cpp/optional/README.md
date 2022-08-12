# std::optional


## Introduction
Comment écrivez-vous une fonction qui accepte ou renvoie éventuellement un objet ? Une solution classique consiste à choisir l'une des valeurs potentielles comme sentinelle pour signaler l' _absence_ de valeur. Cela fonctionne raisonnablement bien lorsque l'une des valeurs représentables du type ne se produit jamais dans la pratique. C'est moins bien quand il n'y a pas de choix évident de sentinelle et qu'on veut pouvoir passer toutes les valeurs représentables. Si tel est le cas, l'approche typique consiste à utiliser un booléen séparé pour indiquer si le paramètre facultatif contient une valeur valide.

Comment écrivez-vous une classe avec un objet membre dont l'initialisation est retardée, c'est-à-dire qui contient éventuellement un objet ? Pour une raison quelconque, vous ne souhaitez pas initialiser ce membre dans le constructeur. L'initialisation peut se produire lors d'un appel  ultérieur ou uniquement sur demande. 

La solution de C++17 aux problèmes ci-dessus est  `std::optional<T>`
qui résout directement les problèmes qui surviennent lors du passage ou du stockage de ce qui peut ou non être actuellement un objet.

## Syntaxe

Vous pouvez demander explicitement si une instance de `std::optional<T>` contient une valeur en utilisant la méthode `has_value` ou par conversion contextuelle en `bool`:

Une fois que vous savez que `std::optional<T>` contient une valeur, vous pouvez l'extraire avec la méthode value() ou l'opérateur `*`  :

Par exemple si l'objet prix est un `std::optional<float>`

**Première version** 
```cpp
	auto prix = article.getPrix();
    if (prix.has_value()) {
        cout << "  prix : " << prix.value() << " euros" << endl;
    } else {
        cout << "  pas de prix" << endl;
    }
```
**Deuxième version**

```cpp
    auto prix = article.getPrix();
    if (prix) {
        std::cout << "  Prix : " << *prix << " €" << std::endl;
    } else {
        std::cout << "  Pas de prix " << std::endl;
    }
```
## Configuration platformio.ini 
```
[env:lolin32]
platform = espressif32
board = lolin32
framework = arduino
build_unflags = -std=gnu++11
build_flags   = -std=gnu++17
```


# Changelog

**12/08/2022 : ** Creation du README.md 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


