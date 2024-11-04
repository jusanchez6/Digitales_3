/**
 * @file ./C_Interrupt/src/7_seg.c
 * 
 * @brief Implementacion de la escritura a los 7 segmentos
 * 
 * Este archivo contiene la implementación de las funciones que 
 * controlan el display de siete segmentos junto con su multiplexacion.
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
#include "../include/7_seg.h"

/**
 * @brief Tabla de conversión de valores a 7 segmentos
 */
uint8_t lookup[10] = {
       0x3f, 0x06, 0x5b, 0x4f, 0x66,
       0x6d, 0x7d, 0x07, 0x7f, 0x6f
   };

void init_7_seg(){
    gpio_init_mask(SEGMENTS_MASK);
    gpio_set_dir_out_masked(SEGMENTS_MASK);

    gpio_init(EN_1);
    gpio_set_dir(EN_1,true);

    gpio_init(EN_2);
    gpio_set_dir(EN_2,true);

    gpio_init(EN_3);
    gpio_set_dir(EN_3,true);

}

void write_value(uint8_t value){
    gpio_put_masked(SEGMENTS_MASK,lookup[value]<<START_PIN);
}

void write_decimals(uint16_t value, uint8_t* run){
    static uint32_t start;
    uint8_t enables[] = {EN_1, EN_2, EN_3};  // Pines de habilitación de cada dígito
    uint8_t val_2_wr;
    
    printf("Value: %d\n", value);
        printf("Current run: %d\n", *run);  

    // Control del tiempo de multiplexado
    if ((time_us_32()-start) > 4600) {
        if (*run > 0) {
            gpio_put(enables[*run - 1], 0);  // Apagar el display anterior
        } else {
            gpio_put(enables[2], 0);  // Apagar el display anterior
        }

        // Descomponer el valor en dígitos individuales
        switch (*run)
        {
        case 0:
            val_2_wr=value % 10;                        // parte decimal
            break;
        case 1:
            val_2_wr=(value %100) / 10;
            break;
        case 2:
            val_2_wr=(value /100);
            break;
        default:
            val_2_wr=0;
            break;
        }

        write_value(val_2_wr);
        
        gpio_put(enables[*run], 1);  // Apagar el display anterior

        
        // Actualizar el tiempo para el multiplexado
        start = time_us_32();
        (*run)++;

        // Si ya mostramos los tres dígitos, volvemos a empezar
        if (*run > 2) {
            *run = 0;  // Reiniciar para mostrar nuevamente desde el primer display
        }
    }
}