/**
 * @file State_machine.h
 * @brief Archivo de cabecera de las funciones de la maquina de estados
 * 
 * Archivo de cabecera de las funciones de la maquina de estados
 * 
 * @authors Maria Del Mar Arbelaez
 *         Julian Mauricio Sanchez
 * 
 * @date 2024-10-2
 */

#include <stdint.h>

// Avoid duplication in code
#ifndef __STATE_MACHINE_H_
    #define __STATE_MACHINE_H_

    /**
     * \brief State machine structure
     * 
     * This structure contains the variables that are used in the state machine
     * 
     */
    typedef struct 
    {
        uint8_t option;
        uint8_t usr[6];
        uint8_t password[4];
        bool id;
        bool wait_for_entry; 
    } state_t;

    /**
     * \addtogroup Prototypes of the functions
     * 
     * @{
     * 
     * @brief Prototypes of the functions for the state machine
     */
    void wait_for_option(state_t &state);
    void wait_for_usr(state_t &state);
    void wait_for_password(state_t &state);
    void verify_id(state_t &state);
    void change_password(state_t &state);
    void in_serial(state_t &state);
    
    /**
     * @}
     */
    
    /**
     * \brief State machine
     * 
     * This function is the state machine that controls the flow of the program
     * 
     */
    typedef void (*state_machine_t)(state_t &state);
    state_machine_t state_machine[] = {wait_for_option, wait_for_usr, wait_for_password, verify_id, change_password};
#endif