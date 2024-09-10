/**
 * @file libs.c
 */

// Standard libraries
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "pico/stdlib.h"


// Libs header file
#include "libs.h"

uint16_t bitmask = 0;
uint8_t position = 0;

/**
 * @brief This function initializes the GPIOs.
 * 
 * This function initializes the GPIOs that are going to be used.
 */
void init_gpio (void ) {
    // Initialize the GPIOs
    gpio_init(PIN_B_1);
    gpio_init(PIN_B_2);
    gpio_init(PIN_B_4);
    gpio_init(PIN_B_8);

    // Set the GPIOs as inputs
    gpio_set_dir(PIN_B_1, GPIO_IN);
    gpio_set_dir(PIN_B_2, GPIO_IN);
    gpio_set_dir(PIN_B_4, GPIO_IN);
    gpio_set_dir(PIN_B_8, GPIO_IN);

    // Set pull down resistors
    gpio_pull_down(PIN_B_1);
    gpio_pull_down(PIN_B_2);
    gpio_pull_down(PIN_B_4);
    gpio_pull_down(PIN_B_8);
}


/**
 * @brief This function checks the bitmask.
 * 
 * This function checks the bitmask to see if a position is already selected.
 * 
 * @param bitmask The bitmask to check
 * @param position The position to check
 * 
 * @return True if the position is already selected, false otherwise
 *
 */
bool check_bitmask (uint16_t bitmask, uint8_t position) {
    return bitmask & (1 << position);
}


/**
 * @brief This function reads the binary input.
 * 
 * This function reads the binary input from the GPIOs.
 * 
 * @param void
 * 
 * @return The value read from the GPIO
 */
int8_t read_binary_input (void ) {
    // Read the GPIO
    
    

    while (true) {
        position = 0;

        position |= gpio_get(PIN_B_1) << 0;
        position |= gpio_get(PIN_B_2) << 1;
        position |= gpio_get(PIN_B_4) << 2;
        position |= gpio_get(PIN_B_8) << 3;

        // Check if the position is valid
        printf("pos %d \n", position);

        if (position >= 1 && position <= 9) {

            if (check_bitmask(bitmask, position)) {
                printf("Position %d already selected\n", position);
            }
            else {
                bitmask |= (1 << position);
                printf("Position %d selected\n", position);
            }

        }
        else {
            printf("Invalid position\n");
        }
        sleep_ms(700);
    }

    return position;
}

/**
 * @brief This is the interrupt service routine for the button.
 * 
 * This function is called when the button is pressed.
 * 
 * @param gpio The GPIO number that triggered the interrupt
 * @param events The interrupt events
 */
void button_isr(uint gpio, uint32_t events) {
    // Solo procesar si el botón se presiona (evento de caída de señal)
    if (gpio == BUTTON_PIN && events & GPIO_IRQ_EDGE_FALL) {
        // Verificar si hay una posición válida que leer
        if (position != -1) {
            // Esperar un pequeño tiempo para estabilizar el botón
            sleep_ms(50);
            // Confirmar y procesar la posición leída
            printf("Button pressed to confirm position %d\n", position);
        }
    }
}