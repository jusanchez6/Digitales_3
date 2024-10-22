/**
 * @file globals.h
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

/** @brief Variable que almacena el ciclo de trabajo de la señal.*/
extern volatile uint64_t g_duty_cycle;

/** @brief Variable que almacena el estado de multiplexacion del display.*/
extern volatile uint8_t g_run;

/** @brief Variable que almacena el tiempo actual.*/
extern volatile uint64_t g_current_time;

/** @brief Variable que almacena el tiempo del último flanco de subida.*/
extern volatile uint64_t g_last_edge_time;

/** @brief Variable que almacena el periodo de la señal.*/
extern volatile uint64_t g_period;

/** @brief Variable que almacena la frecuencia de la señal.*/
extern volatile uint64_t g_frequency;

/** @brief Variable que almacena el tiempo de inicio del pulso.*/
extern volatile uint64_t pulse_time_start;

/** @brief Variable que almacena la bandera de cambio del ciclo de trabajo*/
extern volatile bool g_duty_cycle_flag;

/** @brief Variable que almacena la bandera de cambio de la frecuencia*/
extern volatile bool g_frecuency_flag;

/** @brief Variable que almacena la bandera de deteccion de flancos*/
extern volatile bool g_edge_flag;

#endif
