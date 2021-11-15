# Fichiers SPIFFS

## Introduction
**Attention**, l’écriture de fichier dans la mémoire flash est limitée à 10000 cycles. Optimisez votre code pour réduire les opérations d’écritures afin de prolonger la durée de vie de vos projets.

SPIFFS (**S**erial **P**eripheral **I**nterface **F**lash **F**ile System) est un système de fichier spécialement conçu pour les micro-contrôleurs.

SPIFFS prend en charge les **noms de fichiers jusqu’à 31 caractères utiles** se terminant par `\0` (c’est-à-dire char filename [32]) avec autant de sous-répertoires que l’espace le permet.
Le nombre de caractères correspond au chemin complet incluant le nom du fichier et son extension.
Il ne faut pas utiliser d’espace(s) ou de caractère(s) accentué(s) dans le nom de fichier.

    /dossier/ssdossier/fichier1.text  
    |———————— 31 caractères ———————|

Le chemin de fichier doit toujours commencer par le caractère “/”, par exemple `/fichier.txt`
### 1 Monter le système de fichiers
    SPIFFS.begin()

Cette méthode monte le système de fichiers SPIFFS et doit être appelée avant que n’importe quelle autre méthode  ne soit utilisée. Renvoie true si le système de fichiers a été monté avec succès.

### 2 Ouvrir un fichier
    File file = SPIFFS.open(path, option);


**path** doit être un chemin absolu commençant par une barre oblique (par exemple /dir/nom_fichier.txt).

**option** est une chaîne spécifiant le mode d’accès. Il peut s’agir de

-   **“r”** read, lecture seule
-   **“r+”** lecture et écriture. Le pointeur est positionné au début du fichier
-   **“w”** write, écriture. Le contenu existant est supprimé. Le fichier est créé s’il n’existe pas
-   **“w+”** ouvre le fichier en lecture et à l’écriture. Le fichier est créé s’il n’existe pas, sinon il est tronqué. Le pointeur est positionné au début du fichier
-   **“a”** append, ouvre un fichier en ajout des données. Le fichier est créé s’il n’existe pas. Le pointeur est positionné à la fin du fichier s’il existe déjà
-   **“a+”** append, ouvre un fichier en ajout de données. Le fichier est créé s’il n’existe pas. La pointeur est positionné au début du fichier en lecture et à la fin du fichier pour l’écriture (ajout).

Renvoie l’objet File. Pour vérifier si le fichier a été ouvert avec succès, utilisez l’opérateur booléen.    

# Enregistrer des données

**Effortless-SPIFFS** - C'est une classe utile pour faciliter la lecture et le stockage des données dans les fichiers.
Cette classe vise à rendre l'accès à SPIFFS beaucoup plus facile pour permettre aux utilisateurs de continuer à écrire les choses importantes plutôt que de déboguer pourquoi le stockage ne fonctionne pas.
 
Exemple de code
```cpp
#include <Effortless_SPIFFS.h>

eSPIFFS fileSystem;
float myVariable;

void setup(){
    Serial.begin(115200);
    Serial.println();
}

void loop() {
    // Open the storage file and save data to myVariable
    if (fileSystem.openFromFile("/Float.txt", myVariable)) {
        Serial.print("Successfully read file and parsed data: ");
        Serial.println(myVariable, 6);
    }

    // Set myVariable to a random value
    myVariable = (float)random(1, 1000) / (float)random(1000, 65563);
    Serial.print("myVariable is now: ");
    Serial.println(myVariable, 6);

    // Write the data back to the SPIFFS
    if (fileSystem.saveToFile("/Float.txt", myVariable)) {
        Serial.println("Successfully wrote data to file");
    }

    // Delay between loops
    delay(10000);
}
```
#### Enregistrement des données dans un fichier à partir d'une variable
La méthode  `saveToFile` est utilisée pour enregistrer le contenu d'une variable dans un fichier. les différents prototypes de la méthode **saveToFile** sont
```cpp
// Definition
bool saveToFile(const char*, &bool);
bool saveToFile(const char*, &float);
bool saveToFile(const char*, &double);
bool saveToFile(const char*, &signed char);
bool saveToFile(const char*, &unsigned char);
bool saveToFile(const char*, &signed int);
bool saveToFile(const char*, &unsigned int);
bool saveToFile(const char*, &signed short);
bool saveToFile(const char*, &unsigned short);
bool saveToFile(const char*, &signed long);
bool saveToFile(const char*, &unsigned long);
bool saveToFile(const char*, &char*);
bool saveToFile(const char*, &const char*);
bool saveToFile(const char*, &String);
bool saveToFile(const char*, &std::string);
bool saveToFile(const char*, &ArduinoJson::DynamicJsonDocument);
```
#### Affectation d'une variable à partir d'un fichier
La méthode  `openToFile` est utilisée pour affecter le contenu d'une variable à partir d'un fichier. Les différents prototypes de la méthode **openToFile** sont :
```cpp
bool openFromFile(const char*, &bool);
bool openFromFile(const char*, &float);
bool openFromFile(const char*, &double);
bool openFromFile(const char*, &signed char);
bool openFromFile(const char*, &unsigned char);
bool openFromFile(const char*, &signed int);
bool openFromFile(const char*, &unsigned int);
bool openFromFile(const char*, &signed short);
bool openFromFile(const char*, &unsigned short);
bool openFromFile(const char*, &signed long);
bool openFromFile(const char*, &unsigned long);
bool openFromFile(const char*, &char*);
bool openFromFile(const char*, &const char*);
bool openFromFile(const char*, &String);
bool openFromFile(const char*, &std::string);
bool openFromFile(const char*, &ArduinoJson::DynamicJsonDocument);
```

#### Installer la bibliothèque Effortless-SPIFFS avec pio
Recherche de la bibliothèque

    pio lib search "header:Effortless_SPIFFS.h"

Installation de la bibliothèque
```bash
philippe@b107PSR:~$ pio lib -g install 6954
Library Storage: /home/philippe/.platformio/lib
Library Manager: Installing id:6954
Downloading  [####################################]  100%
Unpacking  [####################################]  100%
Library Manager: Effortless-SPIFFS @ 2.3.0 has been installed!

```
