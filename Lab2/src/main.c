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

    // initialize the gpios
    init_gpio();

    // set the irq
    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &button_isr);

    


	// Infinite loop. This function shouldn't finish or return
    while (1) {
        if (position == -1) {
            position = read_binary_input();
            printf("Read position %d \n", position);
        } else {
            // verify the number in the bitmask variable
            if (position >= 1 && position <= 9) {
                if (check_bitmask(bitmask, position)) {
                    printf("position %d already selected \n");
                } else {
                    bitmask |= (1 << position);
                }
            } else {
                printf("invalid input, try again \n");
            }

            // reset the variable for the next lecture

            position = -1;
            
        }

        sleep_ms(100);

    }
    
    return 0;    
}