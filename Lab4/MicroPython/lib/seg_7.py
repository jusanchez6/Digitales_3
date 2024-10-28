from machine import Pin
import time

START_PIN = 2
EN_1_PIN = 11
EN_2_PIN = 10
EN_3_PIN = 9
    
SEGMENT_PINS = [Pin(i, Pin.OUT) for i in range(START_PIN, START_PIN + 7)]
    
EN_1 = Pin(EN_1_PIN, Pin.OUT)
EN_2 = Pin(EN_2_PIN, Pin.OUT)
EN_3 = Pin(EN_3_PIN, Pin.OUT)

enable_pins = [EN_1, EN_2, EN_3]

# Tabla de conversion
lookup = [
       0x3f, 0x06, 0x5b, 0x4f, 0x66,
       0x6d, 0x7d, 0x07, 0x7f, 0x6f
]



def init():
    """Initialize the 7-segment display.
    Args:
        None
    Returns:
        None
    """

    # Inicializacion de los pines
    for seg_pins in SEGMENT_PINS:
        seg_pins.off()
    for en_pin in enable_pins:
        en_pin.off()
    print("7-Segment display initialized.")

def write_value(value):
    """Write a value to the 7-segment display.
    Args:
        value (int): The value to display.
    
    Returns:
        None
    """
    global SEGMENT_PINS
    bits = lookup[value]
    for i, seg_pin in enumerate(SEGMENT_PINS):
        seg_pin.value((bits >> i) & 1)  # Set the bit value to the pin
        
def write_decimals(value, run):
    """Write a value to the 7-segment display with decimals.
    Args:
        value (int): The value to display.
    
    Returns:
        None
    """
    start_time = time.ticks_us()

    while True: #------------------------------------> Loop infinito que no creo que funcione

        if time.ticks_diff(time.ticks_ms(), write_decimals.last_time) > 4600:
            # Apaga el anterior display
            if(run > 0):
                enable_pins[run-1].off()    # Apaga el display anterior
            else:
                enable_pins[2].off()        # Apaga el display anterior

            # Descomponer el valor en unidades, decenas y centenas
            if (run == 0):
                val_2_wr = value % 10
            elif (run == 1):
                val_2_wr = (value // 10) % 10
            else:
                val_2_wr = (value // 100) % 10

            # Escribir el valor en el display
            write_value(val_2_wr)
            enable_pins[run].on()    # Enciende el display actual
            start_time = time.ticks_us()
            run = (run + 1) % 3     # Siguiente display (se reinicia si llega a 3)         