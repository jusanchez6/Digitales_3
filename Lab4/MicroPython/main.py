##
# @file main.py
#
# @brief  Archivo principal del proyecto.
#
# Este archivo contiene el código principal del proyecto.
# Se encarga de leer la señal PWM de un pin de entrada y mostrar la frecuencia y el ciclo de trabajo en un display de 7 segmentos.
#
# @date 2024-11-04
##

from machine import Pin
import time
import gc

## Pin de entrada de PWM
PWN_IN_PIN = 13

## Configuración del pin de entrada
pwm_pin = Pin(PWN_IN_PIN, Pin.IN)

# Variables globales

## Tiempo del último flanco de subida
last_rising_edge = 0  

## Periodo de la señal
period = 0

## Frecuencia calculada
frequency = 0

## Ciclo de trabajo calculado
duty_cycle = 0

 ## Tiempo en alto del pulso
pulse_high_time = 0      

## Offset de los pines de salida
START_PIN = 2

## PIN para habilitar display 1
EN_1_PIN = 12

## PIN para habilitar display 2
EN_2_PIN = 11

## PIN para habilitar display 3
EN_3_PIN = 10

## Habilitar pines del siete segmentos como salida
SEGMENT_PINS = [Pin(i, Pin.OUT) for i in range(START_PIN, START_PIN + 8)]

## Habilitar pines del display 1 como salida
EN_1 = Pin(EN_1_PIN, Pin.OUT)

## Habilitar pines del display 2 como salida
EN_2 = Pin(EN_2_PIN, Pin.OUT)

## Habilitar pines del display 3 como salida
EN_3 = Pin(EN_3_PIN, Pin.OUT)

## Lista de los pines de habilitación
enable_pins = [EN_1, EN_2, EN_3]

## Tabla de conversión
lookup = [
    0x3f, 0x06, 0x5b, 0x4f, 0x66,
    0x6d, 0x7d, 0x07, 0x7f, 0x6f
]

def mostrar_memoria():
    """! Muestra el consumo de memoria.
    
    Esta función imprime la memoria libre y total disponible.

    @return None
    """
    gc.collect()  # Ejecuta recolección de basura
    memoria_libre = gc.mem_free()
    memoria_total = gc.mem_alloc() + memoria_libre
    print(f"Memoria libre: {memoria_libre} bytes")
    print(f"Memoria total: {memoria_total} bytes")

def pwm_callback(pin):
    """! Callback para la señal PWM.
    
    Esta función se llama cuando se detecta un flanco de subida o bajada en la señal PWM.

    @param pin Pin de entrada.

    @return None
    """
    global last_rising_edge, period, frequency, duty_cycle, pulse_high_time
    
    current_time = time.ticks_us()  # Captura el tiempo actual en microsegundos
    
    if pin.value() == 1:  # Flanco de subida
        if last_rising_edge != 0:
            period = time.ticks_diff(current_time, last_rising_edge)
            frequency = 1000000 / period  # Frecuencia en Hz
        last_rising_edge = current_time
    else:  # Flanco de bajada
        pulse_high_time = time.ticks_diff(current_time, last_rising_edge)
        if period > 0:
            duty_cycle = (pulse_high_time / period) * 100

def init():
    """! Inicializa el display de 7 segmentos.

    Esta función inicializa el display de 7 segmentos apagando todos los segmentos y displays.

    @return None
    """
    for seg_pin in SEGMENT_PINS:
        seg_pin.off()
    for en_pin in enable_pins:
        en_pin.off()
    print("Display de 7 segmentos inicializado.")

def write_value(value):
    """! Escribe un valor en el display de 7 segmentos.
    
    @param value Valor a escribir en el display.

    @return None
    """
    bits = lookup[value]
    for i, seg_pin in enumerate(SEGMENT_PINS):
        seg_pin.value((bits >> i) & 1)

def write_decimals(value):
    """! Muestra el valor en el display de 7 segmentos.
    
    Esta función se encarga de gestionar la multiplexacion en un display de 7 segmentos triple.

    @param value Valor a mostrar en el display.

    @return None
    """
    for run in range(3):  # Muestra en 3 dígitos
        if run > 0:
            enable_pins[run - 1].off()
        else:
            enable_pins[2].off()

        if run == 0:
            val_to_write = value % 10
        elif run == 1:
            val_to_write = (value // 10) % 10
        else:
            val_to_write = (value // 100) % 10

        write_value(val_to_write)
        enable_pins[run].on()

        time.sleep(0.0074)

    enable_pins[2].off()

def main():
    """! Función principal del programa.

    Esta función inicializa el pin de entrada y el display de 7 segmentos, y muestra la frecuencia y el ciclo de trabajo de la señal PWM.

    @return None
    """
    pwm_pin.irq(trigger=Pin.IRQ_RISING | Pin.IRQ_FALLING, handler=pwm_callback)

    init()  # Inicializa el display de 7 segmentos
    mostrar_memoria()  # Muestra la memoria antes de iniciar el programa

    while True:
        try:
            print(f"Frecuencia: {frequency:.2f} Hz, Duty Cycle: {duty_cycle:.2f} %")
            write_decimals(int(duty_cycle))
            mostrar_memoria()  # Muestra la memoria en cada ciclo

        except KeyboardInterrupt:
            print("Interrupción del usuario.")
            break

if __name__ == "__main__":
    main()
