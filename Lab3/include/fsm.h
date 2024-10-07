/**
 * @file fsm.h
 * 
 * @brief Interfaz de la máquina de estados para el control de acceso.
 * 
 * Este archivo define la interfaz de la máquina de estados que maneja 
 * la lógica del sistema de control de acceso, permitiendo la entrada 
 * de usuario y la verificación de credenciales.
 * 
 * @authors Maria Del Mar Arbelaez
 *          Julian Mauricio Sanchez
 * 
 * @date 2024-10-10
 */


#include <stdint.h>
#include <stdbool.h>

#ifndef FSM_H_
#define FSM_H_


/**
 * @brief Inicializa la máquina de estados.
 * 
 * Esta función establece el estado inicial de la máquina de estados 
 * y reinicia los índices de entrada de ID y contraseña.
 */
void fsm_init(void);

/**
 * @brief Ejecuta la máquina de estados.
 * 
 * Llama a la función correspondiente al estado actual de la máquina 
 * de estados.
 */
void fsm_run(void);

/**
 * @brief Verifica las credenciales del usuario.
 * 
 * Esta función verifica si el ID y la contraseña proporcionados son 
 * válidos.
 * 
 * @param id Cadena que representa el ID del usuario.
 * @param password Cadena que representa la contraseña del usuario.
 * @return true si las credenciales son válidas, false en caso contrario.
 */
bool verify_credentials(uint8_t *id, uint8_t *key);




#endif