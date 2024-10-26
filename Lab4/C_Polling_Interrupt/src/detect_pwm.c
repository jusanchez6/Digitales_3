/**
 * @file detect_pwm.c
 * 
 * @brief Funciones para la detección de señales PWM
 * 
 * Este archivo contiene las funciones necesarias para la detección de señales PWM
 * 
 * @authors Maria Del Mar Arbeláez
 *         Julian Mauricio Sánchez
 * 
 * @date 2024-10-21
 * 
 * @see detect_pwm.h
 */

// Standar C Libraries
#include <stdio.h>
#include <stdint.h>

// picoSDK Libraries
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/clocks.h"

// User Libraries
#include "../include/globals.h"
#include "../include/detect_pwm.h"



void detect_pwm_callback (unsigned int gpio, uint32_t events){
    switch (events)
    {
    case GPIO_IRQ_EDGE_RISE:
        g_last_edge_time = time_us_64();
        g_flags.edge_flag = true;
        break;
    
    case GPIO_IRQ_EDGE_FALL:
        g_period = time_us_64();
        g_flags.fall_flag = true;
        break;
    default:
        break;
    }
}

void detect_pwm_init (void ){
    gpio_init(PWM_PIN);
    gpio_set_dir(PWM_PIN, GPIO_IN);
    gpio_pull_down(PWM_PIN);

    gpio_set_irq_enabled_with_callback(PWM_PIN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &detect_pwm_callback);
    
}

