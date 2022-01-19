# Les cartes de développement ESP32

Il existe plusieurs formats de carte.

### Carte de développement 30 broches

![DEV KIT V1 30 pins](/00_hardware/esp32_30pins.png)

### Carte de développement 38 broches

![DEV KIT V1 38 pins](/00_hardware/esp32_38pins.png)

### Carte de développement 36 broches

![DEV KIT V1 36 pins](/00_hardware/esp32_36pins.png)

### Carte TTGO T1

![DEV KIT TTGO T1](/00_hardware/ttgo-t1.jpg)

# Alimenter une carte ESP32
La plage de tension de fonctionnement de l'ESP32 est de **3,0** à **3,6** V. En fonctionnement normal, la carte alimentera la puce à **3,3** V via un régulateur intégré. 

Les broches d'E/S ne sont **pas tolérantes au 5V** ! Si vous interfacez la carte avec des composants 5V (ou plus), vous devrez effectuer un décalage de niveau logique. 

Pour alimenter la carte ESP32, vous avez trois options:

 1. Via le port USB.

    
2.  -Utilisation d'une tension non régulée entre 5V et 12V, connectée aux broches 5V et GND. Cette tension est régulée sur la carte.
    
3.  -Utilisation d'une tension régulée de 3,3 V, connectée aux broches 3,3 V et GND. Soyez très prudent avec cela: ne dépassez pas la limite de 3,3V, ou votre module ESP32 sera endommagé.
    

Attention : soyez très, très prudent de n'utiliser qu'une seule de ces options à la fois. Par exemple, n'alimentez pas votre carte ESP32 via la broche 5V en utilisant une entrée 10V alors qu'en même temps vous avez le module connecté à votre ordinateur via USB. Cela endommagera sûrement votre module, et peut-être même votre ordinateur. 

Nous devons comprendre qu'il existe différents niveaux de tension sur la carte ESP32 NodeMCU. L'image suivante montre un schéma simplifié des niveaux de tension et des composants importants.

![Schéma simplifié](/00_hardware/alimentation_carte_esp32.jpg)

Sur le schéma, vous voyez que la broche USB 5V et la broche VIN sont connectées ensemble à l'entrée d'un régulateur de tension, qui transforme la tension d'entrée entre 5V et 12V en une tension de sortie de 3,3V.

#### Mode alimentation via le port USB

La première possibilité et aussi la plus simple pour une alimentation électrique est le câble USB 5V. Comme l'ESP32 fonctionne à 3,3 V, le régulateur de tension intégré transforme le 5 V de la connexion USB en 3,3 V souhaitée. 
Le **régulateur 3,3** V de la carte ESP32 peut **fournir de manière fiable jusqu'à 600 mA** , ce qui devrait être plus que suffisant pour la plupart des projets. L'ESP32 peut consommer jusqu'à 250 mA **pendant les transmissions RF**. Même en transmettant activement via WiFi, la sortie du régulateur peut également  alimenter  via la broche étiquetée  **3V3** des composants externes.

#### Mode alimentation externe VIN

La deuxième possibilité consiste à utiliser la broche **VIN** du NodeMCU comme entrée pour l'alimentation. Le régulateur de tension AMS1117 a une tension d'entrée maximale de 12V, Par conséquent, une tension comprise entre 7V et 12V est recommandée lorsque l'ESP32 est alimenté par la broche VIN.

#### Mode alimentation externe 3.3V
Alternativement, si vous disposez d'une source de tension régulée entre **3.0V** et **3.6V** , la ligne " **3V3** " peut être utilisée pour alimenter directement l'ESP32 et ses périphériques
