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
A partir d'un client il est possible de d'effectuer ping vers le point d'accès.

# Obtenir la liste des stations connectés
Nous allons afficher les adresses IP de toutes les stations connectées au réseau.
il est nécessaire d'inclure **esp_wifi.h** qui expose les fonctions de niveau inférieur et les structures de données pour obtenir les adresses IP de toutes les stations connectées à l'ESP32.
La structure de type ***wifi_sta_list_t*** contient la liste des stations associées au softAP ESP32. L'appel à la fonction ***esp_wifi_ap_get_sta_list()*** permet d'obtenir la liste des adresses MAC des stations.
La structure ***tcpip_adapter_sta_list_t*** contient  les adresses IP des stations connectées au réseau.   L'appel à la fonction ***tcpip_adapter_get_sta_list*** permet d'obtenir la liste des adresses IP .
La structure ***tcpip_adapter_sta_list_t*** contient un membre appelé **num** qui correspond au nombre de stations actuellement connectées au réseau ESP32.
nous pouvons faire une boucle for pour parcourir le tableau de sta et imprimer les informations sur chaque station.
### le code complet de la fonction:
```c
void afficherListeClients(){

  wifi_sta_list_t wifi_sta_list;
  tcpip_adapter_sta_list_t adapter_sta_list;

  memset(&wifi_sta_list, 0, sizeof(wifi_sta_list));
  memset(&adapter_sta_list, 0, sizeof(adapter_sta_list));

  esp_wifi_ap_get_sta_list(&wifi_sta_list);
  tcpip_adapter_get_sta_list(&wifi_sta_list, &adapter_sta_list);

  for (int i = 0; i < adapter_sta_list.num; i++) {

    tcpip_adapter_sta_info_t station = adapter_sta_list.sta[i];

    Serial.print("station nr ");
    Serial.println(i);

    Serial.print("MAC: ");
    for (int i = 0; i < 6; i++) {
      Serial.printf("%02X", station.mac[i]);
      if (i < 5)Serial.print(":");
    }

    Serial.print("\nIP: ");
    Serial.println(ip4addr_ntoa(&(station.ip)));
    Serial.println("-----------");
  }
}

```
### l'affichage obtenu
![PA wifi](/WifiPA/capture0.JPG)

# Changelog

**23/12/2019 : ** Ajout du dossier wifiPA . 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


