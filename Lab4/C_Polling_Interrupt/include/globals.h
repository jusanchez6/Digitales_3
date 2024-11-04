/**
 * @file ./C_Polling_Interrupt/include/globals.h
 * 
 * @brief Global variables and constants
 * 
 * Este archivo contiene las variables y constantes globales que se utilizan en el programa.
 * 
 * @authors Maria Del Mar Arbeláez
 *          Julian Mauricio Sánchez
 * 
 * @date 2024-10-21
 */ 

#ifndef GLOBALS_H
    #define GLOBALS_H

#include <stdint.h>
#include <stdbool.h>




/** @brief Estructura, que almacena las banderas*/
typedef struct {
    bool edge_flag:         1;
    bool fall_flag:         1;
} flags_t;


/** @brief Variable que almacena las banderas.*/
extern flags_t g_flags;

/** @brief Variable que almacena el tiempo de flanco de subida*/
extern volatile uint64_t g_last_rise_time;

/** @brief Variable que almacena el tiempo de flanco de bajada*/
extern volatile uint64_t g_last_fall_time;

/** @brief Variable que almacena el ciclo de trabajo de la señal.*/
extern volatile uint64_t g_duty_cycle;

/** @brief Variable que almacena el tiempo del pulso*/
extern volatile uint64_t g_pulse_time;

/** @brief Variable que almacena el tiempo de inicio del pulso*/
extern volatile uint64_t g_pulse_start;

/** @brief Variable que almacena el periodo de la señal.*/
extern volatile uint64_t g_period;

/** @brief Variable que almacena la frecuencia de la señal.*/
extern volatile uint64_t g_frequency;

/** @brief Variable que almacena el tiempo de pulso de la señal.*/
extern volatile uint64_t g_pulse_time;


/** @brief Variable que almacena el estado de multiplexacion del display.*/
extern volatile uint8_t g_run;

#endif
