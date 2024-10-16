/**
 * @file detect_pwm.h
 * @brief Archivo de cabecera de las funciones de detect_pwm.
 * 
 * Archivo de cabecera de las funciones de la libreria detect_pwm.
 * 
 * @authors María Del Mar Arbeláez
 *         Julián Mauricio Sánchez
 * 
 * @date 2024-10-15
 */
#include <stdio.h>
#include <stdint.h>

#ifndef __DETECT_PWM_H__
    #define __DETECT_PWM_H__

    /** @brief Pin al que se conecta la señal PWM*/
    #define PWM_PIN 12

    /** @brief Pin para tomar la medida*/
    #define MEASURE_PIN 15

    

    extern volatile uint64_t g_last_edge_time;
    extern volatile uint64_t g_period;
    extern volatile uint64_t g_frequency;

    void pwm_detect_callback(unsigned int gpio, uint32_t events);
    float measure_duty_cycle(uint gpio);
    void init_pwm_detection();


#endif // __DETECT_PWM_H__