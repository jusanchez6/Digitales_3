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

#define JUANITA 1


/**
 * @brief Main program.
 *
 * This function initializes the MCU and does an infinite cycle.
 */
int main() {
	// STDIO initialization
    stdio_init_all();

    // initialize the gpios
    init_read_gpio();
    init_leds();

    // set the irq
    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &button_isr);
    position = -1;
    
    gpio_init(19);
    gpio_init(17);

    gpio_set_dir(19, GPIO_OUT);
    gpio_set_dir(17, GPIO_OUT);
    
    // que solo lea el valor de la posicion si es 255
    // y no haga nada mas hasta que se active el boton

    // que se agregue la posicion en la interrupcion
    // asi como la verificacion de si ya se selecciono la posicion
    // y el cambio de la variable de posicion a -1

	// Infinite loop. This function shouldn't finish or return
    while (JUANITA) {
        

        if (button_pressed) {
            position = read_binary_input();
            proccess_game();
            button_pressed = false;
        } 
        sleep_ms(500);
    }
    
    return 0;    
}