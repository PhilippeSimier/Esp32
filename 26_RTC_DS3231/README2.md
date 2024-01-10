# ESP32 rtc 

## Description


## RTClib
```cpp
struct tm timeinfo; 

timeinfo.tm_year = gps.date.year() - 1900; 
timeinfo.tm_mon = gps.date.month() - 1; 
timeinfo.tm_mday = gps.date.day(); 
timeinfo.tm_hour = gps.time.hour(); 
timeinfo.tm_min = gps.time.minute(); 
timeinfo.tm_sec = gps.time.second(); 

unsigned  long  int unixtime = mktime(&timeinfo); 
Serial.println(""); 
printf("unixtime = %u\n", unixtime); 

rtc.adjust(DateTime(unixtime)); // à tester


```


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


