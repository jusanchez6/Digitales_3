/**
 * @file detect_pwm.cpp
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

#include "detect_pwm.h"

/** @brief Slice del GPIO de la lectura*/
uint8_t slice_num;

/** @brief Canal del GPIO de la lectura (Siempre debería ser B)*/
uint8_t channel;

void init_pwm_detect(){
    // Only the PWM B pins can be used as inputs.
  slice_num = pwm_gpio_to_slice_num(PWM_PIN);
  channel= pwm_gpio_to_channel(PWM_PIN);
  setup_duty_cycle_read(); //aquí configura y prende el slice
}

void setup_duty_cycle_read(){
    // Count once for every 100 cycles the PWM B input is high --> Freq max 1.25M
    pwm_config cfg = pwm_get_default_config();
    pwm_config_set_clkdiv_mode(&cfg, PWM_DIV_B_HIGH);
    pwm_config_set_clkdiv(&cfg, 100);
    pwm_init(slice_num, channel, &cfg, false);
    gpio_set_function(PWM_PIN, GPIO_FUNC_PWM);
    pwm_set_enabled(slice_num, true);
}

void calculate_duty(uint16_t* duty){
    pwm_set_enabled(slice_num, false); //apaga el slice
    uint32_t count=pwm_get_counter(slice_num); // 52m se acaba el contador. 16 bits-> 65536
    uint32_t counting_rate =SYS_CLK_KHZ*10; //SYS_CLK_KHZ*1000 / 100;
    uint32_t max_possible_count = counting_rate * 0.05; //por el tiempo total de medicion 
    *duty=1000*count/max_possible_count;
    printf("max_possible count:%d\n",max_possible_count);
    printf("duty count:%d\n",count);
    printf("duty percent:%d",*duty);
}

uint16_t measure_duty_cycle() {
    static uint16_t duty;
    static uint64_t start;
    if((time_us_64()-start)>=50000){ //espera de 50ms
        calculate_duty(&duty);
        setup_duty_cycle_read(); //aquí configura y prende el slice
        start=time_us_32();
    }
    return duty;
}