"""
mini serveur web elementaire
"""

from machine import Pin
import usocket as socket
import network,sys

led1 = Pin(13,Pin.OUT)

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


def web_page():
  if led1.value() == 1:
    gpio_state="ON"
  else:
    gpio_state="OFF"
  
  html = """<html>
            <head>
            <title>ESP Web Server</title>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <style>
            html {
            font-family: Helvetica;
            display:inline-block;
            margin: 0px auto;
            text-align: center;
            }
            h1{
            color: #0F3376;
            padding: 2vh;
            }
            p{
            font-size: 1.5rem;
            }
            .button1{
            display: inline-block;
            background-color: #e7bd3b;
            border: none; 
            border-radius: 4px;
            color: white;
            padding: 16px 40px;
            text-decoration: none;
            font-size: 30px;
            margin: 2px;
            cursor: pointer;
            }
            .button2{
            background-color: #4286f4;
            }
            </style>
            </head>
            <body>
            <h1>ESP Web Server</h1> 
            <p>GPIO state: """ + gpio_state + """</p>
            <p><a href="/?led=on"><button class="button1">ON</button></a></p>
             <p><a href="/?led=off"><button class="button1 button2">OFF</button></a></p>
             </body></html>"""

  return html

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
        led_on = request.find('/?led=on')
        led_off = request.find('/?led=off')
        if led_on == 6:
            print('LED ON')
            led1.on()
        if led_off == 6:
            print('LED OFF')
            led1.off()
        response = web_page()
        conn.send('HTTP/1.1 200 OK\n')
        conn.send('Content-Type: text/html\n')
        conn.send('Connection: close\n\n')
        conn.sendall(response)
        conn.close()
    except KeyboardInterrupt:
        print('Ctrl-C pressed...exiting')
        s.close()
        sys.exit()
  