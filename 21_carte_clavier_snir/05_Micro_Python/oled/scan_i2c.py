"""
scan i2c esp32
Scan i2c bus...
i2c devices found: 1
Decimal address:  60  | Hexa address:  0x3c
"""

from machine import Pin,I2C
i2c = I2C(1,scl=Pin(22), sda=Pin(21))

print('Scan i2c bus...')
devices = i2c.scan()

if len(devices) == 0:
    print("No i2c device !")
else:
    print('i2c devices found:',len(devices))

for device in devices:  
    print("Decimal address: ",device," | Hexa address: ",hex(device))
