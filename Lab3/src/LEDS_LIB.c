/**
 * @file LEDS_LIB.c
 * @brief Implementación de las funciones de la libreria que controla
 * los leds
 * 
 * Implementación de las funciones de la libreria que controla
 * 
 * @authors Maria Del Mar Arbelaez
 *         Julian Mauricio Sanchez
 * 
 * @date 2024-10-2
 */

// Standard libraries
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Pico libraries
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

// Libs header file
#include "LEDS_LIB.h"

/** @brief Timer para los leds */
volatile alarm_id_t g_alarm_led_id = -1;  // Inicializamos a un valor inválido

/** @brief Estado del led 0: no esta titilando, 1: esta titilando*/
volatile bool g_led_state = false;


/**
 * @brief Funcion de callback del temporizador de los leds
 * 
 * @param id ID de la alarma
 * @param user_data Datos de usuario
 * 
 * @return 500*1000 (500ms)
 */
int64_t blink_callback(alarm_id_t id, void *user_data) {
    if (id != g_alarm_led_id) {
        return 0;  // Si la alarma ha sido cancelada, no continuar
    }
    g_led_state = !g_led_state;
    gpio_put_masked(LED_YELLOW, g_led_state << 12);
    return 500 * 1000;   // Retorna el tiempo en microsegundos para la siguiente interrupción
}

void init_leds(void) {
    gpio_init_mask(LEDS_PINS);
    gpio_set_dir_out_masked(LEDS_PINS);
    gpio_put_masked(LEDS_PINS, 0);
}

void signal_success() {
    if (g_alarm_led_id != -1) {
        cancel_alarm(g_alarm_led_id);   // Cancela la alarma actual si existe
        g_alarm_led_id = -1;            // Reinicializa el valor
    }
    gpio_put_masked(LED_GREEN, LED_GREEN);
}

void signal_error() {
    if (g_alarm_led_id != -1) {
        cancel_alarm(g_alarm_led_id);   // Cancela la alarma actual si existe
        g_alarm_led_id = -1;            // Reinicializa el valor
    }
    gpio_put_masked(LED_RED, LED_RED);
}

void control_yellow_led(uint8_t state) {
    if (state == 0) {
        //< Se apaga el led amarillo
        if (g_alarm_led_id != -1) {
            cancel_alarm(g_alarm_led_id);   // Cancela la alarma si estaba titilando
            g_alarm_led_id = -1;            // Reinicializa el valor
        }
        gpio_put_masked(LED_YELLOW, 0 << 12);
    } 
    else if (state == 1) {
        //< Se enciende el led amarillo
        if (g_alarm_led_id != -1) {
            cancel_alarm(g_alarm_led_id);   // Cancela la alarma si estaba titilando
            g_alarm_led_id = -1;            // Reinicializa el valor
        }
        gpio_put_masked(LED_YELLOW, LED_YELLOW);
    } 
    else if (state == 2) {
        //< Se titila el led amarillo
        if (g_alarm_led_id != -1) {
            cancel_alarm(g_alarm_led_id);   // Cancela cualquier alarma previa
        }
        g_alarm_led_id = add_alarm_in_ms(500, blink_callback, NULL, false);  // Configura la nueva alarma
    }
}
void turn_off_leds(void) {
    sleep_ms(2000);  // Espera 2 segundos antes de apagar
    gpio_put_masked(LEDS_PINS, 0x000 << 10);
    gpio_put_masked(LED_YELLOW, 0x000 << 12);
    
    // Cancela la alarma de titilado si existe
    if (g_alarm_led_id != -1) {
        if (cancel_alarm(g_alarm_led_id)) {
            printf("Alarma cancelada\n");
            g_alarm_led_id = -1;  // Reinicializa el valor después de cancelar
        } else {
            printf("No se pudo cancelar la alarma\n");
        }
    }
}