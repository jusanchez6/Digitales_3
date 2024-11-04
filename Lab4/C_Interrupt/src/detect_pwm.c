/**
 * @file detect_pwm.c
 * @brief Detecta la frecuencia de una señal PWM
 * 
 * Este archivo contiene la función detect_pwm que se encarga de detectar la frecuencia de una señal PWM.
 * 
 * @authors María Del Mar Arbeláez
 *         Julián Mauricio Sánchez
 * 
 * @date 2024-10-15
 */

// Standard Libraries
#include <stdio.h>
#include <stdint.h>

// Pico Libraries
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/clocks.h"

// User Libraries
#include "globals.h"
#include "detect_pwm.h"

void pwm_detect_callback (uint gpio, uint32_t events){
    switch (events)    
    {
    case GPIO_IRQ_EDGE_RISE:
        // Guarda el tiempo actual cuando ocurre el flanco de subida
        pulse_time_start = 0;
        g_current_time = time_us_64();
        if (g_last_edge_time != 0){
            g_period = g_current_time - g_last_edge_time;
            g_frequency = 1000000 / (uint32_t)g_period;
        }
        g_last_edge_time = g_current_time;
        pulse_time_start = g_current_time;  // Guarda el tiempo de inicio del pulso
        break;

    case GPIO_IRQ_EDGE_FALL:
        // tomar el tiempo final de la señal en alto para el calculo del duty cycle
        g_current_time = time_us_64();
        uint64_t pulse = g_current_time - pulse_time_start;  // Cambiar aquí
        if (g_period != 0){
            g_duty_cycle = (pulse  * g_frequency) / 10000;  // Convertir a porcentaje
            printf("Duty cycle: %llu%%\n", (uint8_t)g_duty_cycle);
            write_decimals((uint16_t)g_duty_cycle, (uint8_t *)&g_run);

        }
        break;
    default:
        break;
    }

}

void init_pwm_detection(){
    gpio_init(PWM_PIN);
    gpio_set_dir(PWM_PIN, GPIO_IN);
    gpio_pull_down(PWM_PIN);
    gpio_set_irq_enabled_with_callback(PWM_PIN, GPIO_IRQ_EDGE_RISE|GPIO_IRQ_EDGE_FALL, true, &pwm_detect_callback);
}