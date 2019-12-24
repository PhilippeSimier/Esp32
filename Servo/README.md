# Servomoteur & Esp32 

# Description
Ce dossier propose une classe simple pour commander des servomoteurs.
Les servomoteurs sont pilotés par un fil de commande (blanc ou orange) et alimentés par deux autres fils (rouge 5v  marron Gnd).  Le signal de commande d’un servomoteur est standardisé, c'est le temps de l' impulsion qui détermine l'angle du servomoteur. 
Si le temps d'impulsion varie d'un fabricant  à l'autre, les valeurs suivantes sont assez standard:
1 ms = 0 degré
1.50 ms = 90 degrés
2 ms = 180 degrés

![Impulsions](/Servo/signal.png)

La période du signal est de 20 ms, le signal  généré doit donc avoir une fréquence de 50 Hz. 
 

# PWM avec ESP32
l'ESP32 comporte 16 canaux PWM.  Ces canaux sont numérotés de 0 à 15. Pour générer et contrôler le signal PWM, notre classe dispose de 3 fonctions  **ledcAttachPin**, **ledcSetup** et **ledcWrite**.

 - **ledcAttachPin(broche GPIO, canal)**
Cette fonction sert à associer une broche GPIO à l'un des 16 canaux PWM, qui sont numérotés de 0 à 15. Par exemple, si on désire produire un signal PWM sur la broche GPIO 18,  "ledcAttachPin(18, 0)" fera en sorte que le signal généré par le canal 0 sera acheminé à la broche 18.
 - **ledcSetup(canal, fréquence, résolution)** 
Cette fonction permet de  régler la fréquence et la résolution d'un canal PWM. La fréquence est en hertz. La résolution, qui peut prendre  n'importe quelle valeur entière située entre 1 et 16, détermine le nombre valeurs distinctes pouvant être prises par le rapport  cyclique. Par exemple: avec une résolution de 16 bits, le rapport cyclique pourra prendre 2^16 = 65536 valeurs différentes, alors qu'avec une résolution de 8 bits, le nombre de valeurs possibles ne sera que de 2^8= 256.
 - **ledcWrite(canal, rapport cyclique)** Cette fonction permet de régler le rapport cyclique du signal PWM du canal spécifié.  Par exemple,  "ledcWrite(0, 250)" règle à 250 le rapport cyclique du canal 0.   Le résultat de cette commande dépend de la résolution   préalablement réglée avec la fonction ledcSetup: si la résolution est   de 12 bits, 250/2^12 correspond à un rapport cyclique d'environ 6%; si la résolution est de 10 bits, 250/2^10 correspond plutôt à un rapport   cyclique de 24%, et le rapport cyclique sera de 98%  (250/2^8 ) à une   résolution de 8 bits.
 - 
# La classe ServoMoteur

Le **constructeur** associe un canal PWM disponible, La précision du rapport cyclique  est configurée sur 16 bits de résolution.  Pour ce faire, le constructeur appelle la fonction ledcSetup. La classe ServoMoteur peut être instanciée 16 fois au maximum. Au delà il n'y a plus de canaux PWM disponibles.

La méthode **Attacher** permet d'attacher une broche GPIO au canal PWM, cette méthode  appelle la fonction ledcAttachPin , en passant comme arguments le numéro de la broche GPIO et le canal PWM définis par le constructeur.  de plus la méthode attacher permet de définir en µs la longueur mini et maxi de l'impulsion. Si ces deux valeurs ne sont pas fournies alors les valeurs par défaut de 544 µs et 2400 µs seront utilisées.

La méthode  **Positionner** donne une consigne d’angle à laquelle le servomoteur doit aller. Cette méthode prend pour argument un nombre, de type int , qui donne la valeur en degré de l’angle à atteindre. 


# Raccordement avec esp32 





# Changelog

**23/12/2019 : ** Ajout de la classe ServoMoteur . 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


