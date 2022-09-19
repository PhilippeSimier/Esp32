from machine import Pin
from time import sleep_ms

led1 = Pin(13,Pin.OUT)
led2 = Pin(12,Pin.OUT)

while(True):
    led1.on()
    led2.off()
    sleep_ms(500)
    led1.off()
    led2.on()
    sleep_ms(500)
    