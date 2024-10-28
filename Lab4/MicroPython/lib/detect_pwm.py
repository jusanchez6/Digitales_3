from machine import Pin
import time

PWM_PIN = 12

# Variables globales para el cálculo de frecuencia y ciclo de trabajo
g_last_edge_time = 0
g_current_time = 0
g_period = 0
g_frequency = 0
g_duty_cycle = 0
pulse_time_start = 0

def pwm_detect_callback(pin):
    """Callback function to detect the PWM signal.
    Args:
        pin (Pin): The pin object that triggered the interrupt.
    Returns:
        None
    """
    global g_last_edge_time, g_current_time, g_period, g_frequency, g_duty_cycle, pulse_time_start
    g_current_time = time.ticks_us()

    if (pin.value() == 1):
        if (g_last_edge_time != 0):
            g_period = g_current_time - g_last_edge_time
            g_frequency = 1000000 / g_period
        
        g_last_edge_time = g_current_time
        pulse_time_start = g_current_time

    else:
        pulse = time.ticks_diff(g_current_time, pulse_time_start)
        if (g_period != 0):
            g_duty_cycle = (pulse / g_period) * 100
            
def init_pwm_detection():
    """Initialize the PWM detection.
    Args:
        None
    Returns:
        None
    """
    pin = Pin(PWM_PIN, Pin.IN)
    pin.irq(trigger=Pin.IRQ_RISING | Pin.IRQ_FALLING, handler=pwm_detect_callback)
    print("PWM detection initialized.")       

