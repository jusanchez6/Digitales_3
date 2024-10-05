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

    #define MAT_PINS 0xFF<<2       //0011 1111 1100
    #define MAT_WRITE_PINS 0xF<<2  //0000 0011 1100
    #define MAT_READ_PINS 0xF<<6   //0011 1100 0000

    /**
     * @brief Inicializa el teclado matricial y su callback
     * 
     * Inicializa el teclado matricial y su callback
     * 
     * @return void
     */
    void init_mat(void);

    
    /**
     * @brief Cambia la configuración de entrada y salida del teclado matricial
     * 
     * Cambia la configuración de entrada y salida del teclado matricial
     * 
     * @param change booleano para decidir entre la configuración inicial de la matriz (false) o la cambiada (true).
     * 
     * @return void
     */
    void set_dirs_mat(bool);

    /**
     * @brief Lectura del teclado matricial
     * 
     * Funcion de lectura del teclado matricial con el debounce integrado por Software.
     * 
     * @param value 
     * 
     * @return false si no ha terminado la lectura, true si ya terminó.
     */
    bool read_mat(volatile uint8_t* value);

#endif
