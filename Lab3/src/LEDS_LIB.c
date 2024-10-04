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
#include "pico/stdlib.h"

// Libs header file
#include "LEDS_LIB.h"

/** @brief Timer para los leds */
static alarm_id_t g_alarm_led_id;

/** @brief Estado del led 0: no esta titilando, 1: esta titilando*/
static bool g_led_state = false;


/**
 * @brief Funcion de callback del temporizador de los leds
 * 
 * @param id ID de la alarma
 * @param user_data Datos de usuario
 * 
 * @return 500*1000 (500ms)
 */
uint64_t blink_callback(alarm_id_t id, void *user_data) {
    gpio_put_masked(LED_YELLOW, !gpio_get_masked(LED_YELLOW));
    return 500* 1000;   ///> Se retorna el tiempo en microsegundos para la siguiente interrupcion
}

/**
 * @brief Funcion de callback para apagar los leds
 * 
 * @param id ID de la alarma
 * @param user_data Datos de usuario
 * 
 * @return 0
 */
uint64_t gpio_put_masked_wrapper(alarm_id_t id, void *user_data) {
    gpio_put_masked((uint32_t)(uintptr_t)user_data, 0);
    return 0;
}

void init_leds(void)
{
    gpio_init_mask(LEDS_PINS);
    gpio_set_dir_out_masked(LEDS_PINS);
    gpio_put_masked(LEDS_PINS,0);
}

void signal_success(uint32_t ms)
{
    gpio_put_masked(LED_GREEN, 1);

    add_alarm_in_ms(ms, gpio_put_masked_wrapper, (void*)(uintptr_t)(LED_GREEN), false);
}

void signal_error(uint32_t ms)
{
    gpio_put_masked(LED_RED, 1);

    add_alarm_in_ms(ms, gpio_put_masked_wrapper, (void*)(uintptr_t)(LED_RED), false);
}

void control_yellow_led(uint8_t state)
{
    if (state == 0)
    {   
        //< Se apaga el led amarillo
        gpio_put_masked(LED_YELLOW, 0);
        cancel_alarm(g_alarm_led_id);
        g_led_state = false;        //> No se esta titilando
    }
    else if (state == 1)
    {
        //< Se enciende el led amarillo
        gpio_put_masked(LED_YELLOW, 1);
        cancel_alarm(g_alarm_led_id);
        g_led_state = false;        //> No se esta titilando
    }
    else if (state == 2)
    {
        //< Se titila el led amarillo
        g_alarm_led_id = add_repeating_alarm_in_ms(500, blink_callback, NULL, true);
        g_led_state = true;         //> Se esta titilando
    }
}

void turn_off_leds(void)
{
    gpio_put_masked(LEDS_PINS, 0);
    cancel_alarm(g_alarm_led_id);
    g_led_state = false;        //> No se esta titilando
}