/**
 * @file ./C_Polling/src/main.c
 * 
 * @brief Archivo principal del medidor de ciclo de dureza.
 * 
 * Este archivo inicializa los periféricos e implementa el main del medidor de ciclo de dureza.
 * 
 * @authors María Del Mar Arbeláez
 *          Julián Mauricio Sánchez
 * 
 * @date 2024-10-12
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "detect_pwm.h"  			// Detectar el pwm
#include "7_seg.h"           		// 7 segmentos

int main(){
    // Inicialización de la entrada/salida estándar
    stdio_init_all();   

    // Inicializar periféricos y recursos
    init_7_seg();
    init_pwm_detect();

    //enable the first

    // Bucle principal
    //uint8_t c=0;
    //uint64_t start=time_us_64();
    while (true) {
        uint16_t value=measure_duty_cycle();
        write_decimals(value);
    }
    return 0;           // Nunca se llegará aquí, el bucle es infinito
}