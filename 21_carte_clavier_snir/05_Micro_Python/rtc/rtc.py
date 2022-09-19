"""
rtc
"""

from machine import RTC
from time import sleep

rtc = RTC()

#(year, month, day, weekday, hours, minutes, seconds, subseconds)
rtc.datetime((2019, 8, 5, 0,13,55, 0,0)) 

while True:
    horloge=rtc.datetime()
    print(horloge)
    sleep(1)
    
