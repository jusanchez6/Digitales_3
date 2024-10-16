/**
 * @file pwm.c
 */

// Standard libraries
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

// PWM header file
#include "pwm.h"

// PWM initialization for the project
void project_pwm_init() {
    // Initialize function PWM for GPIO: PWM_GPIO_CHA
    gpio_set_function(PWM_GPIO_CHA, GPIO_FUNC_PWM);
    // Determine the PWM slice connected to GPIO: PWM_GPIO_CHA
    uint sliceNum = pwm_gpio_to_slice_num(PWM_GPIO_CHA);
    // Set period for frequency divisor
    pwm_set_clkdiv_int_frac(sliceNum, PWM_DIV_INTEGER, PWM_DIV_FRAC); // What frequency enters to the PWM?
    // Set top (wrap) value (Determines the frequency)
    pwm_set_wrap(sliceNum, PWM_TOP_VALUE);
    // Set zero duty
    pwm_set_chan_level(sliceNum, PWM_CHA, PWM_DUTY_ZERO);
    // Enable PWM
    pwm_set_enabled(sliceNum, true);    
}

// PWM counter compare level changer
void project_pwm_set_chan_level(uint value) {
    // Determine the PWM slice connected to GPIO: PWM_GPIO_CHA
    uint sliceNum = pwm_gpio_to_slice_num(PWM_GPIO_CHA);
    // Set duty
    pwm_set_chan_level(sliceNum, PWM_CHA, value);
}