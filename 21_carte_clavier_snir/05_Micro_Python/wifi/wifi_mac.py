"""
test de la connexion wifi et affichage de l'adresse MAC
"""

import network
import ubinascii

# wifi connection station mode
wifi = network.WLAN(network.STA_IF)

# wifi is connected ?
if wifi.isconnected():
    ip=wifi.ifconfig()
    print(ip[0])
    mac = ubinascii.hexlify(network.WLAN().config('mac'),':').decode()
    print(mac)
else:
    print (" NON connecté au réseau wifi")





