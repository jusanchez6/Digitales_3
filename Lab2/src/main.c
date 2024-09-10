/**
 * @file main.c
 * @brief This is a brief description of the main C file.
 *
 * Detailed description of the main C file.
 */

// Standard libraries
#include <stdio.h>
#include "pico/stdlib.h"
#include "libs.h"




/**
 * @brief Main program.
 *
 * This function initializes the MCU and does an infinite cycle.
 */
int main() {
	// STDIO initialization
    stdio_init_all();

    // inicializar los pines
    init_gpio();

    


	// Infinite loop. This function shouldn't finish or return
    while (1) {
        int8_t value = read_binary_input();

    }
    
    return 0;    
}