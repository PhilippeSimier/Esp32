# Micro-Python

## Micro-Python 

Mycro-Python est un interpréteur Python optimisé pour les microcontrôleurs comme les cartes ESP32. On peut écrire des scripts Python qui seront directement exécutés sur une carte ESP32. Pour ce faire, il suffit de flasher la carte ESP32 avec Micro-Python  et d’utiliser un logiciel IDE (par exemple _Thonny IDE_ ) pour coder des scripts Python et les envoyer à l’ESP32.

## Installation de MicroPython

La première chose que vous devez faire est de télécharger le fichier .bin du micrologiciel Micro-Python le plus récent.  Vous pouvez le télécharger à partir de la page de [téléchargement de MicroPython](https://micropython.org/download/esp32/) .

Si vous installez Micro-Python sur votre carte pour la première fois, vous devez d'abord effacer toute la mémoire  flash.
Installé `pip esptool.py`
```bash
apt install python3-pip
pip install --upgrade pip
pip install esptool
pip install pyserial
```
Vous pouvez effacer la mémoire flash avec la commande, si votre carte est connectée sur ttyUSB0
```bash
esptool.py --port /dev/ttyUSB0 erase_flash
esptool.py v4.3
Serial port /dev/ttyUSB0
Connecting............
Detecting chip type... Unsupported detection protocol, switching and trying again...
Connecting.........
Detecting chip type... ESP32
Chip is ESP32-D0WDQ6 (revision v1.0)
Features: WiFi, BT, Dual Core, 240MHz, VRef calibration in efuse, Coding Scheme None
Crystal is 40MHz
MAC: ec:94:cb:66:2f:ac
Uploading stub...
Running stub...
Stub running...
Erasing flash (this may take a while)...
Chip erase completed successfully in 13.8s
Hard resetting via RTS pin...


```
Et enfin déployez le firmware **MicroPython** en utilisant :

```bash
esptool.py --chip esp32 --port /dev/ttyUSB0 --baud 460800 write_flash -z 0x1000 esp32-20220618-v1.19.1.bin
```
## Thonny python IDE for beginners

Installer Thonny python IDE
Lors du premier lancement on peut choisir la langue "Français"
puis dans le menu **Exécuter > Sélectionner l’interpréteur** et  choisir l'interpréteur MycroPython (ESP32) 
sélectionner le port de communication /dev/ttyUSB0.

![Interpreteur](/21_carte_clavier_snir/05_Micro_Python/Options_interpreteur.png) 

## Premier script Micro-Python sur ESP32

Le premier script fait clignoter la led builtin de le carte ESP32 (présente sur le pin GPIO2).
Ctrl C dans la console permet de quitter le programme.
```python
from machine import Pin
from time import sleep_ms
import sys

led1 = Pin(2,Pin.OUT)

print('Programme test led builtin')
while (True):
    try:
        led1.on()   
        sleep_ms(500)
        led1.off()    
        sleep_ms(500)
    except KeyboardInterrupt:
        print('Ctrl-C pressed...exiting')
        sys.exit()
```

## Quelques commandes utiles en console

Micro-python dispose de nombreux modules pré installés. la commande help("modules") permet de les lister.  Cette liste est  susceptible de s’allonger au fur et à mesure du développement du langage micro-python.
```python
>>> help("modules") 
__main__          gc                ubluetooth        upysh
_boot             inisetup          ucollections      urandom
_onewire          math              ucryptolib        ure
_thread           micropython       uctypes           urequests
_uasyncio         neopixel          uerrno            uselect
_webrepl          network           uhashlib          usocket
apa106            ntptime           uheapq            ussl
btree             onewire           uio               ustruct
builtins          uarray            ujson             usys
cmath             uasyncio/__init__ umachine          utime
dht               uasyncio/core     umqtt/robust      utimeq
ds18x20           uasyncio/event    umqtt/simple      uwebsocket
esp               uasyncio/funcs    uos               uzlib
esp32             uasyncio/lock     upip              webrepl
flashbdev         uasyncio/stream   upip_utarfile     webrepl_setup
framebuf          ubinascii         uplatform         websocket_helper
Plus any modules on the filesystem
```
## Documentation de référence pour ESP32

[Documentation de référence ESP32](https://docs.micropython.org/en/latest/esp32/quickref.html)

## Installation de modules complémentaires

Exécuter le script suivant en adaptant le non du point d'accès WIFI et le mot de passe
```python
import network

# user data
ssid = "xxxxxx" # wifi router name
pw = "xxxxxxxx" # wifi router password

print('Connexion au PA Wifi')
# wifi connection station mode
wifi = network.WLAN(network.STA_IF)
wifi.active(True)
wifi.connect(ssid, pw)

# wait for connection
print('Wifi connecté')
while not wifi.isconnected():
    pass

# wifi connected
print(wifi.ifconfig())
import upip
```
Puis dans la console
```python
>>> upip.install('micropython-ssd1306')
Installing to: /lib/
Warning: micropython.org SSL certificate is not validated
Installing micropython-ssd1306 0.3 from https://files.pythonhosted.org/packages/01/d0/0841d47772962c80af3ab178ef062ed2cd524cb99eb38463e669428402a8/micropython-ssd1306-0.3.tar.gz
>>> 
```

# Changelog

**19/09/2022 : ** Creation du README.md 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 
