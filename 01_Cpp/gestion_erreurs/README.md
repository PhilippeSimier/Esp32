# La gestion des erreurs

L'identification et la gestion des erreurs d'exécution sont importantes pour le développement d'applications robustes. Il peut y avoir plusieurs types d'erreurs d'exécution :
-   Erreurs récupérables :
    
    -   Erreurs indiquées par les fonctions via des valeurs de retour (codes d'erreur)
        
    -   Exceptions C++, levées à l'aide du mot-clé `throw`
        
-   Erreurs irrécupérables (fatales) :
    
    -   Assertions ayant échoué (en utilisant `assert`)
## Assertions

Le but d'une assertion est de détecter les erreurs de programmation en documentant quelque chose qui ne devrait jamais arriver. Si cela se produit, alors le programmeur a fait une erreur quelque part, et cette erreur peut être identifiée et doit être corrigée.

L'utilisation d'une instruction conditionnelle pour détecter un paramètre non valide (ou pour valider un autre type d'hypothèse), ainsi que l'affichage d'un message d'erreur et la fin du programme, est une réponse si courante aux problèmes que C++ fournit une méthode de raccourci pour le faire.

Une assertion est une condition pour continuer l'exécution du programme. Si l'expression est évaluée à `true`, l'instruction d'assertion ne fait rien. 
Si l'expression conditionnelle prend la valeur `false`, un message d'erreur s'affiche et le programme se termine (via `std::abort`). 
Ce message d'erreur contient  l'expression qui a échoué sous forme de texte, ainsi que le nom du fichier de code et le numéro de ligne de l'assertion. Cela permet de dire très facilement non seulement quel était le problème, mais où dans le code le problème s'est produit. 

En C++, les assertions d'exécution sont implémentées via la macro de préprocesseur assert , qui réside dans l'en-tête  `#include  <assert.h>`
```cpp
	#include  <assert.h>
	
	float calculateTime(float height, float gravity) {
		assert(gravity > 0.0); // gravity doit être supérieure à 0.0
	float res{ 0.0};
	if (height <= 0.0) {
		res = 0.0;
	} else {
		res = std::sqrt((2.0 * height) / gravity);
	}
	return res;
	}
```

## Exceptions

L'un des moyens les plus courants de gérer les erreurs potentielles dans une fonction consiste à utiliser des codes de retour.
Toutefois les codes de retour ne se mélangent pas très bien avec les constructeurs. Que se passe-t-il si vous créez un objet et que quelque chose à l'intérieur du constructeur tourne mal ? Les constructeurs n'ont pas de type de retour pour renvoyer un indicateur d'état !!!

La gestion des exceptions fournit un mécanisme permettant de dissocier la gestion des erreurs ou d'autres circonstances exceptionnelles du flux de contrôle typique de votre code. Cela donne plus de liberté pour gérer les erreurs.

**Lancer une exception**
En C++, une instruction **throw** est utilisée pour signaler un cas d'exception ou d'erreur.
```cpp
	throw std::runtime_error("Exception in constructor");
```
le code lance une exception du type `std::runtime_error`
**À la recherche d'exceptions**
La levée d'exceptions n'est qu'une partie du processus de gestion des exceptions. En C++,  le mot clé **try** est utilisé pour définir un bloc d'instructions qui doit être surveillé afin d'attraper toutes les exceptions lancées.
Le mot-clé **catch** est utilisé pour définir un bloc de code (appelé **bloc catch** ) qui gère les exceptions pour un seul type de données ici `std::runtime_error`
```cpp
    try { 
     
    // bloc de code à surveiller 
         
    } 
    catch (const std::runtime_error &e) {
        std::cout << "Exception caught: " << e.what() << std::endl;     
    }
```

# Changelog

**08/08/2022 : ** Creation du README.md 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


