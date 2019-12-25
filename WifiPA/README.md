# Point d'accès WIFI & Esp32 

# Description
Définir l'ESP32 comme AP (point d'accès), permet d'être connecté à l'ESP32 à l'aide de n'importe quel appareil doté de capacités Wi-Fi sans avoir à se connecter à un routeur.

En termes simples, lorsque l'ESP32 est défini comme point d'accès, il va créer un réseau Wi-Fi et les appareils Wi-Fi (stations) à proximité pourront s'y connecter (smartphone ou  ordinateur).
 
 ![PA wifi](/WifiPA/access-point.png)

# la méthode softAP
Vous devez définir un nom SSID et un mot de passe pour accéder à l'ESP32. Dans cet exemple, nous définissons le nom SSID  sur **ESP32AP** ,  Le mot de passe est **totototo** la  contrainte est qu'il doit avoir au minimum **8 caractères**.
```c
  #include "WiFi.h"
  
  const char *ssid = "ESP32AP";
  const char *password = "totototo";
  
  WiFi.softAP(ssid, password);
```
Il existe  d'autres paramètres facultatifs que vous pouvez transmettre à la méthode softAP () . Voici tous les paramètres :

 - **SSID** : 63 caractères maximum;
 - **mot de passe** : minimum de 8 caractères; mis à NULL si vous voulez que le point d'accès soit ouvert
 - **canal** : numéro de canal Wi-Fi (1-13)
 - **ssid_hidden** : (0 = diffusion SSID, 1 = masquage SSID)
 - **max_connection** : nombre maximal de clients connectés simultanément (1-4)

Nous pouvons obtenir l'IP du point d'accès en appelant la méthode softAPIP de l'objet WiFi .
```c
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
```
On obtient dans la console
```
IP address: 192.168.4.1
dhcps: send_offer>>udp_sendto result 0
requete GET /
requete GET /
```
Un serveur DHCP distribue les adresses IP aux clients qui se connectent. Le premier client obtient 192.168.4.2
A partir d'un client il est possible de pinger le point d'accès.


# Changelog

**23/12/2019 : ** Ajout du dossier wifiPA . 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


