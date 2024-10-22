/**
 * @file globals.h
 * 
 * @brief Definición de variables globales
 * 
 * Este archivo contiene la definición de las variables globales que se utilizan en el proyecto.
 * 
 * @authors María Del Mar Arbeláez
 *         Julián Mauricio Sánchez
 * 
 * @date 2024-10-21
 * 
 */

#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>

/** @brief Variable que almacena el ciclo de trabajo de la señal.*/
extern volatile uint64_t g_duty_cycle;

/** @brief Variable que almacena el estado de multiplexacion del display.*/
extern volatile uint8_t g_run;

/** @brief Variable que almacena el tiempo actual.*/
volatile uint64_t g_current_time;

/** @brief Variable que almacena el tiempo del último flanco de subida.*/
volatile uint64_t g_last_edge_time;

/** @brief Variable que almacena el periodo de la señal.*/
volatile uint64_t g_period;

/** @brief Variable que almacena la frecuencia de la señal.*/
volatile uint64_t g_frequency;

/** @brief Variable que almacena el tiempo de inicio del pulso.*/
volatile uint64_t pulse_time_start;

#endif // GLOBALS_H