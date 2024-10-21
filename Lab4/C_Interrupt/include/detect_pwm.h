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

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "7_seg.h"

#ifndef __DETECT_PWM_H__
    #define __DETECT_PWM_H__

    /** @brief Pin al que se conecta la señal PWM*/
    #define PWM_PIN 12


    void pwm_detect_callback(unsigned int gpio, uint32_t events);
    void update_display_values(uint8_t duty_cycle); 
    void init_pwm_detection();


#endif // __DETECT_PWM_H__