/**
 * @file main.c
 * @brief Archivo que contiene la función main.
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
#include "libs.h"

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
    repeating_timer_t timer_mat;
    if(!add_repeating_timer_ms(5, repeating_timer_callback ,NULL, &timer_mat)){printf("timers don't work :(");}
    reading=false;

    printf("Done initialization");
    volatile uint8_t c=0;
    while (JUANITA) {
        //vamos a tirar irqs y polling yay (he dicho)
        if(reading){read_mat(c);}
        if(timer_mat.user_data){ 
            if(!reading) {change_mat(&c);} //function for changing thingy
        } 
        //sleep_ms(30);
    }
    return 0;    
}