/**
 * @file libs.h
 * @brief Header file for the libs.c file
 */

#include <stdint.h>

// Avoid duplication in code
#ifndef _LIBS_H_
#define _LIBS_H_

    // DEFINITION OF PINS TO BINARY READ
    #define READ_PINS 0x07F00000
    
    #define BUTTON_PIN  27
    
    // DEFINITION OF THE PLAYER PINS
    #define PLAYERS_PIN 28

    // DEFINITION OF THE LEDS
    #define LEDS_PIN 0x000FFFFC

    // Initialization of the bitmask for the binary read
    extern uint16_t bitmask;
    extern volatile uint8_t position;


    // definition of the variable to store the current player
    extern volatile bool g_state_player;



    // Definitions and prototypes
    void init_read_gpio (void );
    void init_leds (void );
    void set_led (uint8_t position, bool player);
    bool check_bitmask (uint16_t bitmask, uint8_t position);
    int8_t read_binary_input (void );
    void button_isr (uint gpio, uint32_t events);
    void change_player (bool player);


    // to do:

    // rutina para verificar si hay tres en raya
    // - verificar si hay tres en ray

    // rutina para verificar si hay empate
    // - verificar si hay empate

    // Rutina para apagar los leds

    // rutina para cuando gana jugador 0
    // - patron 1
    // - limpiar la mascara
    // - apagar leds

    // rutina para cuando gana jugador 1
    // - patron 2
    // - limpiar la mascara
    // - apagar leds

    // rutina para cuando se empata
    // - patron 3
    // - limpiar la mascara
    // - apagar leds

    // rutina para indicar un error
    // - patron 4 (que se enciendan de manera intermitente los leds por medio segundo)





#endif