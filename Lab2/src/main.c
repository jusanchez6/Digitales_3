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
    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL|GPIO_IRQ_EDGE_RISE, true, &button_isr);
    position = -1;
    // Que no haga nada hasta que se active el boton

    //initializing game :)
    uint8_t moment=1;
    reset_game();
    while (JUANITA) {
        if (button_pressed) {
            process_time(&moment);
            if(moment==1){
                position = read_binary_input();
                process_game();
            }
            button_pressed = false;
            sleep_ms(50);
        }
    }
    return 0;    
}