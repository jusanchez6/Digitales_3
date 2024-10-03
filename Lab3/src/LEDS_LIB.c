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

void init_leds(void)
{
    gpio_init_mask(LEDS_PINS);
    gpio_set_dir_out_masked(LEDS_PINS);
    gpio_put_masked(LEDS_PINS,0);
}

void change_led(uint8_t c)
{
    gpio_put_masked(LEDS_PINS,0);
    switch(c){
        case 0:
            gpio_put_masked(LEDS_PINS,LED_RED);
            break;
        case 1:
            gpio_put_masked(LEDS_PINS,LED_GREEN);
            break;
        case 2:
            gpio_put_masked(LEDS_PINS,LED_YELLOW);
            break;
        default:
            gpio_put_masked(LEDS_PINS,0);
            break;
    }
}

    
/*
bool repeating_timer_callback(repeating_timer_t *t) {
    //change output on matrix :0
    //printf("Repeat at %lld\n", time_us_64());
    t->user_data=(void*)true;
    return true;
}
*/