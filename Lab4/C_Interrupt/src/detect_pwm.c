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
#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/clocks.h"
#include "globals.h"

#include "detect_pwm.h"

volatile uint64_t g_current_time;
volatile uint64_t g_last_edge_time;
volatile uint64_t g_period;
volatile uint64_t g_frequency;

volatile uint64_t pulse_time_start = 0;

/**
 * @brief Función que se llama cuando se detecta un flanco de subida en la señal PWM
 * 
 * Esta función se llama cuando se detecta un flanco de subida en la señal PWM.
 * 
 * @param gpio Pin en el que se detectó el flanco de subida
 * @param events Eventos que ocurrieron en el pin
 */

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
            printf("Pulse: %llu us\n", pulse);
            g_duty_cycle = (pulse  * g_frequency) / 10000;  // Convertir a porcentaje
            printf("Duty cycle: %llu%%\n", (uint8_t)g_duty_cycle);
            uint8_t en = 0;
            update_display_flag = 1;

        }
        break;
    default:
        break;
    }

    //printf("Period: %llu us\n", g_period);
    printf("Frequency: %llu Hz\n", g_frequency);
    //printf("Duty cycle: %f%%\n", g_duty_cycle);  // Imprimir en porcentaje
}

/**
 * @brief Función que inicializa la detección de la señal PWM
 * 
 * Esta función inicializa la detección de la señal PWM en el pin 12.
 * 
 */
void init_pwm_detection(){
    gpio_init(PWM_PIN);
    gpio_set_dir(PWM_PIN, GPIO_IN);
    gpio_pull_down(PWM_PIN);
    gpio_set_irq_enabled_with_callback(PWM_PIN, GPIO_IRQ_EDGE_RISE|GPIO_IRQ_EDGE_FALL, true, &pwm_detect_callback);
}

