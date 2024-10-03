/**
 * @file State_machine.c
 * @brief Implementación de las funciones de la maquina de estados
 * 
 * Implementación de las funciones de la maquina de estados
 * 
 * @authors Maria Del Mar Arbelaez
 *        Julian Mauricio Sanchez
 * 
 * @date 2024-10-2
 */

// Standard libraries
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "pico/stdlib.h"


// Libs header file
#include "State_machine.h"

void in_serial(state_t *state)
{
    if (!state->wait_for_entry && uart_is_readable(uart_default))
    {
        state->option = uart_getc(uart_default);
        
        if (state->option >= '1' && state->option <= '2')
        {
            state_machine[state->option - '1'](*state);
            state->option = '0';
        } else {   
            printf("Invalid option\n");
            //mostrar el fokin menu
        }
    }

    if (state->wait_for_entry && uart_is_readable(uart_default))
    {   
        //que opcion eligió el usuario????
        
        uint8_t c = uart_getc(uart_default);
        if (c == '\n')
        {
            state->wait_for_entry = false;
        } else {
            state->usr[state->id] = c;
            state->id++;
        }
    }
}


void wait_for_option(state_t *state)
{   
    

    printf("Waiting for option\n");

    if (uart_is_readable(uart_default)) {
        state->option = uart_getc(uart_default);
        printf("Received: %c\n", state->option);
        state->change = true;
    }
    
}

