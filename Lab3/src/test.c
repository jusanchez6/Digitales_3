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
    init_callback();
    //attach timer
    //repeating_timer_t timer_mat;
    //if(!add_repeating_timer_ms(5, repeating_timer_callback ,NULL, &timer_mat)){printf("timers don't work :(");}
    
    reading=0;
    volatile uint8_t c=0;
    bool done=false;

    while (JUANITA) {
        if(reading!=0){
            done=read_mat(c);}
        if (done){
            done=false;
        }
        //sleep_ms(3);
    }
    return 0;    
}