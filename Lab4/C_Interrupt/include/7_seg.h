/**
 * @file 7_seg.h
 * @brief Archivo de cabecera de las funciones de los 7 segmentos.
 * 
 * Archivo de cabecera de las funciones de la libreria.
 * 
 * @authors María Del Mar Arbeláez
 *          Julián Mauricio Sánchez
 * 
 * @date 2024-10-15
 */

#include <stdio.h>

#ifndef __7_SEG_H__
    #define __7_SEG_H__
    
    #define START_PIN 2
    #define SEGMENTS_MASK 0x7F << START_PIN
    #define EN_1 11
    #define EN_2 10
    #define EN_3 9

    void init_7_seg();
    void display_number(uint8_t number);
    void write_decimals(uint8_t value, uint8_t* run);

#endif // __7_SEG_H__