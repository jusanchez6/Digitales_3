/**
 * @file Access.c
 * 
 * @brief Implementacion del sistema de control de accesso con teclado matricial
 * 
 * Este archivo contiene la implementación de las funciones necesarias para el sistema de control de acceso con verificacion de ID y clave de usuario, utilzando LEDs y un teclado matricial
 * 
 * @authors Maria Del Mar Arbelaez
 *         Julian Mauricio Sanchez
 * 
 * @date 2024-10-4
 */

// Standard libraries
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Pico libraries
#include "pico/stdlib.h"
#include "hardware/timer.h"

#include "Access.h"
#include "LEDS_LIB.h"
#include "libs.h"

/** @brief Variable global para almacenar el estado del temporizador */
static bool g_is_timeout = false;

/** @brief ID de la alarma configurada */
static alarm_id_t g_alarm_id;

/** @brief Base de datos de usuarios */
user_t users[MAX_USERS];

void init_users () {
    strcpy(users[0].id, "123456");
    strcpy(users[0].key, "1234");
    users[0].attempts = 0;
    users[0].blocked = false;

    strcpy(users[1].id, "654321");
    strcpy(users[1].key, "4321");
    users[1].attempts = 0;
    users[1].blocked = false;

    // Agregar mas usuarios si es necesario
}

bool verify_credentials (uint8_t *id, uint8_t *key) {
    
    for (int i = 0; i < MAX_USERS; i++) {
        if (strcmp(users[i].id, id) == 0 & !users[i].blocked) { //> Se verifica que el usuario no este bloqueado 

            if (strcmp(users[i].key, key) == 0) {
                users[i].attempts = 0;
                return true;
            } else {
                users[i].attempts++;
                if (users[i].attempts >= MAX_ATTEMPTS) {
                    users[i].blocked = true;
                }
                return false;
            }
        }

    } 
}


/**
 * @brief Funcion de callback para el temporizador de timeout
 * 
 * @param id ID de la alarma
 * @param user_data Datos de usuario
 * 
 * @return 0
 */
uint64_t timeout_callback(alarm_id_t id, void *user_data) {
    g_is_timeout = true;                    //> Se activa la bandera de timeout
    return 0;                               //> Se retorna 0 para detener la alarma
}


void start_timeout_timer(void) {
    g_is_timeout = false;
    g_alarm_id = add_alarm_in_ms(10000, timeout_callback, NULL, true);
}

bool timeout_expired(void) {
    return g_is_timeout;
}

void cancel_timeout_timer(void) {
    cancel_alarm(g_alarm_id);
}

void access_control(void) {
    uint8_t entered_id[6];
    uint8_t entered_key[4];

    // Encender led amarillo
    control_yellow_led(1);

    // Leer ID
    for (int i = 0; i < 6; i++) {
        
        
        entered_id[i] = read_mat();         //> CORREGIR
        // apagar el led amarillo en la primera lectura
        if (i == 0) {
            control_yellow_led(0);
        }
    }

    // Iniciar temporizador de timeout
    start_timeout_timer();

    // blink led amarillo
    control_yellow_led(2);

    // Leer clave
    for (int i = 0; i < 4; i++) {
        entered_key[i] = read_mat();         //> CORREGIR

        if (timeout_expired()) {
            signal_error(5000);
            return;
        }   
    }

    cancel_timeout_timer();

    if (verify_credentials(entered_id, entered_key)) {
        // encender led verde
        signal_success(5000);
    } else {
        // encender led rojo
        signal_error(5000);
    }

}