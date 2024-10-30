/**
 * @file detect_pwm.h
 * @brief Archivo de cabecera de las funciones de los 7 segmentos.
 * 
 * Archivo de cabecera de las funciones de la libreria.
 * 
 * @authors María Del Mar Arbeláez
 *          Julián Mauricio Sánchez
 * 
 * @date 2024-10-12
 */

#include <stdint.h>

#ifndef _DETECT_PWM_H_
    #define _DETECT_PWM_H_

    #define PWM_PIN 13
    void init_pwm_detect();
    uint8_t check_flank(void); //see which 
    void setup_duty_cycle_read();
    uint16_t measure_duty_cycle();
    void calculate_duty(uint16_t* duty);
    

#endif
