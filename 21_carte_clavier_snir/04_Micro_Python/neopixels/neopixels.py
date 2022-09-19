"""
Neopixels
       esp8266      esp32
broche   14(13)     18(13)
"""
   
from neopixel import NeoPixel
from machine import Pin

np = NeoPixel(Pin(19), 4)

# GRB format 

np[0] = (0, 255, 0) #set to red, full brightness
np[1] = (128,0, 0) #set to green, half brightness
np[2] = (0, 0, 64) #set blue
np[3] = (64, 64, 0) #set yellow
np.write()

