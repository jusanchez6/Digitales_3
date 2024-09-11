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


// Remove the redefinition of 'bitmask'
uint16_t bitmask = 0;
volatile uint8_t position = -1;

/**
 * @brief This is the variable to store the current player.
 *
 * This variable stores the current player.
 * 0: Player 1
 * 1: Player 2
 */
volatile bool g_state_player = 0;

/**
 * @brief This function initializes the GPIOs.
 *
 * This function initializes the GPIOs that are going to be used.
 */
void init_read_gpio(void)
{
    // Initialize the GPIOs

    gpio_init_mask(READ_PINS);
    gpio_init(BUTTON_PIN);

    // Set the direction of the GPIOs
    gpio_set_dir_in_masked(READ_PINS);

    gpio_set_dir(BUTTON_PIN, GPIO_IN);

    // Set pull down resistors
    gpio_pull_down(20);
    gpio_pull_down(21);
    gpio_pull_down(22);
    gpio_pull_down(23);
    gpio_pull_down(BUTTON_PIN);
}

/**
 * @brief This function initializes the LEDs.
 *
 * This function initializes the LEDs that are going to be used.
 */
void init_leds(void)
{
    // Initialize the GPIOs

    gpio_init_mask(LEDS_PIN);

    // Set the direction of the GPIOs
    gpio_set_dir_out_masked(LEDS_PIN);
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
bool check_bitmask(uint16_t bitmask, uint8_t position)
{
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
int8_t read_binary_input(void)
{
    // Read the GPIO

    position = 0;

    position |= gpio_get(20) << 0;
    position |= gpio_get(21) << 1;
    position |= gpio_get(22) << 2;
    position |= gpio_get(23) << 3;

    return position;
}

/**
 * @brief This function changes the player.
 *
 * This function changes the player.
 */
void change_player (bool player)
{
    player = !player;
    gpio_put(PLAYERS_PIN, player);
}


/**
 * @brief This function sets the LED.
 *
 * This function sets the LED.
 *
 * @param position The position of the LED to set
 */
void set_led(uint8_t position, bool player)
{
    // Set the LED
    if (player)
    {   
        // Set the LED for player 2 pos + 2
        gpio_put_masked(LEDS_PIN, (1 << (position * 2)));
    }
    else
    {
        gpio_put_masked(LEDS_PIN, (1 << ((position * 2) + 1)));
    }
}


/**
 * @brief This is the interrupt service routine for the button.
 *
 * This function is called when the button is pressed.
 *
 * @param gpio The GPIO number that triggered the interrupt
 * @param events The interrupt events
 */
void button_isr(uint gpio, uint32_t events)
{

    while (position =! 255)
    {
        if (position >= 1 && position <= 9)
        {
            if (check_bitmask(bitmask, position))
            {
                printf("position %d already selected \n");
                // rutina de error para indicar que la posición ya fue seleccionada
                position = -1;
                break;
            }
            else
            {
                bitmask |= (1 << position);
                printf("position %d selected \n", position);
                // encender el led indicado
                set_led(position, g_state_player);

                // verificar si se hizo tres en raya

                // verificar si se llenó el tablero
                     
                // cambiar el estado del jugador
                change_player(g_state_player);
            }
        }
        else
        {
            printf("invalid input, try again \n");
            break;
        }
    }
    position = -1;
}
