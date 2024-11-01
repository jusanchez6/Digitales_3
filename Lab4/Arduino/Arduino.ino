/**
 * @file 7_seg.c
 * 
 * @brief Implementacion de la escritura a los 7 segmentos
 * 
 * Este archivo contiene la implementación de los siete segmentos.
 * 
 * @authors María Del Mar Arbeláez
 *          Julián Mauricio Sánchez
 * 
 * @date 2024-10-12
 */

//#include "./libs/detect_pwm/detect_pwm.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "./src/detect_pwm/detect_pwm.h"
#include "./src/7_seg/7_seg.h"

#include "hardware/pwm.h"


void setup() {
  init_7_seg();
  init_pwm_detect(); 
}

void loop() {
  uint16_t value=measure_duty_cycle();
  write_decimals(value);
}
