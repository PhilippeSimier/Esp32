# La mémoire flash

## Introduction
Tout d'abord faisons un petit tour d'horizon des mémoires disponibles sur le micro-contrôleur Esp32.

L'Esp32 dispose  d'une mémoire de type  **RAM**. Cette mémoire est extrêmement rapide, mais aussi extrêmement volatile, c'est à dire que les données stockées dessus ont une durée de vie très courte. C'est ici que sont stockées les variables de notre programme. Il n'est pas possible de l'utiliser pour stocker sur une longue durée car elles sont effacées à chaque reboot, en cas de plantage, et même en cas de mise en veille (deepsleep) de la puce.

L'Esp32 dispose aussi d'une mémoire  **RAM type RTC**. C'est à dire un espace mémoire qui est persistant au reboot, mais qui sera toujours perdu en cas de coupure de courant. Habituellement cet espace de stockage sert a conserver l'horloge interne entre les deepsleep, mais sur ESP on peut y stocker des données librement pendant un court laps de temps (quelques minutes).  Attention, en cas de plantage et/ou de coupure totale, cette mémoire est perdue, de plus la librairie rtcfifo ajoute d'autres limitations.

Enfin, la puce dispose aussi d'un module mémoire  **flash**. Cet espace de stockage est persistant, même en cas de coupure de courant. C'est d'ailleurs ici que l'on charge le code du programme qui sera exécuté. En contrepartie, ce type de mémoire est très long à accéder à la fois en lecture et en écriture. Autre bémol important, cette mémoire  **s'use à l'écriture**  (100.000 cycles environ).

## A propos de EEPROM
Il n'y a pas à proprement parler  de mémoire EEPROM physique. La mémoire EEPROM est émulée pour **assurer une compatibilité descendante avec les applications Arduino existantes**
La classe **EEPROM est obsolète**. Pour les nouvelles applications sur ESP32, utilisez un système de fichiers. 
 L'EEPROM est implémentée à l'aide d'un seul blob dans la mémoire flash, il s'agit donc d'un conteneur dans un conteneur. En tant que tel, ce n'est pas une méthode de stockage haute performance. La mémoire EEPROM permet d’enregistrer uniquement 512 octets.

## Le système de fichier SPIFFS


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

### 3 formater le système de fichiers

Pour formater appeler la méthode format sur l' objet **SPIFFS** . Cette méthode ne prend aucun argument et renvoie en sortie une valeur booléenne indiquant si la procédure a réussi ( **true** ) ou échoué ( **false** ).
```cpp
	bool formatted = SPIFFS.format();

	if(formatted){
	    Serial.println("\n\nSuccess formatting");
	}else{
	    Serial.println("\n\nError formatting");
	}	
```
 ### 4 lister un répertoire
La fonction suivante permet de lister un répertoire
 ```cpp
		void listDir(char * dir){
 
		 File root = SPIFFS.open(dir);
		 File file = root.openNextFile();
 
		  while(file){
			 Serial.print("FILE: ");
		     Serial.println(file.name());
		     file = root.openNextFile();
		 }
	 }

 ```

