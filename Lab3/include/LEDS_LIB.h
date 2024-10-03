/**
 * @file LEDS_LIB.h
 * @brief Archivo de cabecera de las funciones de la libreria que controla
 * los leds
 * 
 * Archivo de cabecera de las funciones de la libreria que controla
 * los leds
 * 
 * @authors Maria Del Mar Arbelaez
 *          Julian Mauricio Sanchez
 * 
 * @date 2024-10-2
 */

#include <stdint.h>

// Avoid duplication in code
#ifndef __LED_LIB_H_
    #define __LED_LIB_H_

    #define LEDS_PINS 0x07 << 9         //0x0000 1110 0000 0000 
    #define LED_RED 0x01 << 9           //0x0000 0010 0000 0000
    #define LED_GREEN 0x01 << 10        //0x0000 0100 0000 0000
    #define LED_YELLOW 0x01 << 11       //0x0000 1000 0000 0000
    


    void init_leds(void);
    void change_led(uint8_t c);
    


#endif