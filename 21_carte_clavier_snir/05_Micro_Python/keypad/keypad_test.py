
from machine import Pin
from time import sleep

# CONSTANTS
KEY_UP   = const(0)
KEY_DOWN = const(1)

keys = [['1', '2', '3'], ['4', '5', '6'], ['7', '8', '9'], ['*', '0', '#']]

# Connecteur Haut
rows = [26,25,33,32]  
cols = [15,5,4]

# Connecteur bas
#rows = [32, 33, 25, 26]  
#cols = [4, 5, 15]


# set pins for rows as outputs
col_pins = [Pin(pin_name, mode=Pin.OUT) for pin_name in cols]

# set pins for cols as inputs
row_pins = [Pin(pin_name, mode=Pin.IN, pull=Pin.PULL_DOWN) for pin_name in rows]

def init():
    for col in range(0,3):
        col_pins[col].off()

def scan(row, col):
    """ scan the keypad """

    # set the current column to high
    col_pins[col].on()
    key = None

    # check for keypressed events
    if row_pins[row].value() == KEY_DOWN:
        key = KEY_DOWN
    if row_pins[row].value() == KEY_UP:
        key = KEY_UP
    col_pins[col].off()

    # return the key state
    return key

print("starting")

# set all the columns to low
init()

while True:
    for col in range(3):
        for row in range(4):
            key = scan(row, col)
            if key == KEY_DOWN:
                print("Key Pressed", keys[row][col])
                last_key_press = keys[row][col]
                
        

