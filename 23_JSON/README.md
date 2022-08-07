# Json 


## Introduction

JSON est principalement utilisé pour sérialiser et transmettre des données structurées via une connexion réseau - transmettre des données entre un serveur et un client. Il est souvent utilisé dans des services tels que les API (Application Programming Interfaces) et les services Web qui fournissent des données publiques.

## Principe

Pour représenter des données en JSON, les paires clé/valeur se présentent comme suit :
Dans un exemple concret, vous souhaiterez peut-être structurer des données sur un utilisateur :
```js
{
    "nom":"SIMIER",
    "prenom":"Philippe",
    "web":"philippes.ddns.net",
    "age":60
}
```

##  La bibliothèque JSON
Bien qu'il existe une bibliothèque dite officiel nommée **Arduino_JSON**,
la bibliothèque **ArduinoJson**   de Benoît Blanchon sera préférée pour ses performances et sa documentation.
Pour l'installer  utiliser la commande suivante :
```bash
pio pkg install --library "bblanchon/ArduinoJson@^6.19.4"
```

## Analyser une chaîne JSON

ArduinoJSON utilise un espace de mémoire préalloué pour stocker l'arborescence d'un JsonObject, ceci est fait par la fonction template `StaticJsonDocument<N>` qui alloue de la mémoire sur la pile, elle peut être remplacé par `DynamicJsonDocument` qui alloue sur le tas.


Utilisez la fonction **deserializeJson** pour décoder/analyser la chaîne JSON en un JsonObject appelé **doc** . 
l'entrée peut provenir d'un `Stream` ou d'une chaîne de caractères `char[]`.
```cpp

char json[] =
      "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";

StaticJsonDocument<512> doc;
DeserializationError error = deserializeJson(doc, json);
    if (error){
        Serial.println(F("Failed to read file, using default configuration"));
        Serial.println(error.f_str());
    }
```
Le résultat peut être faux pour différentes raisons :

-   la chaîne JSON a une syntaxe non valide ;
-   la chaîne JSON ne représente pas un objet ;
-   le Buffer est trop petit - utilisez [l'assistant ArduinoJson](https://arduinojson.org/v6/assistant/) pour calculer la taille du tampon.

Maintenant que l'objet  est en mémoire, vous pouvez facilement extraire ses données. 
```cpp

	const char* sensor = doc["sensor"];
	long time = doc["time"];
    double latitude = doc["data"][0];
    double longitude = doc["data"][1];
```



# Changelog

**02/08/2022 : ** Creation du README.md 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


