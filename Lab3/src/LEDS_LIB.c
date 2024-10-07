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
static alarm_id_t g_alarm_led_id;

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
    g_led_state = !g_led_state;
    gpio_put_masked(LED_YELLOW, g_led_state << 12);
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
int64_t turn_off_red_callback(alarm_id_t id, void *user_data) {
    gpio_put_masked(LED_RED, 0x00 << 10);
    return 0;
}

/**
 * @brief Funcion de callback para apagar los leds
 * 
 * @param id ID de la alarma
 * @param user_data Datos de usuario
 * 
 * @return 0
 */
int64_t turn_off_green_callback(alarm_id_t id, void *user_data) {
    gpio_put_masked(LED_GREEN, 0 << 11);
    return 0;
}

void init_leds(void)
{
    gpio_init_mask(LEDS_PINS);
    gpio_set_dir_out_masked(LEDS_PINS);
    gpio_put_masked(LEDS_PINS,0);
}

void signal_success()
{
    cancel_alarm(g_alarm_led_id);
    gpio_put_masked(LED_GREEN, LED_GREEN);
}

void signal_error()
{
    cancel_alarm(g_alarm_led_id);
    gpio_put_masked(LED_RED, LED_RED);
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
        gpio_put_masked(LED_YELLOW, LED_YELLOW);
        cancel_alarm(g_alarm_led_id);
        g_led_state = false;        //> No se esta titilando
    }
    else if (state == 2)
    {
        //< Se titila el led amarillo
        add_alarm_in_ms(500, blink_callback, NULL, false);
    }
}

void turn_off_leds(void)
{
    sleep_ms(2000);
    gpio_put_masked(LEDS_PINS, 0x000 << 10);
    cancel_alarm(g_alarm_led_id);
}