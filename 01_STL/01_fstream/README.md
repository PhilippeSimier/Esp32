## Utilisation des flux sur fichiers

Nous allons tester l'utilisation des classes C++ **ifstream** et **ofstream** pour écrire et lire des fichiers dans la partition SPIFF.
Notez que le noyau Arduino propose aussi des API pour travailler avec des fichiers, qui sont suffisamment flexibles pour la plupart des opérations de base.
La première chose que nous devons faire pour utiliser les flux est d'inclure:
```cpp
	#include` `<SPIFFS.h>
    #include` `<fstream>
```
2 puis monter le système de fichiers SPIFFS
```cpp
	if (!SPIFFS.begin(true)) {
	  Serial.println("An Error has occurred while mounting SPIFFS");
	  return;
	}
```
3 créer un objet de la classe **ofstream** pour l'écriture 
```cpp
	std::ofstream fichier;
```
4 Ouvrir le fichier
```cpp
 fichier.open("/spiffs/test.txt");
```
Notez que le nom du fichier doit inclure le chemin complet qui, dans notre cas, doit commencer par « **/spiffs** », qui est le chemin racine par défaut lorsque nous montons le système de fichiers sans passer de paramètres supplémentaires (vous pouvez le vérifier [ici](https://github.com/espressif/arduino-esp32/blob/46d5afb17fb91965632dc5fef237117e1fe947fc/libraries/SPIFFS/src/SPIFFS.h#L27)).
Dans un scénario d'application réel, **vous devez effectuer des validations d'erreur.**
```cpp
	 if (fichier.is_open()){
	 // 
	 }
```

5 Ecrire une chaîne avec l'opérateur   <<
```cpp
	fichier << "Une première ligne de texte\n";
```
6 Fermer le fichier
```cpp
	fichier.close();
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


