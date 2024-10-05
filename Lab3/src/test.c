/**
 * @file test.c
 * @brief Archivo que contiene la función test.
 *
 * Archivo que contiene la función main del programa.
 * 
 * @authors Maria Del Mar Arbelaez Sandoval
 *         Julian Mauricio Sanchez Ceballos
 * 
 * @date 2024-09-29
 * 
 * 
 */

// Standard libraries
#include <stdio.h>
#include "pico/stdlib.h"
#include "mat.h"

/**
 * @brief Main program.
 *
 * Función principal del programa, desde aqui se llama los metodos
 * que gestionan todo el juego.
 */
#define JUANITA 1

int main() {
	// STDIO initialization
    stdio_init_all();

    // initialize the gpios
    init_mat();

    //reading=0;
    volatile uint8_t value;

    while (JUANITA) {
        while(!read_mat(&value)); //bloquear hasta que esté lista la lectura
        printf("Value read is %c\n",value);
    }
    return 0;    
}