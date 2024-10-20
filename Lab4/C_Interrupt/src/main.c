/**
 * @file main.c
 * @brief Main file for the project
 * 
 * This file contains the main function for the project.
 * 
 * @authors María Del Mar Arbeláez
 *          Julián Mauricio Sánchez
 * 
 * @date 2024-10-15
 */

#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/clocks.h"
#include "hardware/sync.h"
#include "pico/platform.h"

#include "detect_pwm.h"
#include "pwm.h"

#define PWM_PIN2 15

int main() {
    stdio_init_all();
    project_pwm_init();
    project_pwm_set_chan_level(3000);
    init_pwm_detection();
    

    while (1){
        __wfi();
    }
    return 0;
}
