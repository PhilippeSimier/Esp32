from machine import Pin
from time import sleep_ms
import sys

relay1 = Pin(27,Pin.OUT)
relay2 = Pin(14,Pin.OUT)

print('Programme test des sorties relais')

while(True):
    try:
        relay1.on()
        sleep_ms(1000)
        relay1.off()
        sleep_ms(1000)
        relay2.on()
        sleep_ms(1000)
        relay2.off()
        sleep_ms(1000)
    except KeyboardInterrupt:
        print('Ctrl-C pressed...exiting')
        sys.exit()