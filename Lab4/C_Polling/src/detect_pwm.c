/**
 * @file detect_pwm.c
 * 
 * @brief Implementacion de la detección del PWM
 * 
 * Este archivo contiene la detección del ciclo de dureza del PWM.
 * 
 * @authors María Del Mar Arbeláez
 *          Julián Mauricio Sánchez
 * 
 * @date 2024-10-12
 */

//Standard Libraries
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

//Pico Libraries
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "detect_pwm.h"

#define SLICE 

uint8_t slice_num;

void init_pwm_detect(){
    slice_num = pwm_gpio_to_slice_num(PWM_PIN);
}
//podría usar una estructura para las banderas !!!
uint8_t check_flank(void){
    //para que no haya flanco: 0
    //para que sea de subida: 1
    //para que sea de bajada: 2
    static bool before;
    bool now=gpio_get(PWM_PIN);
    if (before^now){
        before=now;
        if(now) {return 1;}
        else {return 2;}
    }
    return 0;
}

void setup_duty_cycle_read(){
    // Only the PWM B pins can be used as inputs.

    // Count once for every 100 cycles the PWM B input is high --> Freq max 1.25M
    pwm_config cfg = pwm_get_default_config();
    pwm_config_set_clkdiv_mode(&cfg, PWM_DIV_B_HIGH);
    pwm_config_set_clkdiv(&cfg, 100);
    pwm_init(slice_num, &cfg, false);
    gpio_set_function(PWM_PIN, GPIO_FUNC_PWM);

    pwm_set_enabled(slice_num, true);
}

uint16_t measure_duty_cycle() {
    setup_duty_cycle_read();
    sleep_ms(10); //máxima espera 50 //freq min -> 20Hz
    pwm_set_enabled(slice_num, false);
    uint32_t counting_rate =SYS_CLK_KHZ*10; //SYS_CLK_KHZ*1000 / 100;
    uint32_t max_possible_count = counting_rate * 0.01;

    uint16_t count=pwm_get_counter(slice_num); // 52m se acaba el contador. 16 bits-> 65536
    uint16_t duty=100*count/max_possible_count;
    return duty;
}

void calculate_duty();
