/**
 * @file main.c
 * 
 * @brief Archivo principal del generador de ciclo de dureza.
 * 
 * Este archivo se encarga de generar la salida de otro microcontrolador de pwm con un determinado ciclo de dureza
 * 
 * @authors María Del Mar Arbeláez
 *          Julián Mauricio Sánchez
 * 
 * @date 2024-10-22
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define PWM_OUT_PIN 15
#define FREQ 1000
#define DUTY 70

int main(){
    // Inicialización de la entrada/salida estándar
    stdio_init_all();

    //get the necessary pwm slice and channel for the pin
    uint8_t slice_num = pwm_gpio_to_slice_num(PWM_OUT_PIN);
    uint8_t channel_num= pwm_gpio_to_channel(PWM_OUT_PIN); 
     // 1 wrap --> 1.25MHz (100div)

    // 1 ciclo -> 1/1.25MHz
    // x ciclos -> 1/freq
    // x=(1/freq)*1.25MHZ 

    uint16_t cycles_per_freq=10*SYS_CLK_KHZ/FREQ;

    pwm_config cfg = pwm_get_default_config();
    pwm_config_set_clkdiv(&cfg, 100);
    pwm_config_set_wrap(&cfg,cycles_per_freq);
    pwm_init(slice_num, &cfg, false);

    gpio_set_function(PWM_OUT_PIN,GPIO_FUNC_PWM);

    uint32_t cycles_per_duty=cycles_per_freq*DUTY/100;
    pwm_set_chan_level(slice_num,channel_num,cycles_per_duty); // tres ciclos en 1

    pwm_set_enabled(slice_num,true);
    
    while(true){
        printf("ciclos de freq: %d\n",cycles_per_freq);
        printf("ciclos de duty: %d\n",cycles_per_duty);
        sleep_ms(500);
    }
    return 0;           // Nunca se llegará aquí, el bucle es infinito
}