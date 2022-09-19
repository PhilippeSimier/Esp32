"""
wifi connexion et installation le la bibliotheque ssd1306
Installing to: /lib/
Warning: micropython.org SSL certificate is not validated
Installing micropython-ssd1306 0.3 from https://files.pythonhosted.org/packages/01/d0/0841d47772962c80af3ab178ef062ed2cd524cb99eb38463e669428402a8/micropython-ssd1306-0.3.tar.gz
Après l'installation d'une blibliothèque faire un reset de la carte
"""


import network

# user data
ssid = "xxxxxxxxxx" # wifi router name
pw = "xxxxxxxxxxx" # wifi router password

# wifi connection station mode
wifi = network.WLAN(network.STA_IF)
wifi.active(True)
wifi.connect(ssid, pw)

# wait for connection
while not wifi.isconnected():
    pass

# wifi connected
print(wifi.ifconfig())

import upip
upip.install('micropython-ssd1306')



