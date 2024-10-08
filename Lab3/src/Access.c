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
#include <string.h> // Ensure this line is present

// Pico libraries
#include "pico/stdlib.h"
#include "hardware/timer.h"

#include "Access.h"
#include "LEDS_LIB.h"
#include "libs.h"
#include "mat.h" // Ensure 'read_mat' is declared in 'mat.h' "??????? what the fuck?????" -Julian 

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

    strcpy(users[2].id, "ABCD12");
    strcpy(users[2].key, "1234");
    users[2].attempts = 0;
    users[2].blocked = false;

    strcpy(users[3].id, "ABCD34");
    strcpy(users[3].key, "1234");
    users[3].attempts = 0;
    users[3].blocked = false;

    strcpy(users[4].id, "987654");
    strcpy(users[4].key, "1234");
    users[4].attempts = 0;
    users[4].blocked = false;

    

    // Agregar mas usuarios si es necesario
}

bool verify_credentials(uint8_t *id, uint8_t *key) {
    control_yellow_led(0);      // apagar el led amarillo
    for (int i = 0; i < MAX_USERS; i++) {
        printf("\nComparando usuario %d...", i);

        // Comparar ID
        if (memcmp(users[i].id, id, 6) == 0 && users[i].blocked == false) { // Cambiar a memcmp
            // Imprimir los IDs y claves que se comparan
            /*
            printf("\nID Usuario en base de datos: %s", users[i].id);
            printf("\nID Usuario ingresado: %s", id);
            printf("\nClave Usuario en base de datos: %s", users[i].key);
            printf("\nClave Usuario ingresada: %s", key);
            */
           
            // Comparar clave
            if (memcmp(users[i].key, key, 4) == 0) { // Cambiar a memcmp
                users[i].attempts = 0;
                return true;
            } else {
                printf("Clave incorrecta\n");
                users[i].attempts++;
                if (users[i].attempts >= MAX_ATTEMPTS) {
                    printf("Usuario bloqueado\n");
                    users[i].blocked = true;
                }
                return false;
            }
        }
    }
    printf("\nUsuario no encontrado o bloqueado\n");
    return false; // Retorna false si no se encuentra el usuario
}

void change_password(uint8_t *id, uint8_t *new_key) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (memcmp(users[i].id, id, 6) == 0) {
            strcpy(users[i].key, new_key);
            printf("Clave cambiada\n");
            return;
        }
    }
    printf("Usuario no encontrado\n");
}

bool access_control(uint8_t *id, uint8_t *key) {
    control_yellow_led(0); // Apaga el LED amarillo
    
    if (verify_credentials(id, key)) {
        signal_success(); // LED verde por 5 segundos
        return true;
    } else {
        signal_error(); // LED rojo por 2 segundos
        return false;
    }
    

}