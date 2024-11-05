/**
 * @file Arduino.ino
 * 
 * @brief Este archivo contiene la función principal del proyecto.
 * 
 * @author María Del Mar Arbeláez
 * @author  Julián Mauricio Sánchez
 * 
 * @date 2024-11-4
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "./src/detect_pwm/detect_pwm.h"
#include "./src/7_seg/7_seg.h"


void setup() {
  init_7_seg();
  init_pwm_detect(); 
}

void loop() {
  uint16_t value=measure_duty_cycle();
  write_decimals(value);
}
