#  Dé-sérialisation

Cette  section explique tout ce qu'il y a à savoir sur la dé-sérialisation. La dé-sérialisation est le processus de conversion d'une séquence d'octets en une représentation mémoire. Dans notre cas, cela signifie convertir un document JSON en une hiérarchie de structures et de tableaux C++.

Nous utiliserons une réponse JSON de l'API  https://philippes.ddns.net/cgi-bin/bme280Json
comme exemple. 
```
{
	"OK" : true,
	"altitude":"62 m",
	"TemperatureC":"30.9 °C",
	"TemperatureF":"87.6 F",
	"Pression":"1014.8 hPa",
	"Humidite":"33.5 %",
	"PointRosee":"13.0 °C"
}
```
Comme vous le voyez, c'est un objet JSON qui contient 7 clés. Il comprend la valeur de la température en °C en °F, la pression, l'humidité et le point de rosée.

## Principe
L'une des caractéristiques  d'ArduinoJson est sa stratégie d'allocation de mémoire fixe.
Voici comment cela fonctionne :
1. Tout d'abord, vous créez un JsonDocument pour réserver une quantité de mémoire spécifiée.
2. Ensuite, vous désérialisez le document JSON.
3. Enfin, vous détruisez le JsonDocument, ce qui libère la mémoire réservée.

La mémoire du JsonDocument peut être soit dans la pile, soit dans le tas. L'emplacement dépend de la classe dérivée que vous choisissez. Si vous utilisez un `StaticJsonDocument`, la mémoire réservée sera dans la pile ; si vous utilisez un `DynamicJsonDocument`, la mémoire réservé  sera dans le tas.
Un `JsonDocument` est responsable de la réservation et de la libération de la mémoire utilisée par ArduinoJson. C'est une instance de l'idiome RAII. 

### Comment spécifié la taille de la mémoire réservée

Lorsque vous créez un JsonDocument, vous devez spécifier sa capacité en octets. Dans le cas de `DynamicJsonDocument`, vous définissez la capacité via un argument du constructeur.
```cpp
	const size_t capacity = 256;
    DynamicJsonDocument mesure(capacity);
```
Dans le cas d'un `StaticJsonDocument`, vous définissez la capacité via un paramètre de modèle
```cpp
	StaticJsonDocument<256> mesure;
```
Lorsque le JsonDocument est petit, nous pouvons le garder dans la pile. En utilisant la pile, nous réduisons la taille de l'exécutable et améliorons les performances car nous évitons le surcoût dû à la gestion du tas (heap).

### Désérialiser le document JSON
Maintenant que le JsonDocument est prêt, nous pouvons analyser l'entrée avec deserializeJson() 
```cpp
DeserializationError error = deserializeJson(mesure, mesureJson);
```
Sachez que, `DeserializationError` convertit implicitement en booléen, vous n'avez donc pas à écrire `if (err != DeserializationError::Ok);` vous pouvez simplement écrire `if (err)`.
Deuxièmement, `DeserializationError` a une fonction membre `c_str()` qui renvoie une représentation de l'erreur sous forme de chaîne de caractères.
```cpp
	if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.f_str());
    }
```
### Extraire des valeurs d'un objet JSON
Maintenant, que le JsonDocument contient une représentation en mémoire de l'entrée JSON. Nous pouvons en extraire les valeurs.
```cpp
	bool ok = mesure["OK"];
```
l'opérateur d'indice ([]) a été personnalisé pour imiter un objet JavaScript.
#### Explicit casts
ArduinoJson propose une syntaxe alternative avec une conversion de type explicite.
```cpp
auto temp  = mesure["TemperatureC"].as<const char*>();
```
# Changelog

**29/08/2022 : ** Creation du README.md 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


