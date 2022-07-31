# Le conteneur std::map

## Utilisation du conteneur map de la STL

Le test porte sur le conteneur **map**  avec les exceptions.
Le programme map.cpp se compile et s’exécute sur la cible ESP32 sans problème.

Une map est un conteneur associatif qui stocke des éléments formés par une combinaison d'une **clé** et d'une **valeur mappée** , suivant un ordre spécifique . Les clés sur une map doivent être uniques.
La première chose que nous devons faire pour utiliser le conteneur map est :
```cpp
	#include <map>
```
Nous devons déclarer une map en spécifiant le type des clés et le type des valeurs mappées.
ici nous utilisons le type **String** du framwork Arduino. (avec un S majuscule).  On aurait pu aussi utilisé le type string de la stl (stl::string)  avec un s minuscule.
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
Il est important de noter que la méthode **insert** vérifie si chaque élément inséré n'a pas une clé équivalente à celle d'un élément déjà présent dans le conteneur et, si elle est trouvée, l'élément n'est pas inséré.

Maintenant que nous avons notre map avec des éléments, nous allons tous les parcourir  et imprimer à la fois leurs clés et leurs valeurs. la fonction **afficher** fait le travail avec un itérateur. 
```cpp
/**
 * @brief fonction pour afficher m 
 *        Utilise un itérateur  
 * @param _m une référence vers une map
 */
	void afficher(std::map<String, int> &x) {

	    std::map<String, int>::iterator it;

	    for (it = x.begin(); it != x.end(); it++) {
	        Serial.print(it->first);
	        Serial.print(" : ");
	        Serial.print(it->second);
	        Serial.println();
	    }
	}
```
Pour démarrer l'itération, nous devons appeler la méthode **begin()** sur la map, qui renverra un itérateur faisant référence au premier élément du conteneur.  De même, pour obtenir une condition d'arrêt, nous devons appeler la méthode **end()**, qui renvoie un itérateur faisant référence à l' élément _après la fin dans le conteneur_ .
Pour faire passer un itérateur à l'élément suivant du conteneur, nous devons utiliser l'**opérateur ++**. Si nous combinons le tout dans une boucle for, nous pouvons facilement parcourir tous les éléments de la map.
Étant donné que les éléments de la map sont exposés par paires, l'itérateur pointera vers une **paire** . Ainsi, nous pouvons accéder à la clé et à la valeur en utilisant respectivement les **it->first** et **it->second** variables membres.

### Obtenir une valeur à partir de la clé

Pour obtenir la valeur d'une clé donnée, utiliser la méthode **at** , en passant en entrée la **clé** pour laquelle on veut obtenir la valeur mappée. Cette méthode renvoie une référence à la valeur mappée de l'élément . Cependant, dans ce cas, si la clé n'est pas trouvé, une exception **out_of_range** est levée.
```cpp
// obtenir une valeur avec la méthode at
    try{
        int value = m.at("bcd");
        Serial.println(value);       
    }
    catch( std::exception e)
    {
        Serial.println(e.what());
        Serial.println("Clé pas trouvée !");
    }
```
### Obtenir une valeur avec l'opérateur []
 L'opérateur `[]` . En entrée, nous devons également passer la clé pour laquelle nous voulons obtenir la valeur mappée. 
```cpp
	int value = m["xyz"];
```
Cependant, le comportement lorsque l'élément n'est pas trouvé peut être un peu inattendu. Si la clé fournie ne correspond à aucune clé d' élément du conteneur, la méthode insère un nouvel élément avec cette clé et renvoie une référence à sa valeur mappée. Cela augmente toujours la taille du conteneur de un, même si aucune valeur mappée n'est affectée à l'élément (l'élément est construit en utilisant son constructeur par défaut).

### Rechercher un élément

Nous allons maintenant utiliser la méthode find  pour rechercher dans le conteneur un élément avec la clé fournie. Cette méthode renvoie un **itérateur** à l'élément, s'il est trouvé, ou un itérateur à **map::end** s'il n'est pas trouvé.
```cpp
// rechercher un élément méthode find
    auto a = m.find("abc");
    if (a != m.end()) {

        Serial.println("Element avec la clé 'abc' trouvé :");
        Serial.print(a->first.c_str());
        Serial.print(" : ");
        Serial.println(a->second);
        
    } else {
        Serial.println("Pas d'élement avec la clé 'abc'.");
    }
```
Notez que nous utiliserons le mot-clé auto pour définir la variable qui contiendra le résultat, de sorte que c'est le compilateur qui déduira son type.




# Changelog

**31/07/2022 : ** Creation du README.md 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#

 

