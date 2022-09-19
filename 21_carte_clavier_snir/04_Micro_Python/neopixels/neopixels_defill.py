"""
Neopixels
"""

NBPIXELS=4

from neopixel import NeoPixel
from machine import Pin
from time import sleep_ms

np = NeoPixel(Pin(19), 4)


def defilement(color):
    for p in range(NBPIXELS):
        np[p] = color
        np[(p-1)%NBPIXELS]=(0,0,0)
        np.write()
        sleep_ms(100)

while(True):
    defilement((0,255,0))




