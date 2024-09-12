/**
 * @file libs.h
 * @brief Header file for the libs.c file
 */

#include <stdint.h>

// Avoid duplication in code
#ifndef _LIBS_H_
    #define _LIBS_H_

    // DEFINITION OF PINS TO BINARY READ
    #define READ_PINS 0x0E300000 // 0000 1110 0011 0000 0000 0000 0000 0000(en binario)
    
    #define BUTTON_PIN  28
    
    // DEFINITION OF THE PLAYER PINS
    #define PLAYERS_PIN 20

    // DEFINITION OF THE LEDS
    #define LEDS_PIN 0x003FFFFC // 0000 0000 0000 1111 1111 1111 1111 1100

    #define LEDS_PIN_PLAYER_0 0x0000AAAA  // 1010 1010 1010 1010 (en binario)

    #define LEDS_PIN_PLAYER_1 0x00005555  // 0101 0101 0101 0101 (en binario)

    extern volatile uint8_t position;
    extern volatile bool g_state_player;
    extern volatile uint16_t g_state_leds_0;
    extern volatile uint16_t g_state_leds_1;
    extern volatile bool button_pressed;



    // Definitions and prototypes
    void init_read_gpio (void );
    void init_leds (void );
    void set_led (uint8_t position, bool player);
    bool check_bitmask (uint16_t bitmask, uint8_t position);
    int8_t read_binary_input (void );
    void button_isr (uint gpio, uint32_t events);
    void change_player (void);
    void reset_game (void);
    void check_winner (void);
    void proccess_game (void);


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