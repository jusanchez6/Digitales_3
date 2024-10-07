/**
 * @file fsm.c
 * 
 * @brief Implementación de la máquina de estados para el control de acceso.
 * 
 * Este archivo contiene la implementación de la lógica de la máquina de 
 * estados que gestiona la entrada de ID y contraseña, así como su 
 * verificación.
 * 
 * @authors Maria Del Mar Arbelaez
 *          Julian Mauricio Sanchez
 * 
 * @date 2024-10-06
 */

// Standard libraries
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

// Pico libraries
#include "mat.h"
#include "LEDS_LIB.h"
#include "access.h"
#include "fsm.h"

// Definición de un tipo para la función de estado
typedef void (*state_func_t)(void);

// Definimos las funciones de cada estado
static void state_waiting(void);
static void state_entering_credentials(void);
static void state_entering_pass(void);
static void state_verifying(void);


// Variable que apunta a la función actual del estado
static state_func_t current_state;

// Buffers para ID y Contraseña
static uint8_t user_id[7];
static uint8_t user_pass[5];
static uint8_t id_index = 0, pass_index = 0;

// Inicialización de la FSM
void fsm_init(void) {
    current_state = state_waiting; // Estado inicial
    id_index = 0; // Resetear índices
    pass_index = 0;

}

// Ejecución de la FSM
void fsm_run(void) {
    current_state(); // Llama a la función del estado actual
}

// Estado "waiting": espera que se presione una tecla para iniciar
static void state_waiting(void) {
    uint8_t key;
    control_yellow_led(1);              // LED amarillo indicando que está listo para recibir el ID
    
    while (!read_mat(&key));
    
    if (key == '*') {
        printf("Ingresa ID: ");
        current_state = state_entering_credentials;
        control_yellow_led(0);          // Apaga el LED amarillo, indica inicio de ingreso de ID

        id_index = 0;
        pass_index = 0;
    }
    
}

// Estado "entering_id": el usuario ingresa el ID
static void state_entering_credentials(void) {
    uint8_t key;
    control_yellow_led(0);
    while (!read_mat(&key)); 

    if (id_index < 6) { // Asegúrate de que no se exceda el tamaño del buffer
        //imprimir el valor de la tecla ingresado
        user_id[id_index++] = key;
        printf("%c", key);
            

        if (id_index == 6) {
            user_id[++id_index] = '\0'; // Asegúrate de que la cadena esté terminada
            // Se ha ingresado el ID completo                
            printf("\nIngresa Contraseña: ");
            current_state = state_entering_pass; // Cambia al siguiente estado               
        }   
    }
}


// Estado "entering_pass": el usuario ingresa la contraseña
static void state_entering_pass(void) {
    uint8_t key;
    control_yellow_led(2); // LED amarillo titila indicando ingreso de contraseña

    while (!read_mat(&key)); 
    if (pass_index < 4) { // Asegúrate de que no se exceda el tamaño del buffer
        //imprimir el valor de la tecla ingresado
        
        user_pass[pass_index++] = key;
        printf("%c", key);

        if (pass_index == 4) {
            user_pass[++pass_index] = '\0'; // Asegúrate de que la cadena esté terminada
            // Se ha ingresado la contraseña completa
            current_state = state_verifying;
        }
    }
    
}

// Estado "verifying": verifica las credenciales del usuario
static void state_verifying(void) {
    control_yellow_led(0); // Apaga el LED amarillo
    if (access_control(user_id, user_pass)) {
        // Acceso concedido
        printf("Acceso concedido\n");
        signal_success(2000);


    } else {
        // Acceso denegado
        printf("Acceso denegado\n");
        signal_error(2000);

    }
    
    
    turn_off_leds();
    current_state = state_waiting;

}
