# std::any


## Introduction
`std::any` est « la forme moderne de `void*`» car il fait bien plus qu'un pointeur générique `void*`.
Un `void*`perd  l'informations sur le type de l'objet vers lequel il pointe :
```cpp
	int i = 42;
	void* pvi = &i;
	double d = *static_cast<double*>(pvi);
```
La conception est incorrecte, mais la compilation est possible et l'exécution continue comme si de rien n'était !!!

`std::any` Se souvient en quelque sorte des informations sur le type :
```cpp
try {     
      std::any ai = i;
      double d2 = std::any_cast<double&>(ai);   
} catch (std::bad_any_cast &e) {
     std::cout << "Exception caught: " << e.what() << std::endl;
}
```
Il ne donne pas accès au type statique de l'objet qui lui a été donné, mais il est toujours capable de reconnaître quand nous essayons de le caster dans le mauvais type. 
Noté que le programme "reboot"  si l'exception n'est pas attrapée.

## Syntaxe

On peut utiliser la méthode `has_value()` pour déterminer s'il y a une valeur. 

```cpp
    std::any a{1};
    std::cout << "a -> " << std::any_cast<int>(a) << '\n';

    a = 3.1415f;
    std::cout << "a -> " << std::any_cast<float>(a) << '\n';

    a = std::string("Hello world!");
    std::cout << "a -> " << std::any_cast<std::string>(a) << '\n';

    a = {}; // On peut utiliser la méthode has_value() pour déterminer s'il y a une valeur.
    if (!a.has_value()) {
        std::cout << "a -> " << "n'a pas de valeur\n";
    }
```
Vous pouvez réinitialiser un objet `std::any`  via `.reset()`.
```cpp
	a.reset();
    if (!a.has_value()) {
        std::cout << "a -> " << "n'a pas de valeur\n";
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


