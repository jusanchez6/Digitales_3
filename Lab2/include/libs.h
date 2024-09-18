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
    #define LEDS_PIN 0x001FFFFC // 0000 0010 0001 1111 1111 1111 1111 1100

    #define LEDS_PIN_PLAYER_0 0x000AAAA8  // 1010 1010 1010 1010 1000 (en binario)
    #define LEDS_PIN_PLAYER_1 0x00055554  // 0101 0101 0101 0101 0100 (en binario)
    #define INNER_LED 25 //LED interno

    #define striped_pattern   0xFFF77777
    #define a_delay 500

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
    void process_game (void);
    void process_time(uint8_t*);
    void choose_player(void);

    // to do:
    //animaciones

#endif