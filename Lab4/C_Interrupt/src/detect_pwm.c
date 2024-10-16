/**
 * @file detect_pwm.c
 * @brief Detecta la frecuencia de una señal PWM
 * 
 * Este archivo contiene la función detect_pwm que se encarga de detectar la frecuencia de una señal PWM.
 * 
 * @authors María Del Mar Arbeláez
 *         Julián Mauricio Sánchez
 * 
 * @date 2024-10-15
 */
#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/clocks.h"

#include "detect_pwm.h"
#include <cassert>


/**
 * @brief Función que se llama cuando se detecta un flanco de subida en la señal PWM
 * 
 * Esta función se llama cuando se detecta un flanco de subida en la señal PWM.
 * 
 * @param gpio Pin en el que se detectó el flanco de subida
 * @param events Eventos que ocurrieron en el pin
 */
void pwm_detect_callback (uint gpio, uint32_t events){
    if (events & GPIO_IRQ_EDGE_RISE){
        uint64_t current_time = time_us_64();
        
        if (g_last_edge_time != 0){
            uint64_t period = current_time - g_last_edge_time;
            g_last_edge_time = current_time;
            g_period = period;
            g_frequency = 1000000 / (float)period;
        }
        g_last_edge_time = current_time;
    }

    printf("Frecuencia: %llu\n", g_frequency);
    printf("Periodo: %llu\n", g_period);
}

/**
 * @brief Funcion para la medicion del ciclo de dureza mediante el pwm
 * 
 * Esta funcion se encarga de medir el ciclo de dureza de la señal PWM
 */
float measure_duty_cycle(uint gpio) {
    // Only the PWM B pins can be used as inputs.
    assert(pwm_gpio_to_channel(gpio) == PWM_CHAN_B);
    uint slice_num = pwm_gpio_to_slice_num(gpio);

    // Count once for every 100 cycles the PWM B input is high
    pwm_config cfg = pwm_get_default_config();
    pwm_config_set_clkdiv_mode(&cfg, PWM_DIV_B_HIGH);
    pwm_config_set_clkdiv(&cfg, 100);
    pwm_init(slice_num, &cfg, false);
    gpio_set_function(gpio, GPIO_FUNC_PWM);

    pwm_set_enabled(slice_num, true);
    sleep_ms(10);
    pwm_set_enabled(slice_num, false);
    float counting_rate = clock_get_hz(clk_sys) / 100;
    float max_possible_count = counting_rate * 0.01;
    return pwm_get_counter(slice_num) / max_possible_count;


}

/**
 * @brief Función que inicializa la detección de la señal PWM
 * 
 * Esta función inicializa la detección de la señal PWM en el pin 12.
 * 
 */
void init_pwm_detection(){
    gpio_init(PWM_PIN);
    gpio_set_dir(PWM_PIN, GPIO_IN);
    gpio_pull_down(PWM_PIN);
    gpio_set_irq_enabled_with_callback(PWM_PIN, GPIO_IRQ_EDGE_RISE, true, &pwm_detect_callback);
}

