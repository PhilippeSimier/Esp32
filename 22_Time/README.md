# ESP32 rtc 

## Description

Le circuit Real Time Clock (RTC) est un composant essentiel dans les applications qui dépendent de la gestion précise du temps. Il permet de synchroniser des événements, de marquer des horodatages et de maintenir une référence temporelle cohérente.
L'une des principales fonctions d'un RTC est de fournir une horloge en temps réel précise. Il maintient une trace du temps, sous la forme de temps epoch (valeur de secondes écoulées depuis le depuis le 1er janvier 1970 à 00h00 UTC.
La puce ESP32 contient en interne une minuterie matérielle pour maintenir l'heure du système, permettant  la conservation de l'heure dans divers modes de veille. 
Cependant, le  RTC intégré à l'ESP32 ne conserve pas ses données en cas de coupure d'alimentation. Il est donc essentiel de synchroniser ce RTC interne 

 - soit avec un serveur NTP à travers le réseau internet,
 - soit avec un RTC périphérique sur le bus I2C doté d'une alimentation sauvegardée par   une batterie.

## Obtenir l'heure calendaire actuelle

Si vous avez besoin d'obtenir l'heure et la date avec une résolution d'une seconde, utilisez l'extrait de code suivant : L'heure est affiché en français et en heure locale.

```cpp
const char * months[] = {
    "Janv.", "Févr.", "Mars", "Avr.", "Mai", "Juin", "Juil.",
    "Août", "Sept.", "Oct.", "Nov.", "Déc."
};

const char * days[] = {
    "Dim.", "Lun.", "Mar.", "Mer.", "Jeu.", "Ven.", "Sam."
};

struct tm timeInfo;
time_t now;    // time_t Type arithmétique le nombre de secondes depuis 00h00, le 1er janvier 1970 UTC
time(&now);   // renvoie l'heure actuelle du système sous forme de temps Epoch
localtime_r(&now, &timeInfo);  // convertit le temps Epoch en temps calendaire exprimée en heure locale
    
    Serial.printf("%s %d %s %d ",
            days[timeInfo.tm_wday],
            timeInfo.tm_mday,
            months[timeInfo.tm_mon],
            timeInfo.tm_year + 1900);

    Serial.println(&timeInfo, "%H:%M:%S");
```
## Mettre à jour la date et  l'heure

Pour mettre à jour la date et l'heure à partir du temps Epoch (temps Unix, mesuré en secondes depuis le 1er janvier 1970), il suffit d'utiliser la fonction `settimeofday`
```cpp
struct timeval new_time;
new_time.tv_sec = 1704981007; // 11th January 2024 13:50:07
new_time.tv_usec = 0;

if (settimeofday(&new_time, NULL) == 0) {
   Serial.printf("La mise à jour de la date et de l'heure a réussi.\r\n");
    } 

```
Pour convertir l'heure calendaire stockée dans une variable de type `struct tm` en temps Epoch (temps Unix, mesuré en secondes depuis le 1er janvier 1970), vous pouvez utiliser la fonction `mktime` de la bibliothèque.

```cpp
	struct tm calenderTime; 
	calenderTime.tm_year = 2024 - 1900; // année - 1900 
	calenderTime.tm_mon = 0; // mois (0-11) 
	calenderTime.tm_mday = 17; // jour du mois 
	calenderTime.tm_hour = 12; // heure 
	calenderTime.tm_min = 0; // minute 
	calenderTime.tm_sec = 0; // seconde  
	// Conversion de la structure tm en temps Epoch  
	time_t epochTime = mktime(&calenderTime);
```

## Définir la time zone pour obtenir le temps local

La détermination de la zone horaire permet de convertir l'heure universelle coordonnée (UTC) en heure locale. Différentes régions du monde ont des décalages horaires différents par rapport à l'UTC en raison de la rotation de la Terre. Ainsi, définir la zone horaire permet de représenter correctement l'heure locale à un endroit spécifique.
De plus certaines régions observent l'heure d'été, au cours de laquelle les horloges sont réglées d'une heure en avant par rapport à l'heure normale. La définition de la zone horaire tient compte de ces ajustements automatiques pour garantir que l'heure est correctement gérée, qu'il s'agisse de l'heure d'été ou de l'heure normale.

Les fuseaux horaires sont généralement définis en utilisant des noms de région (comme "Europe/Paris") ou des abréviations standard (comme "CET" pour Central European Time sans tenir compte de l'heure d'été). 

Pour utiliser une abréviation qui prend en compte l'heure d'été utiliser "CEST" (Central European Summer Time).

Voici un exemple :
```cpp
// Définir la timezone sur Paris (Central European Time)
if (setenv("TZ", "CET-1CEST,M3.5.0,M10.5.0/3", 1) != 0) {
   Serial.printf("Erreur lors de la définition de la timezone");    
}

// Mettre à jour la variable d'environnement TZ
tzset();
```
La chaîne "CET-1CEST,M3.5.0,M10.5.0/3" est une valeur typique pour la variable d'environnement TZ (TimeZone). Cette chaîne représente le fuseau horaire de l'Europe centrale (Central European Time, CET) avec l'ajustement pour l'heure d'été (Central European Summer Time, CEST).

La partie "CET-1" indique que le fuseau horaire standard est CET (UTC+1), ce qui signifie que le temps local est en avance d'une heure par rapport au temps universel coordonné (UTC).

La partie "CEST,M3.5.0,M10.5.0/3" spécifie les règles de changement d'heure d'été. Cela indique que le passage à l'heure d'été (CEST) se produit le dernier dimanche de mars à 2h00, avec "M3.5.0", et le passage à l'heure standard (CET) se produit le dernier dimanche d'octobre à 3h00, avec "M10.5.0/3".

En résumé, cette valeur de la variable TZ indique que le système est configuré pour le fuseau horaire de l'Europe centrale, avec un ajustement automatique pour l'heure d'été. Cela signifie que le système prend en compte les changements d'heure d'été et d'heure standard conformément aux règles spécifiées.

## Synchroniser avec un serveur NTP

Le NTP (Network Time Protocol) est un protocole Internet qui permet de synchroniser l' horloge, à travers le réseau internet.
Sur un esp32 aucune librairie additionnelle n’est requise, tout est intégré de base dans `time.h` 

la fonction `configTime` est utilisée pour configurer le RTC interne à l' ESP32 afin de synchroniser l'heure à partir d'un serveur NTP (Network Time Protocol).


Voici un exemple de code
```cpp
	String ntpServerName[3]; 
	ntpServerName[0] = "ntp-p1.obspm.fr";
	ntpServerName[1] = "pool.ntp.org";
    // connexion aux serveurs NTP, avec un offset nul. Temps UTC   
    configTime(0, 0, 
			    ntpServerName[0].c_str(),
			    ntpServerName[1].c_str()
			    );      
    // Attente de la synchronisation
    struct tm timeinfo;
    while (!getLocalTime(&timeinfo)) {
        Serial.print("!");
    }
```
Vous pouvez définir jusqu'à 3 serveurs NTP différents.
# Changelog

 **04/09/2022 :**  Creation du README.md 

**18/01/2024 :**  Actualisation de la présentation

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)

<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


