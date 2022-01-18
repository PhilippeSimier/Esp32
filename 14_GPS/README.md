# Capteur GPS


Le récepteur Byonics GPS5 HA (Version Ballon Haute Altitude pour des altitudes jusqu'à 84Km) est un GPS série RS-232 5 volts, 4800 bauds qui envoie des phrases standard NMEA-0183 une fois par seconde.
Une LED bleue, qui se trouve à l'intérieur du boîtier, reste allumée lors de la recherche des satellites et clignote lorsque le capteur est synchronisé avec les satellites. 

Le brochage du DB-9 est 

 - 2 : sortie de données GPS (RS-232)
 - 4 : entrée d'alimentation +5 V
 - 5 : masse
 
 La consommation de courant est d'environ 32 mA.
 Phrases NMEA envoyées chaque seconde : $GPGSA, $GPRMC, $GPGGA, $GPGSV. 
 La précision est d'environ. 2,5 mètres.

![schéma de raccordement](/14_GPS/Schema_GPS.png)

