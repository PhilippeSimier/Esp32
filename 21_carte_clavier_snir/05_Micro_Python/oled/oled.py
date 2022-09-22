"""
display test
"""


from machine import Pin,I2C
from ssd1306 import SSD1306_I2C

i2c = I2C(1,scl=Pin(22), sda=Pin(21))

display_WIDTH=128
display_HEIGHT=64

display = SSD1306_I2C(display_WIDTH, display_HEIGHT, i2c, 0x3c)
display.fill(0)
display.text("Hello BTS", 30, 30)
display.show()
 

