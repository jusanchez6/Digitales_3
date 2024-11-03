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

    //Standard Libraries
    #include <stdio.h>
    #include <stdint.h>
    #include <stdbool.h>

    //Pico Libraries
    #include "pico/stdlib.h"
    #include "hardware/pwm.h"
    
    /** @brief Pin al que se conecta la señal PWM*/
    #define PWM_PIN 13
    
    /** @brief Función que averigua el canal y el slice del gpio
     * 
     * @param void 
     * 
     * @return void
    */
    void init_pwm_detect();

    /** @brief Función que hace el setup de la lectura del pwm con hardware
     * 
     * @param void
     * 
     * @return void
    */
    void setup_duty_cycle_read();

    /** @brief Función con el flujo de la lectura del pwm
     * 
     * Esta función hace el setup, espera cierto tiempo 
     * 
     * @param void
     * 
     * @return void
    */
    uint16_t measure_duty_cycle();
    void calculate_duty(uint16_t* duty);
    
#endif
