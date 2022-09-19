from machine import Timer,Pin
from time import sleep_ms
import sys


class Keypad_Timer () :
    """
    Class to scan a Keypad matrix (e.g. 12-keys as 3x4 matrix) and report
    last key press.
    """

    #! Key states
    KEY_UP      = const( 0 )
    KEY_DOWN    = const( 1 )

    #-------------------------------------------------------------------------

    def __init__ ( self ) :
        self.init()

    #-------------------------------------------------------------------------

    def init ( self ) :
        """Initialise/Reinitialise the instance."""

        self.keys = [['1', '2', '3'], ['4', '5', '6'], ['7', '8', '9'], ['*', '0', '#']]
        #! Initialise all keys to the UP state.
        self.state = [[self.KEY_UP] * 3 for _ in range(4)]

        # Connecteur Haut
        self.rows = [26,25,33,32]  
        self.cols = [15,5,4]

        # Connecteur bas
        #self.rows = [32, 33, 25, 26]  
        #self.cols = [4, 5, 15]

        # set pins for cols as outputs
        self.col_pins = [Pin(pin_name, mode=Pin.OUT) for pin_name in self.cols]

        # set pins for rows as inputs
        self.row_pins = [Pin(pin_name, mode=Pin.IN, pull=Pin.PULL_DOWN) for pin_name in self.rows]

        self.timer = Timer(1)

        self.scan_col = 0        
        self.key_char = None

    #-------------------------------------------------------------------------

    def get_key ( self ) :
        """Get last key pressed."""

        key_char = self.key_char

        self.key_char = None    #! consume last key pressed

        return key_char

    #-------------------------------------------------------------------------

    def key_process ( self, row, row_pin ) :
        """Process a key press or release."""

        key_event = None

        if row_pin.value():
            if self.state[row][self.scan_col] == self.KEY_UP :
                key_event = self.KEY_DOWN
                self.state[row][self.scan_col] = key_event
        else:
            if self.state[row][self.scan_col] == self.KEY_DOWN :
                key_event = self.KEY_UP
                self.state[row][self.scan_col] = key_event

        return key_event

    #-------------------------------------------------------------------------

    def scan_row_update(self):
        """
        Timer interrupt callback to scan next keypad column/raw.
        NOTE: This is a true interrupt and no memory can be allocated !!
        """

        #! Deassert row.
        self.col_pins[ self.scan_col ].off()

        #! Next scan row.
        self.scan_col = ( self.scan_col + 1 ) % len( self.col_pins )

        #! Assert next row.
        self.col_pins[ self.scan_col ].on()

    #-------------------------------------------------------------------------

    def timer_callback ( self, timer ) :
        """
        Timer interrupt callback to scan next keypad row/column.
        """
        
        for row in range( len( self.rows ) ) :
            #! Process pin state.
            key_event = self.key_process( row, self.row_pins[ row ] )
            
            #! Process key event.
            if key_event == self.KEY_DOWN:                
                self.key_char = self.keys[row][self.scan_col]

        self.scan_row_update()
        
    #-------------------------------------------------------------------------

    def start ( self ) :
        """Start the timer."""
        self.timer.init(period=100, mode=Timer.PERIODIC, callback=self.timer_callback)

    #-------------------------------------------------------------------------

    def stop ( self ) :
        """Stop the timer."""
        self.timer.deinit()

#!============================================================================


keypad = Keypad_Timer()
keypad.start()

while True:
    try:
        key = keypad.get_key()
        if key :
            print( "keypad: got key:", key )
        sleep_ms(100)
    except KeyboardInterrupt:
        print('Ctrl-C pressed...exiting')
        keypad.stop()
        sys.exit()
