"""
@file main.py
@brief  Archivo principal del proyecto.

Este archivo contiene el código principal del proyecto. Se encarga de leer la señal PWM de un pin de entrada y mostrar la frecuencia y el ciclo de trabajo en un display de 7 segmentos.

@authors Maria Del Mar Arbelaez
        Julian Mauricio Sanchez

@date 2024-10-28
"""


from machine import Pin
import time

PWN_IN_PIN = 13
# Configuración del pin de entrada
pwm_pin = Pin(PWN_IN_PIN, Pin.IN)

# Variables globales
last_rising_edge = 0      # Tiempo del último flanco de subida
period = 0                # Periodo de la señal
frequency = 0             # Frecuencia calculada
duty_cycle = 0            # Ciclo de trabajo calculado
pulse_high_time = 0       # Tiempo en alto del pulso

START_PIN = 2
EN_1_PIN = 12
EN_2_PIN = 11
EN_3_PIN = 10

SEGMENT_PINS = [Pin(i, Pin.OUT) for i in range(START_PIN, START_PIN + 8)]
EN_1 = Pin(EN_1_PIN, Pin.OUT)
EN_2 = Pin(EN_2_PIN, Pin.OUT)
EN_3 = Pin(EN_3_PIN, Pin.OUT)

enable_pins = [EN_1, EN_2, EN_3]

# Tabla de conversión
lookup = [
    0x3f, 0x06, 0x5b, 0x4f, 0x66,
    0x6d, 0x7d, 0x07, 0x7f, 0x6f
]

def pwm_callback(pin):
    """
    @brief Callback para la señal PWM.
    
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
    """
    @brief Inicializa el display de 7 segmentos.

    Esta función inicializa el display de 7 segmentos apagando todos los segmentos y displays.

    @param None

    @return None

    """
    for seg_pin in SEGMENT_PINS:
        seg_pin.off()
    for en_pin in enable_pins:
        en_pin.off()
    print("Display de 7 segmentos inicializado.")

def write_value(value):
    """
    @brief Escribe un valor en el display de 7 segmentos.
    
    Esta función escribe un valor en el display de 7 segmentos.

    @param value Valor a escribir en el display.

    @return None
    """
    bits = lookup[value]
    for i, seg_pin in enumerate(SEGMENT_PINS):
        seg_pin.value((bits >> i) & 1)

def write_decimals(value):
    """
    @brief Muestra el valor en el display de 7 segmentos.
    
    Esta función se encarga de gestionar la multiplexacion en un display de 7 segmentos triple

    @param value Valor a mostrar en el display.

    @return None
    """
    for run in range(3):  # Muestra en 3 dígitos
        # Apaga el display anterior
        if run > 0:
            enable_pins[run - 1].off()
        else:
            enable_pins[2].off()

        # Descomponer el valor en unidades, decenas y centenas
        if run == 0:
            val_to_write = value % 10
        elif run == 1:
            val_to_write = (value // 10) % 10
        else:
            val_to_write = (value // 100) % 10

        # Escribe el valor en el display
        write_value(val_to_write)
        enable_pins[run].on()  # Enciende el display actual

        # Mantiene el dígito encendido por un tiempo breve
        time.sleep(0.0074)  # Mantiene el dígito encendido por 10 ms

    # Apaga el último display después de mostrar
    enable_pins[2].off()




def main():
    """
    @brief Función principal del programa.

    Esta función es la función principal del programa. Se encarga de inicializar el pin de entrada y el display de 7 segmentos, y de mostrar la frecuencia y el ciclo de trabajo de la señal PWM.

    @param None

    @return None

    """
    pwm_pin.irq(trigger=Pin.IRQ_RISING | Pin.IRQ_FALLING, handler=pwm_callback)

    # Inicializa el display de 7 segmentos
    init()

    while True:
        try:
            # Imprime los resultados
            print(f"Frecuencia: {frequency:.2f} Hz, Duty Cycle: {duty_cycle:.2f} %")
    
            # Muestra el duty cycle en el display
            write_decimals(int(duty_cycle))

        except KeyboardInterrupt:
            print("Interrupción del usuario.")
            break

if __name__ == "__main__":
    main()

