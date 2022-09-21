from machine import Pin
from time import sleep_ms

relay1 = Pin(27,Pin.OUT)
relay2 = Pin(14,Pin.OUT)

while(True):
    relay1.on()
    sleep_ms(1000)
    relay1.off()
    sleep_ms(1000)
    relay2.on()
    sleep_ms(1000)
    relay2.off()
    sleep_ms(1000)