"""
affiche la température dans une page web
"""
import usocket as socket
from machine import Pin
from onewire import OneWire
from ds18x20 import DS18X20
from time import sleep_ms
import network,sys

bus = OneWire(Pin(18))
ds = DS18X20(bus)
capteur_temperature = ds.scan()
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


temp_celsius=0

def web_page():
  html = """<html>
            <head>
            <title>Temperature Web Server</title>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <script>
 
            setInterval(function() {
            getData();
            }, 2000); //mise à jour toutes les 2000 milli Secondes 
 
            function getData() {
               var xhttp = new XMLHttpRequest();
               xhttp.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                       document.getElementById("TEMPValue").innerHTML = this.responseText;
                   }
               };
             xhttp.open("GET", "TEMPValue", true);
             xhttp.send();
            }
            </script>
            </head>
            <body>
            <h1>Température de la pièce: <span id="TEMPValue">"""+str(temp_celsius)+"""</span> °C
            </h1> 
            </body>
            </html>"""

  return html

def conversion_temerature():
    global temp_celsius
    ds.convert_temp()       
    temp_celsius = ds.read_temp(capteur_temperature[0])
    print("Température : ",temp_celsius )
      

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind(('', 80))
s.listen(5)

while True:
    try:
        conn, addr = s.accept()
        print('Got a connection from %s' % str(addr))
        request = conn.recv(1024)
        request = str(request)
        print('Content = %s' % request)
        root = request.find('/ ')               #demande de la page html
        temp = request.find('/TEMPValue')       #demande de température
        conversion_temerature()
        if root==6:
          conn.send('HTTP/1.1 200 OK\n')
          conn.send('Content-Type: text/html\n') #html
          conn.send('Connection: close\n\n')
          response = web_page()
          conn.sendall(response)
          conn.close()
        elif temp==6:      
          conn.send('HTTP/1.1 200 OK\n')
          conn.send('Content-Type: text/plane\n') #que du texte
          conn.send('Connection: close\n\n')
          conn.sendall(str(temp_celsius))
          conn.close()
    except KeyboardInterrupt:
        print('Ctrl-C pressed...exiting')
        s.close()
        sys.exit()
