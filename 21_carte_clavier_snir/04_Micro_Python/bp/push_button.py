from machine import Pin

bp1 = Pin(39, Pin.IN)
bp2 = Pin(34, Pin.IN)
bp3 = Pin(35, Pin.IN)

led1 = Pin(13,Pin.OUT)
led2 = Pin(12,Pin.OUT)

while True:
    if bp1.value() == 0:
        led1.on()
    if bp2.value() == 0:
        led2.on()
    if bp3.value() == 0:
        led1.off()
        led2.off()