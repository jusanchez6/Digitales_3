/**
 * @file main.c
 * 
 * @brief Archivo principal del sistema de control de acceso con teclado matricial.
 * 
 * Este archivo inicializa los periféricos y ejecuta la máquina de estados para manejar el flujo de control de acceso.
 * 
 * @authors Maria Del Mar Arbelaez
 *         Julian Mauricio Sanchez
 * 
 * @date 2024-10-6
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "mat.h"            	// Teclado matricial
#include "LEDS_LIB.h"           // Control de LEDs
#include "access.h"  			// Control de acceso y usuarios
#include "fsm.h"           		// Máquina de estados

int main(void) {
    // Inicialización de la entrada/salida estándar
    stdio_init_all();   

    // Inicializar periféricos y recursos
    init_mat();         // Inicializar el teclado matricial
    init_leds();        // Inicializar los LEDs
    init_users();       // Inicializar la base de datos de usuarios

    // Inicializar la máquina de estados
    fsm_init();     

    // Bucle principal
    while (true) {
        fsm_run();      // Ejecutar la máquina de estados en cada iteración
    }

    return 0;           // Nunca se llegará aquí, el bucle es infinito
}