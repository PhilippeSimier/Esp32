"""
import upip
upip.install('picoweb')
upip.install('utemplate')
upip.install('pycopy-ulogging')
"""

import picoweb
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

app = picoweb.WebApp(__name__)

def web_page():
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
            </style>
            </head>
            <body>
            <h1>ESP Web Server</h1> 
             </body></html>"""
  return html

@app.route("/")
def index(req, resp):
    yield from picoweb.start_response(resp)
    yield from resp.awrite(web_page())
 
app.run(debug=True, port=80, host = wifi.ifconfig()[0])
