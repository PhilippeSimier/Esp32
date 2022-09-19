from onewire import OneWire
from ds18x20 import DS18X20
from machine import Pin
from time import sleep_ms
import sys

bus = OneWire(Pin(18))
ds = DS18X20(bus)
capteur_temperature = ds.scan()

while True:
    try:
        ds.convert_temp()       
        sleep_ms(750)
        temp_celsius = ds.read_temp(capteur_temperature[0])
        print("Température : ",temp_celsius )
    except KeyboardInterrupt:
        print('Ctrl-C pressed...exiting')
        sys.exit()
        