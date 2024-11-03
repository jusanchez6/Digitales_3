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


#ifndef _DETECT_PWM_H_
    #define _DETECT_PWM_H_
    //Standard Libraries
    #include <stdio.h>
    #include <stdint.h>
    #include <stdbool.h>
    #include <Arduino.h>
    //Pico Libraries
    #include "hardware/pwm.h"
    
    /** @brief Frecuencia del sistema en KHz*/
    #define SYS_CLK_KHZ 125000

    /** @brief Pin al que se conecta la señal PWM*/
    #define PWM_PIN 13
    void init_pwm_detect();
    uint8_t check_flank(void); //see which 
    void setup_duty_cycle_read();
    uint16_t measure_duty_cycle();
    void calculate_duty(uint16_t* duty);
    

#endif
