# La classe Led 

## Description

La classe Led  prend en charge l'envoi de données pour mettre à jour une série de LED
de couleur communément appelées NeoPixels.
Elle est une spécialisation de la classe `makuna/NeoPixelBus` , plus précisément de `NeoPixelBus<NeoRgbFeature, Neo800KbpsMethod> ` La classe utilise la vitesse de bus la plus courante de 800 Kbp/s et l'ordre de couleur  est rouge, vert  bleu.

Elle permet de contrôler les 4 leds RGB **WS2812** présente sur la carte SNIR.

## platformIO.ini

Le fichier platformIO.ini doit contenir la  dépendance **makuna/NeoPixelBus@^2.7.0**

```ini
[env:lolin32]
platform = espressif32
board = lolin32
framework = arduino
lib_deps =
	makuna/NeoPixelBus@^2.7.0
```
## Les Méthodes de la classe Led

### Le constructeur 
il possède un arguments qui définit le nombre de leds contrôlées.

Le constructeur appelle la méthode `Begin()` pour  initialiser le NeoPixelBus et le préparer à l'utilisation suivit de la méthode `Show()` pour envoyer les informations de pixel aux leds physiques.

```cpp
	led = new  Led(4); // quatre leds;
```

###  allumer

La méthode allumer permet de définir une couleur pour une led. Elle appelle la méthode `SetPixelColor(id, couleur)` pour définir la couleur  d'un pixel donné, suivi de la méthode `Show()` pour envoyer l'information aux leds physiques.
```cpp
	led->allumer(VERT, 0); // led 0 verte
```

### éteindre

La méthode éteindre permet de définir la couleur noir pour une led. Elle appelle la méthode `SetPixelColor(id, RgbColor(0,0,0))` pour définir la couleur noir  d'un pixel donné, suivi de la méthode `Show()` pour envoyer l'information aux leds physiques.
```cpp
	led->eteindre(0);
```


# Changelog

**04/09/2022 : ** Creation du README.md 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


