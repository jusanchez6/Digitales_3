/**
 * @file 7_seg.h
 * @brief Archivo de cabecera de las funciones de los 7 segmentos.
 * 
 * Archivo de cabecera de las funciones de la libreria.
 * 
 * @authors María Del Mar Arbeláez
 *          Julián Mauricio Sánchez
 * 
 * @date 2024-10-12
 */

#ifndef _7_SEG_H_
    #define _7_SEG_H_

    //Standard Libraries
    #include <stdio.h>
    #include <stdint.h>
    #include <stdbool.h>

    //Pico Libraries
    #include "pico/stdlib.h"

    #define START_PIN 2
    #define SEGMENTS_MASK 0xFF<<START_PIN
    #define EN_1 12
    #define EN_2 11
    #define EN_3 10
    
    void init_7_seg(void);
    static inline void write_value(uint8_t value, bool dp);
    void write_decimals(uint16_t value);

#endif
