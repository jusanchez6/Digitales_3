/**
 * @file libs.h
 * @brief Header file for the libs.c file
 */

#include <stdint.h>

// Avoid duplication in code
#ifndef _LIBS_H_
#define _LIBS_H_

    // DEFINITION OF PINS TO BINARY READ
    #define PIN_B_1 20
    #define PIN_B_2 21
    #define PIN_B_4 22
    #define PIN_B_8 26
    #define BUTTON_PIN  27

    // Initialization of the bitmask for the binary read



    // Definitions and prototypes
    void init_gpio (void );
    bool check_bitmask (uint16_t bitmask, uint8_t position);
    int8_t read_binary_input (void );
    void button_isr (uint gpio, uint32_t events);


#endif