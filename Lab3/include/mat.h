/**
 * @file mat.h
 * @brief Archivo de cabecera de las funciones del teclado matricial.
 * 
 * Archivo de cabecera de las funciones de la libreria.
 * 
 * @authors Maria Del Mar Arbelaez
 *         Julian Mauricio Sanchez
 * 
 * @date 2024-10-02
 */

#include <stdint.h>

#ifndef _MAT_H_
    #define _MAT_H_

    #define MAT_PINS 0xFF<<2 //0x0011 1111 1100
    #define MAT_WRITE_PINS 0xF<<2 //0x0011 1100
    #define MAT_READ_PINS 0xF<<6 //0x0011 1100 0000

    extern volatile uint8_t reading;
    extern volatile uint8_t gpio_pressed;
    void init_mat(void);
    void set_dirs_mat(bool);
    void init_callback(void);
    void mat_callback(uint gpio, uint32_t events);
    void change_mat(volatile uint8_t* cnt);
    bool repeating_timer_callback(repeating_timer_t *t);
    bool read_mat(uint8_t c);

#endif
