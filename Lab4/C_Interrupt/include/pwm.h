/**
 * @file pwm.h
 * @brief Archivos de cabezera del archivo pwm.c
 * 
 * Este archivo contiene las definiciones de las funciones de la libreria pwm.c
 * 
 * @authors María Del Mar Arbeláez
 *         Julián Mauricio Sánchez
 * 
 * @date 2024-10-21
 * 
 * @version 1.0
 */

#include <stdint.h>

// Avoid duplication in code
#ifndef _PWM_H_
#define _PWM_H_

// Definitions and prototypes
#define PWM_GPIO_CHA        16
#define PWM_CHA             0
#define PWM_DIV_INTEGER     128
#define PWM_DIV_FRAC        0
#define PWM_TOP_VALUE       4095
#define PWM_DUTY_ZERO       0

void project_pwm_init();
void project_pwm_set_chan_level(uint);

#endif