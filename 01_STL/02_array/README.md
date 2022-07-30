# Le conteneur std::array

## std::array
`std::array<>`  encapsule l'ancien tableau de style C avec des avantages supplémentaires. C'est une sorte de conteneur séquentiel avec des éléments de taille constante.
### déclaration
```cpp
#include <array>

array <int,10> tableau1;
```
le premier paramètre est le type des éléments à stocker dans le `tableau1` et le deuxième paramètre est une constante représentant le nombre d’éléments du tableau.

### déclaration avec initialisation
```cpp
#include <array>

array <int,10> tableau1 = {15,8,25,2};
```
Si nous fournissons un nombre moins important d’éléments lors de l’initialisation, les éléments restants seront initialisés avec la valeur par défaut 0.

**std :: array** fournit également une fonction membre `fill()` pour définir la même valeur pour tous les éléments en une fois.

### accéder aux éléments de std::array
Accès à un élément dans std::array à l'aide de l'opérateur []
```cpp
int a = tableau1[3];
```
Accés à un élément dans std::array en utilisant la fonction membre at()
L'accès à n'importe quel élément hors limites à l'aide de la fonction at () déclenchera une exception out_of_range .
```cpp
int b = tableau1.at(4);
```

### Itérer sur un objet std::array <>
#### Itérer en utilisant la boucle for & operateur []
```cpp
for (int i = 0; i < tableau1.size(); i++)
	{
		std::cout << tableau1[i] << " , ";
	}
	std::cout << std::endl;
```
#### Itérer en utilisant un iterateur

```cpp
auto it = tableau1.begin();
    while(it != tableau1.end())
    {
        AfficherValeurs(*it);
        it++;
    }
    std::cout << std::endl;
```

> Remarque sur le mot-clé **auto**
>  Lors de l'initialisation d'une  variable, le mot-clé **auto** peut être utilisé à la place du type de  variable pour indiquer au compilateur de déduire le type de la  variable à partir du type de l'initialisateur.  C'est ce qu'on appelle  l' inférence de type (aussi parfois appelée déduction de type). 
> Notez  que cela ne fonctionne que lors de l'initialisation d'une variable  lors de sa création. Les variables créées sans valeur d'initialisation  ne peuvent pas utiliser cette fonctionnalité (car C ++ n'a pas de  contexte pour en déduire le type).

#### Itérer en utilisant for_each (STL algorithm)
```cpp
for_each (tableau1.begin(), tableau1.end(), AfficherValeurs);
    cout << endl;
```


### Changelog

 **29/10/2019 :** Version finale . 
 
 
> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER Lycée Touchard Le Mans**
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#
https://docplayer.fr/15188945-Le-traitement-d-images-avec-opencv.html

