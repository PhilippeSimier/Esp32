"""
Uart echo
"""

from machine import UART

uart = UART(2, baudrate=9600)
  
while True:
    if uart.any()>0:
        strMsg=uart.read()
        print(strMsg.decode())
        uart.write(strMsg)
        
