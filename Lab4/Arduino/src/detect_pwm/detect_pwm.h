/**
 * @file ./Arduino/src/detect_pwm/detect_pwm.h
 * @brief Archivo de cabecera de las funciones de los 7 segmentos.
 * 
 * Archivo de cabecera de las funciones de la librería.
 * 
 * @authors María Del Mar Arbeláez
 *          Julián Mauricio Sánchez
 * 
 * @date 2024-11-04
 * 
 * @see detect_pwm.c
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

    /**
     * @brief Función que inicializa el channel y slice de un GPIO
     * 
     * @param void
     * @return void
     */
    void init_pwm_detect();

    /**
     * @brief Función que inicializa el channel y slice de un GPIO
     * 
     * @param void
     * @return void
     */
    void setup_duty_cycle_read();

    /**
     * @brief Función que genera el flujo para encontrar el ciclo de dureza
     * 
     * Esta función se encarga de llamar a inicialización y a esperar
     * hasta que el valor de conteo esté listo para hacer el cálculo.
     * 
     * @param void
     * 
     * @return ciclo de dureza en 16 bits
     */
    uint16_t measure_duty_cycle();

    /**
     * @brief Función que hace el cálculo del ciclo de dureza
     * 
     * @param duty puntero a la variable que guarda el ciclo de dureza.
     * 
     * @return void
     */
    void calculate_duty(uint16_t* duty);
    

#endif
