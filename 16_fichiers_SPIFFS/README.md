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

