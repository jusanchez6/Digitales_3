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

#include <stdint.h>

#ifndef _7_SEG_H_
    #define _7_SEG_H_

    #define START_PIN 2
    #define SEGMENTS_MASK 0x7F<<START_PIN
    #define EN_1 11
    #define EN_2 10
    #define EN_3 9

    void init_7_seg(void);
    void write_value(uint8_t value);
    void write_decimals(uint8_t value,uint8_t*run);

#endif
