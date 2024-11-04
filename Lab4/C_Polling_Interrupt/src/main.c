/**
 * @file ./C_Polling_Interrupt/src/main.c
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
#include "../include/detect_pwm.h"
#include "../include/7_seg.h"

// Global variables
volatile uint64_t g_last_rise_time;
volatile uint64_t g_last_fall_time;
volatile uint64_t g_pulse_start;
volatile uint64_t g_frequency;
volatile uint64_t g_period;
volatile uint64_t g_duty_cycle;
volatile uint64_t g_pulse_time;
volatile uint8_t g_run = 0;


flags_t g_flags;

/**
 * @brief Main program.
 *
 * This function initializes the MCU and does an infinite cycle.
 */
int main() {
	// STDIO initialization
    stdio_init_all();
    detect_pwm_init();
    init_7_seg();
	
	// Write your initialization code here
	
	// Infinite loop. This function shouldn't finish or return
    while (1) {
        // Espera a que se detecte un flanco de subida o bajada
        __wfi();

        // Si se detecta un flanco de subida calcula la frecuencia
        if (g_flags.edge_flag){
            g_period = g_last_rise_time - g_pulse_start;
            g_frequency = 1000000 / g_period;
            g_flags.edge_flag = false;
        }

        // Si se detecta un flanco de bajada calcula el ciclo de trabajo
        if (g_flags.fall_flag){
            g_pulse_time = g_last_fall_time - g_last_rise_time;
            g_duty_cycle = (g_pulse_time * 100) / g_period;
            g_flags.fall_flag = false;
        }


        // multiplexado de los displays
        write_decimals((uint8_t)g_duty_cycle, (uint8_t *)&g_run);
    }
	
    return 0;
}