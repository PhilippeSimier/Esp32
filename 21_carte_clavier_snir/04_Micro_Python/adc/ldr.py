"""
analog read
"""

from machine import Pin,ADC
from time import sleep

adc = ADC(Pin(36))
adc.atten(ADC.ATTN_11DB)    # set 11dB input attentuation (voltage range roughly 0.0v - 3.6v)
adc.width(ADC.WIDTH_10BIT)   # set 10 bit return values (returned range 0-1023)
led1 = Pin(13,Pin.OUT)


while True:
    valeur=adc.read()
    print(valeur)
    if valeur>512:
        led1.on()
    else:
        led1.off()    
    sleep(1)
