# Le littéral nullptr

Les pointeurs sont des objets qui contiennent l'adresse d'un autre objet. Cette adresse peut être déréférencée à l'aide de l'opérateur de déréférencement (*) pour obtenir la valeur à cette adresse.
il existe une valeur supplémentaire qu'un pointeur peut contenir : une valeur nulle. Une valeur nulle  est une valeur spéciale qui signifie que quelque chose n'a **aucune valeur**. Lorsqu'un pointeur contient une valeur nulle, cela signifie que le pointeur ne **pointe sur rien.** Un tel pointeur est appelé un pointeur nul .

## Problème avec le littéral NULL

les programmeurs C insistent sur l'utilisation du littéral `NULL`  qui est défini comme un pointeur générique (void *) qui à pour valeur 0 pour identifier clairement un pointeur vide. Donc, pour suivre les meilleures pratiques, nous  écrivons :

```
const char* color = NULL;
```
Tant que nous restons dans le domaine du langage C, tout va bien.
 Toutefois `NULL`en C++ ne peut pas avoir la même  définition qu'en C car le compilateur C++ ne fait pas de conversion de type implicite. 
Le programme test  démontre que NULL est défini de la manière suivante:
```
#define NULL 0
```
En C++ `NULL` n'est pas un littéral de type `void*`mais un littéral de type `int` qui à la valeur 0.

Soit le programme suivant
```cpp
  const char *color { NULL };
  String colorStr1 { color };
  String colorStr2 { NULL };
```
Pour l'objet **colorStr1**, le compilateur va choisir le constructeur de String à partir d'un char * qui est indéfini. La classe String a prévu ce cas de figure et  construit une chaîne vide.
Pour l'objet  **colorStr2** le compilateur va choisir la surcharge du constructeur  String qui accepte un entier.   La chaîne construite est une chaîne qui contient le caractère `0`  En passant `NULL`au constructeur, on a juste appelé la mauvaise surcharge, celle qui prend un entier et le convertit en chaîne. Conclusion les deux chaînes sont différentes.
Notez que vous pouvez construire directement une chaîne vide  en utilisant la syntaxe suivante :
```cpp
	String colorStr3 {};
```
En conclusion le littéral  **NULL** perturbe la surcharge des fonctions.
Il perturbe aussi la déduction du type de modèle pour les fonctions template.

## Solution

Au lieu de `NULL`, il faut utiliser `nullptr`, un nouveau mot-clé introduit en C++11.
`nullptr`est convertit implicitement en `T*`pour n'importe quel type `T`.
`nullptr`n'est pas un entier et le compilateur ne peut donc pas appeler la mauvaise surcharge.
Le littéral`nullptr`a son propre type, `nullptr_t`, donc le compilateur fait des déductions de type correctes.


## Avertissement
Le déréférencement d'un pointeur nul entraîne un comportement indéfini.
Chaque fois que vous utilisez des pointeurs, vous devez faire très attention à ce que votre code ne déréférence pas les pointeurs nuls ou pendants, car cela entraînera un comportement indéfini (probablement un plantage de l'application). 
tout comme nous pouvons utiliser une condition pour tester les valeurs booléennes pour `true`ou `false`, nous pouvons utiliser une condition pour tester si un pointeur a une valeur `nullptr`ou non :
```cpp

void print( int* ptr ){
	if ( ptr ){
		std::cout << *ptr; // déréférencement possible
	} else {
	    // Erreur 
	}
}
```

## Conclusion

Utiliser `nullptr`lorsque vous avez besoin d'un littéral de pointeur nul pour l'initialisation, l'affectation ou la transmission d'un pointeur nul à une fonction.

Privilégier les références aux pointeurs dans la mesure du possible. Les pointeurs et les références  donnent tous deux la possibilité d'accéder indirectement à un autre objet.

# Changelog

**08/08/2022 : ** Creation du README.md 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


