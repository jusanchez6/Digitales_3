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

#include "detect_pwm.h"

uint8_t slice_num;

void init_pwm_detect(){
    // Only the PWM B pins can be used as inputs.
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
    // Count once for every 100 cycles the PWM B input is high --> Freq max 1.25M
    pwm_config cfg = pwm_get_default_config();
    pwm_config_set_clkdiv_mode(&cfg, PWM_DIV_B_HIGH);
    pwm_config_set_clkdiv(&cfg, 100);
    pwm_init(slice_num, &cfg, false);
    gpio_set_function(PWM_PIN, GPIO_FUNC_PWM);
    pwm_set_enabled(slice_num, true);
}

void calculate_duty(uint16_t* duty){
    pwm_set_enabled(slice_num, false); //apaga el slice
    uint32_t count=pwm_get_counter(slice_num); // 52m se acaba el contador. 16 bits-> 65536
    uint32_t max_possible_count = SYS_CLK_KHZ /2;
    *duty=1000*count/max_possible_count; //se multiplica por 1000 para que tenga espacio para el decimal
    printf("max_possible count 1:%d\n",max_possible_count);
    printf("max_possible count 1:%d\n",max_possible_count);
    printf("duty count:%d\n",count);
    printf("duty percent:%d",*duty);
}

uint16_t measure_duty_cycle() {
    static uint16_t duty;
    static uint8_t moment;
    static uint64_t start;
    if(!moment){
        moment=1;
        setup_duty_cycle_read(); //aquí configura y prende el slice
        start=time_us_32();

    }
    else if((time_us_64()-start)>=50000){ //espera de 50ms
        calculate_duty(&duty);
        moment=0;
    }
    return duty;
}
