# ESP32 rtc 

## Description

L'ESP32 emploie une minuterie matérielle pour maintenir l'heure du système, permettant ainsi la conservation de l'heure dans divers modes de veille tant que l'ESP32 demeure alimenté.

## Obtenir l'heure actuelle

Si vous avez besoin d'obtenir l'heure avec une résolution d'une seconde, utilisez l'extrait de code suivant : L'heure est affiché en français et en heure locale.

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
time(&now);   // renvoie l'heure actuelle du système sous forme de temps depuis l'époque
localtime_r(&now, &timeInfo);  // convertit l'heure depuis l'époque en heure calendaire exprimée en heure locale
    
    Serial.printf("%s %d %s %d ",
            days[timeInfo.tm_wday],
            timeInfo.tm_mday,
            months[timeInfo.tm_mon],
            timeInfo.tm_year + 1900);

    Serial.println(&timeInfo, "%H:%M:%S");
```
## Mise à jour de la date et de l'heure

Pour mettre à jour la date et l'heure il suffit d'utiliser la fonction `settimeofday`
```cpp
struct timeval new_time;
new_time.tv_sec = 1704981007; // 11th January 2024 13:50:07
if (settimeofday(&new_time, NULL) == 0) {
   Serial.printf("La mise à jour de la date et de l'heure a réussi.\r\n");
    } 

```
## Définir la time zone

définir la timezone sur **Paris** en utilisant la fonction `setenv`.

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

## Synchroniser avec NTP

Le NTP (Network Time Protocol) est un protocole Internet qui permet de synchroniser l' horloge, à travers le réseau internet.
Aucune librairie additionnelle n’est requise, tout est intégré de base dans `time.h` 

la fonction `configTime` est utilisée pour configurer le module ESP32 afin de synchroniser l'heure à partir d'un serveur NTP (Network Time Protocol).

[configTime](https://github.com/espressif/arduino-esp32/blob/master/cores/esp32/esp32-hal-time.c#L48)


# Changelog

**04/09/2022 : ** Creation du README.md 

**08/01/2023 : ** Actualisation de la présentation

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)

<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


