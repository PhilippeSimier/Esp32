#  shared_ptr

Le type `shared_ptr` est un pointeur intelligent de la bibliothèque standard C++ conçu pour des scénarios dans lesquels plusieurs propriétaires peuvent devoir gérer la durée de vie de l'objet en mémoire. Après avoir initialisé `shared_ptr`, vous pouvez le copier, le passer par valeur dans des arguments de fonction et l'assigner à d'autres instances `shared_ptr`. Toutes les instances pointent vers le même objet. 
    
##  Exemple d'utilisation de la classe

Histoire de tester sérieusement le concept, nous allons l'utiliser au travers d'une « mini implémentation » d'arbre binaire. Un arbre binaire est une structure de données récursive qui permet d'organiser les valeurs sous forme d'une arborescence de nœuds en mémoire. 
Les **arbres binaires**  sont des cas particuliers d’arbres où chaque _nœud_ possède au maximum  **deux  _fils_**.
le principe est très simple. Chaque nœud de notre arbre contient une valeur. L'arbre sera trié si on respecte la règle suivante pour chaque nœud parent : le fils de gauche doit contenir une valeur inférieure au parent, et le fils de droite doit contenir une valeur supérieure au parent. Voici un exemple d'arbre trié de cette façon :

Il est  aisé de définir un **arbre binaire** en définissant les classes Arbre et Nœud :
 Voici un exemple d'implémentation.
### Classe Arbre
```cpp
#include <iostream>
#include <memory>
#include <Noeud.h>

template <typename ELEMENT>
class Arbre {
    typedef std::shared_ptr<Noeud<ELEMENT>> NoeudPtr;

public:
    Arbre();
    virtual ~Arbre();

    void push(const ELEMENT & value);

private:
    NoeudPtr root;
};

// Implementations

template <typename ELEMENT>
Arbre<ELEMENT>::Arbre() :
root() {}

template <typename ELEMENT>
Arbre<ELEMENT>::~Arbre() {
    std::cout << "Tree released" << std::endl;
}

/**
 * Insert un élément dans l'arbre
 * @param value
 */
template <typename ELEMENT>
void Arbre<ELEMENT>::push(const ELEMENT & value) {

    NoeudPtr node(new Noeud<ELEMENT>(value));
    if (root.get() == nullptr) {
        root = node;
        std::cout << "First insertion of " << value << std::endl;
    } else {
        root->push(node);
    }
}
```
### Classe Nœud
```cpp
#include <iostream>
#include <memory>

template <typename ELEMENT>
class Noeud {
    typedef std::shared_ptr<Noeud<ELEMENT>> NoeudPtr;

public:

    Noeud(const ELEMENT & value);
    virtual ~Noeud();

    void push(NoeudPtr node);
    int hauteur();
    int taille();

private:
    NoeudPtr leftNode;
    ELEMENT value;
    NoeudPtr rightNode;

};

// Implementation de la classe Noeud

template <typename ELEMENT>
Noeud<ELEMENT>::Noeud(const ELEMENT & value) :
leftNode(),
value(value),
rightNode() {
    std::cout << "Node " << value << " created" << std::endl;
}

template <typename ELEMENT>
Noeud<ELEMENT>::~Noeud() {
    std::cout << "Node " << value << " released" << std::endl;
}

template <typename ELEMENT>
void Noeud<ELEMENT>::push(NoeudPtr node) {
    if (node->value < value) {
        if (leftNode.get() == nullptr) {
            leftNode = node;
            std::cout << "Insert on left of " << value << std::endl;
        } else {
            leftNode->push(node);
        }
    } else {
        if (rightNode.get() == nullptr) {
            rightNode = node;
            std::cout << "Insert on right of " << value << std::endl;
        } else {
            rightNode->push(node);
        }
    }
}
```

Et voici maintenant un exemple d'utilisation où plusieurs instances de ressources sont stockées dans un arbre binaire. L'arbre est lui-même est instancié en dynamique, mais aussi les instances de nœuds et les ressources. Tous est maintenu par des `std::shared_ptr`.

```cpp
void setup() {

    Serial.begin(115200);
    while (!Serial)
        continue;

    RessourcePtr first( new Ressource("First value"));
    RessourcePtr second(new Ressource("Second value"));
    RessourcePtr third( new Ressource("Third value"));
    RessourcePtr fourth(new Ressource("Fourth value"));
    
    typedef std::shared_ptr< Arbre<RessourcePtr> >   ArbrePtr;
    
    ArbrePtr unArbre( new Arbre<RessourcePtr>() );
    unArbre->push(third);
    unArbre->push(fourth);
    unArbre->push(second);
    unArbre->push(first);
    unArbre->push(first);
}
```
A la fin de la fonction setup l'ensemble des ressources allouées en dynamique sont automatiquement relâchées.


# Changelog

**08/08/2022 : ** Creation du README.md 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


