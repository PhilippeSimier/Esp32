"""
rtc hms oled
"""
   

from machine import Pin,I2C,RTC
from time import sleep
from ssd1306 import SSD1306_I2C
i2c = I2C(1,scl=Pin(22), sda=Pin(21))

OLED_WIDTH=128
OLED_HEIGHT=64

oled = SSD1306_I2C(OLED_WIDTH, OLED_HEIGHT, i2c, 0x3c)


rtc = RTC()

#(year, month, day, weekday, hours, minutes, seconds, subseconds)
rtc.datetime((2019, 8, 2, 4,13,55, 0,0)) 

while True:
    horloge=rtc.datetime()
    #heure=str(horloge[4])+':'+str(horloge[5])+':'+str(horloge[6])
    #ou
    heure= s =  "%02d" % horloge[4]+':'+"%02d" % horloge[5]+':'+"%02d" % horloge[6]
    oled.fill(0)
    oled.text(heure ,30, 40)
    oled.show()
    sleep(1)
    



