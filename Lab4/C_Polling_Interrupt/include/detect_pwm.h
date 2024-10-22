/**
 * @file detect_pwm.h
 * 
 * @brief Archivo de cabecera para las funciones del archivo detect_pwm.c
 * 
 * Archivo de cabecera de las funciones de la libreria detect_pwm.c
 * 
 * @authors Maria Del Mar Arbeláez
 *         Julian Mauricio Sánchez
 * 
 * @date 2024-10-21
 * 
 * @see detect_pwm.c
 * 
 */

// Standar C Libraries
#include <stdint.h>

// picoSDK Libraries
#include "pico/stdlib.h"

#ifndef DETECT_PWM_H
    #define DETECT_PWM_H    

    #define PWM_PIN 12

    /**
     * @brief Función que detecta los flancos de subida y bajada de una señal PWM
     * 
     * Funcion que registra los tiempos, de flanco de subida y de bajada, ademas
     * de activar una bandera para indicar que se detecto un flanco.
     * 
     * @param gpio Pin de entrada de la señal PWM
     * @param events Eventos de la señal
     */
    void detect_pwm_callback(unsigned int gpio, uint32_t events);

    /**
     * @brief Función que inicializa la detección de señales PWM
     * 
     * Funcion que inicializa el pin de entrada de la señal PWM y activa las interrupciones
     * para detectar los flancos de subida y bajada.
     * 
     */
    void detect_pwm_init(void );

#endif