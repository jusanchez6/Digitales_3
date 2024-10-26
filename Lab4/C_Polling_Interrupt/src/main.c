/**
 * @file main.c
 * @brief This is a brief description of the main C file.
 *
 * Detailed description of the main C file.
 */

// Standard libraries
#include <stdio.h>
#include "pico/stdlib.h"

// Pico libraries
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/clocks.h"
#include "hardware/sync.h"
#include "pico/platform.h"

// User libraries
#include "../include/globals.h"

volatile uint64_t g_duty_cycle;
volatile uint64_t g_frequency;
volatile uint64_t g_last_edge_time;
volatile uint64_t pulse_time_start;
volatile uint64_t g_period;

flags_t g_flags;
/**
 * @brief Main program.
 *
 * This function initializes the MCU and does an infinite cycle.
 */
int main() {
	// STDIO initialization
    stdio_init_all();
	
	// Write your initialization code here
	
	// Infinite loop. This function shouldn't finish or return
    while (1) {
        // Espera a que se detecte un flanco de subida o bajada
        __wfi();

        // Si se detecta un flanco de subida calculo del periodo y la frecuencia
        if (g_flags.edge_flag && g_last_edge_time != 0){
            // Calcula el periodo
            g_period = time_us_64() - g_last_edge_time;
            g_frequency = 1000000 / (uint32_t)g_period;
            // Resetea la bandera de flanco de subida
            g_flags.edge_flag = false;
        }

        // Si se detecta un flanco de bajada calculo del ciclo de trabajo
        if (g_flags.fall_flag && g_period != 0){
            // Calcula el tiempo de inicio del pulso
            pulse_time_start = time_us_64();
            // Calcula el tiempo de duración del pulso
            uint64_t pulse = pulse_time_start - g_last_edge_time;
            // Calcula el ciclo de trabajo
            g_duty_cycle = (pulse  * g_frequency) / 10000;
            // Resetea la bandera de flanco de bajada
            g_flags.fall_flag = false;

        }

        // Mostrar los valores en la consola
        printf("Periodo: %d us\n", (uint32_t)g_period);
        printf("Frecuencia: %d Hz\n", (uint32_t)g_frequency);
        printf("Ciclo de trabajo: %d %%\n", (uint32_t)g_duty_cycle);


    }
	
    return 0;
}