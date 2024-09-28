/**
 * @file libs.h
 * @brief Archivo de cabecera de las funciones de la libreria.
 * 
 * Archivo de cabecera de las funciones de la libreria.
 * 
 * @authors Maria Del Mar Arbelaez
 *         Julian Mauricio Sanchez
 * 
 * @date 2024-09-18
 */

#include <stdint.h>

// Avoid duplication in code
#ifndef _LIBS_H_
    #define _LIBS_H_

    #define MAT_PINS 0xFF<<2 //0x0011 1111 1100
    #define MAT_WRITE_PINS 0xF<<2 //0x0011 1100
    #define MAT_READ_PINS 0xF<<6 //0x0011 1100 0000

    extern volatile bool reading;
    void init_mat(void);
    void init_callback(void);
    void mat_callback(uint gpio, uint32_t events);
    void change_mat(volatile uint8_t* cnt);  
    bool repeating_timer_callback(repeating_timer_t *t);
    void read_mat(uint8_t c);

#endif