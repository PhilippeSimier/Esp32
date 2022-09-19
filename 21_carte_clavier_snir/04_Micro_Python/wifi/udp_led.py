"""
serveur udp pour commander une led (char o/n)
"""
from machine import Pin
import socket,sys

led1 = Pin(13,Pin.OUT)

import network

# user data
ssid = "xxxxxxxxxx" # wifi router name
pw = "xxxxxxxxxxx" # wifi router password
# wifi connection station mode
wifi = network.WLAN(network.STA_IF)
wifi.active(True)
wifi.connect(ssid, pw)
while not wifi.isconnected():
    pass
print(wifi.ifconfig())

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind(('', 5000))
print("A l'écoute du port 5000")

while True:
    try:
        data, addr = s.recvfrom(1024)
        print('received:',data,'from',addr)
        if (data.decode()=='o'):
            led1.on()
        elif (data.decode()=='n'):
            led1.off()
    except KeyboardInterrupt:
        print('Ctrl-C pressed...exiting')
        s.close()
        sys.exit()
