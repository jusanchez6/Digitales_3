/**
 * @file main.c
 * @brief Main file for the project
 * 
 * This file contains the main function for the project.
 * 
 * @authors María Del Mar Arbeláez
 *          Julián Mauricio Sánchez
 * 
 * @date 2024-10-15
 */

#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/clocks.h"
#include "hardware/sync.h"
#include "pico/platform.h"

#include "detect_pwm.h"
#include "pwm.h"
#include "7_seg.h"
#include "globals.h" 


// Definición de variables globales

volatile uint64_t g_current_time = 0;
volatile uint64_t g_last_edge_time = 0;
volatile uint64_t g_period = 0;
volatile uint64_t g_frequency = 0;
volatile uint64_t pulse_time_start = 0;
volatile uint64_t g_duty_cycle = 0; 
volatile uint8_t g_run = 0;  


/**
 * @brief Main function
 * 
 * Esta función inicializa el sistema y entra en un ciclo infinito.
 * 
 * @param void
 * 
 * @return void
 */
int main() {

    stdio_init_all();       // Inicializa la UART
    sleep_ms(5000);         // Espera 5 segundos
    
     
    init_pwm_detection();   // Inicializa la detección de la señal PWM
    init_7_seg();           // Inicializa los 7 segmentos
    
    while (1){
        __wfi();    // Espera a una interrupción
    }
   
}
