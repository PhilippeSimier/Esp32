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