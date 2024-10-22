/**
 * @file detect_pwm.h
 * @brief Archivo de cabecera par las funciones del archivo detect_pwm.c
 * 
 * Archivo de cabecera de las funciones de la libreria detect_pwm.
 * 
 * @authors María Del Mar Arbeláez
 *         Julián Mauricio Sánchez
 * 
 * @date 2024-10-15
 * 
 * @version 1.0
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

    /** @brief Función que se llama cuando se detecta un flanco de subida en la señal PWM
     * 
     * Esta función se llama cuando se detecta un flanco de subida o de bajada en la señal PWM.
     * se encarga de calcular el ciclo de trabajo de la señal. Y actualizar el display.
     * 
     * @param gpio Pin en el que se detectó el flanco de subida
     * @param events Eventos que ocurrieron en el pin
     * 
     * @return void
    */
    void pwm_detect_callback(unsigned int gpio, uint32_t events);
    
    /** @brief Inicializa la detección de la señal PWM
     * 
     * Esta función inicializa la detección de la señal PWM, 
     * Asignando los gpios como entrada, configurandolo como resistencia pull-down y
     * Activando la ISR.
     * 
     * @param void
     * 
     * @return void
    */
    void init_pwm_detection();


#endif // __DETECT_PWM_H__