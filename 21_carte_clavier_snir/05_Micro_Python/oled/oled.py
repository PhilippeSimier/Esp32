"""
oled test
"""


from machine import Pin,I2C
from ssd1306 import SSD1306_I2C
i2c = I2C(1,scl=Pin(22), sda=Pin(21))

OLED_WIDTH=128
OLED_HEIGHT=64

oled = SSD1306_I2C(OLED_WIDTH, OLED_HEIGHT, i2c, 0x3c)
oled.fill(0)
oled.text("Hello BTS", 30, 30)
oled.show()
 

