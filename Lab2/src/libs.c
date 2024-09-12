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

// Global variables
uint16_t bitmask = 0;
volatile uint8_t position = -1;
volatile bool g_state_player = 0;
volatile uint16_t g_state_leds_0 = 0;
volatile uint16_t g_state_leds_1 = 0;
volatile bool button_pressed = false;

/**
 * @brief This function initializes the GPIOs.
 */
void init_read_gpio(void)
{
    gpio_init_mask(READ_PINS);
    gpio_init(BUTTON_PIN);
    gpio_set_dir_in_masked(READ_PINS);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);

    // Set pull down resistors
    gpio_pull_down(21);
    gpio_pull_down(22);
    gpio_pull_down(26);
    gpio_pull_down(27);
    gpio_pull_down(BUTTON_PIN);
}

/**
 * @brief This function initializes the LEDs.
 */
void init_leds(void)
{
    gpio_init_mask(LEDS_PIN_PLAYER_0);
    gpio_set_dir_out_masked(LEDS_PIN_PLAYER_0);

    gpio_init_mask(LEDS_PIN_PLAYER_1);
    gpio_set_dir_out_masked(LEDS_PIN_PLAYER_1);

}

/**
 * @brief Checks if a specific position is already selected.
 */
bool check_bitmask(uint16_t bitmask, uint8_t position)
{
    return bitmask & (1 << position);
}

/**
 * @brief Reads binary input from the GPIOs.
 */
int8_t read_binary_input(void)
{
    position = 0;
    position |= gpio_get(21) << 0;
    position |= gpio_get(22) << 1;
    position |= gpio_get(26) << 2;
    position |= gpio_get(27) << 3;
    return position;
}

/**
 * @brief Changes the current player.
 */
void change_player(void)
{
    g_state_player = !g_state_player;   
    gpio_put(PLAYERS_PIN, !gpio_get(PLAYERS_PIN));
}

/**
 * @brief Sets the LED for the given position and player.
 */
void set_led(uint8_t position, bool player)
{
    printf("Setting LED %d for player %d \n", position, player);
    if (!player)
    {
        // Set the LED for player 0
        gpio_put_masked(LEDS_PIN, gpio_get_all() | (1 << (position * 2)));

        // Update the state of the LEDs for player 0
        g_state_leds_0 |= (1 << (position - 1));
    }
    else
    {
        // Set the LED for player 1
        gpio_put_masked(LEDS_PIN, gpio_get_all() | (1 << ((position * 2) + 1)));

        // Update the state of the LEDs for player 1
        g_state_leds_1 |= (1 << (position - 1));
    }

    sleep_ms(1000);  // Esperar un segundo para el feedback
    printf("State LEDs 0: %x \n", g_state_leds_0);
    printf("State LEDs 1: %x \n", g_state_leds_1);
}

/**
 * @brief Checks specific winning patterns for the player.
 */
void check_winner(void)
{
    // Combinaciones ganadoras en un tablero de 3x3
    uint16_t winning_patterns[8] = {
        0x07,  // 000 000 111 - fila 1
        0x38,  // 000 111 000 - fila 2
        0x1C0, // 111 000 000 - fila 3
        0x49,  // 001 001 001 - columna 1
        0x92,  // 010 010 010 - columna 2
        0x124, // 100 100 100 - columna 3
        0x54,  // 100 010 001 - diagonal 1
        0x111  // 001 010 100 - diagonal 2
    };

    // Revisar si el jugador 0 tiene alguna combinación ganadora
    for (int i = 0; i < 8; i++)
    {
        if ((g_state_leds_0 & winning_patterns[i]) == winning_patterns[i])
        {
            printf("Player 0 wins!\n");
            sleep_ms(1000);  // Esperar un segundo antes de apagar todos los LEDs
            reset_game();
            return;
        }
    }

    // Revisar si el jugador 1 tiene alguna combinación ganadora
    for (int i = 0; i < 8; i++)
    {
        if ((g_state_leds_1 & winning_patterns[i]) == winning_patterns[i])
        {
            printf("Player 1 wins!\n");
            sleep_ms(1000);  // Esperar un segundo antes de apagar todos los LEDs
            reset_game();
            return;
        }
    }

    // Revisar si hay un empate
    if ((g_state_leds_0 | g_state_leds_1) == 0x1ff)  // Todas las posiciones ocupadas
    {
        printf("It's a tie!\n");
        sleep_ms(1000);  // Esperar un segundo antes de apagar todos los LEDs
        gpio_put_masked(LEDS_PIN, 0);  // Apagar todos los LEDs
    }
}

/**
 * @brief Resets the game after a win or tie.
 */
void reset_game(void)
{
    bitmask = 0;
    g_state_leds_0 = 0;
    g_state_leds_1 = 0;
    gpio_put_masked(LEDS_PIN, 0); // Turn off all LEDs
    printf("Game reset!\n");
}

void proccess_game (void) {
    if (position >= 1 && position <= 9)
    {
        if (check_bitmask(bitmask, position))
        {
            printf("Position %d already selected \n", position);
        }
        else
        {
            bitmask |= (1 << position);
            printf("Position %d selected \n", position);
            set_led(position, g_state_player);
            check_winner();
            change_player();
        }
    }
    else
    {
        printf("Invalid input, try again \n");
    }
    position = -1; // Reset position after handling
}

/**
 * @brief This is the interrupt service routine for the button.
 */
void button_isr(uint gpio, uint32_t events)
{
    button_pressed = true;
    
}