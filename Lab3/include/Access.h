/**
 * @file Access.h
 * 
 * @brief Declaraciones para el sistema de control de accesso con teclado matricial
 * 
 * Este archivo contiene las declaraciones de las funciones, estructuras y constantes necesarias
 * para el sistema de control de acceso con verificacion de ID y clave de usuario, utilzando ledas y un teclado matricial
 * 
 * @authors Maria Del Mar Arbelaez
 *          Julian Mauricio Sanchez
 * 
 * @date 2024-10-4
 */

#ifndef ACCESS_H
#define ACCESS_H

// Standard libraries
#include <stdint.h>
#include <stdbool.h>

// Pico libraries
#include "pico/stdlib.h"

/** @brief Numero maximo de usuarios en la base de datos */
#define MAX_USERS 10

/** @brief Numero maximo de intentos fallidos perrmitidos antes de bloquear el usuario */
#define MAX_ATTEMPTS 3

/**
 * @brief Estructura que representa un usuario
 * 
 * Contiene el ID, la clave, el numero de intentos fallidos y el estado del usuario
 */
typedef struct
{
    uint8_t id[6];
    uint8_t key[4];
    uint8_t attempts;
    bool blocked;
} user_t;


/**
 * @brief Inicializa la base de datos de usuarios
 * 
 * Carga una lista de usuarios con sus respectivos IDs y contraseñas
 * 
 */
void init_users(void);

/**
 * @brief Verifica las credenciales ingresadas
 * 
 * Compara el ID y la clave ingresados con los de la base de datos
 * 
 * @param id ID ingresado por el usuario
 * @param key Clave ingresada por el usuario
 * 
 * @return true si las credenciales son correctas, false en caso contrario
 */

bool verify_credentials(uint8_t *id, uint8_t *key);


/**
 * @brief Inicializa el temporizador para contar el tiempo de entreda de la clave
 * 
 * Configura una alamar que se dispara despues de un tiempo determinado (10 segundos)
 */
void start_timeout_timer(void);

/**
 * @brief Verifica si el tiempo limite de ingreso ha expirado
 * 
 * @return true si el tiempo ha expirado, false en caso contrario
 */
bool timeout_expired(void);

/**
 * @brief Cancela la alamra de tiempo limite
 * 
 * Detiene la alarma de tiempo limite si el proceso de verificacion se completo antes de que el tiempo limite haya expirado
 */
void cancel_timeout_timer(void);

/**
 * @brief Cambia la contraseña de un usuario
 * 
 * Cambia la contraseña de un usuario en la base de datos
 * 
 */
void change_password(uint8_t *id, uint8_t *new_key);


/**
 * @brief Procesa el accesso al sistema
 * 
 * Gestiona el flujo de entrada deln ID y la contraseña del usuario
 * reliando la verificacion de las credenciales y senalizando el estado del usuario
 * con los leds
 * 
 * @param id ID ingresado por el usuario
 * @param key Clave ingresada por el usuario
 * 
 * @return none
 */
bool access_control(uint8_t *id, uint8_t *key);


#endif