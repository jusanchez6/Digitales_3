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
    
    // que solo lea el valor de la posicion si es 255
    // y no haga nada mas hasta que se active el boton

    // que se agregue la posicion en la interrupcion
    // asi como la verificacion de si ya se selecciono la posicion
    // y el cambio de la variable de posicion a -1

	// Infinite loop. This function shouldn't finish or return
    uint8_t moment=1;
    reset_game();
    while (JUANITA) {
        if (button_pressed) {
            process_time(&moment);
            //printf("RISE:%d \n",moment);
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