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
#include "globals.h"  // Incluir el archivo de cabecera



#define PWM_PIN2 15

volatile uint8_t update_display_flag = 0;  // Definición de la bandera
volatile uint64_t g_duty_cycle = 0; // Definición del ciclo de trabajo

int main() {
    stdio_init_all();
    
    init_pwm_detection();
    init_7_seg();
    
    while (1){
        __wfi();
        uint8_t en = 0;

        // Verifica si se necesita actualizar el display
        if (update_display_flag) {
            
            write_decimals(g_duty_cycle, &en);  // Escribe el valor en el display
            update_display_flag = 0;  // Resetea el flag
        }
    }
   
}
