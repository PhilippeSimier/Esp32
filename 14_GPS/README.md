# Capteur Byonics GPS5 HA


Le récepteur Byonics GPS5 HA est une version pour le ballon Haute Altitude (altitudes jusqu'à 84 Km) . C'est un GPS qui envoie des phrases standard NMEA-0183 une fois par seconde sur une liaison série RS-232 en 5 volts à la vitesse de 4800 bauds 
Une LED bleue, qui se trouve à l'intérieur du boîtier, reste allumée lors de la recherche des satellites puis clignote lorsque le capteur est synchronisé avec les satellites. 

Le brochage du connecteur DB-9 est 

 - 2 : sortie de données GPS (RS-232)
 - 4 : entrée d'alimentation +5 V
 - 5 : masse
 
 - [ ] La consommation de courant est d'environ 32 mA.
 - [ ] Phrases NMEA envoyées chaque seconde : $GPGSA, $GPRMC, $GPGGA,
       $GPGSV.
 - [ ] La précision est d'environ. 2,5 mètres.
 
 ### Schéma de raccordement ESP32
 - le niveau 1 (-5V) est transformé en +3.3V
 - le niveau 0 (+5V) est transformé en +0V

![schéma de raccordement](/14_GPS/Schema_GPS.png)

# Décodage des phrases NMEA

La bibliothèque Bibliothèque TinyGPS est utilisé.
Elle est installée en utilisant la commande suivante :

    pio lib -g install 416
Le programme exemple  montre comment extraire les informations de latitude, de longitude et d'altitude. D'autres informations comme la date et l'heure peuvent aussi être obtenues.
