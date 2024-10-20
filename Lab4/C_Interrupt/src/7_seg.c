/**
 * @file 7_seg.c
 * 
 * @brief Archivo que contiene las funciones para mostrar un número en un display de 7 segmentos
 * 
 * Este archivo contiene las funciones para mostrar un número en un display de 7 segmentos.
 * 
 * @authors María Del Mar Arbeláez
 *         Julián Mauricio Sánchez
 * 
 * @date 2024-10-12
 */

//stadard libraries
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

//pico libraries
#include "pico/stdlib.h"
#include "hardware/gpio.h"

//local libraries
#include "7_seg.h"

uint8_t lookup[10] ={
    0x3f, 0x06, 0x5b, 0x4f, 0x66,
    0x6d, 0x7d, 0x07, 0x7f, 0x6f
};

/**
 * @brief Inicializa los pines del display de 7 segmentos
 * 
 */
void init_7_seg(){
    gpio_init_mask(SEGMENTS_MASK);
    gpio_set_dir_out_masked(SEGMENTS_MASK);

    gpio_init(EN_1);
    gpio_set_dir(EN_1, GPIO_OUT);

    gpio_init(EN_2);
    gpio_set_dir(EN_2, GPIO_OUT);

    gpio_init(EN_3);
    gpio_set_dir(EN_3, GPIO_OUT);
}

/**
 * @brief Muestra un número en el display de 7 segmentos
 * 
 * @param number Número a mostrar
 */
void write_value(uint8_t value){
    printf("Writing:%d \n",value);
    gpio_put_masked(SEGMENTS_MASK,lookup[value]<<START_PIN);
}

/**
 * @brief Realiza la escritura de los decimales de un número
 * 
 * @param value Número a mostrar
 * @param run Puntero a la variable que indica el estado de la escritura
 *  
 */


void write_decimals(uint8_t value, uint8_t* run){
    static uint32_t start;
    uint8_t enables[] = {EN_1, EN_2, EN_3};
    uint8_t val_2_wr;

    if (*run == 0){
        start = time_us_32();
        *run = 1;
    }

    switch (*run)
    {
    case 0:
        val_2_wr = value % 10;
        break;
    case 1:
        val_2_wr = (value / 100) % 10;
        break;
    case 2:
        val_2_wr =value / 100;
        break;
    case 3:
        val_2_wr = value % 10;
        break;
    default:
        break;
    }

    // multiplexing
    if (time_us_32() - start > 1000>2){
        gpio_put(enables[*run - 1], 0);
        write_value(val_2_wr);
        gpio_put(enables[*run], 1);
        start = time_us_32();
        (*run)++;
        if (*run > 3){*run = 0;}
    }    

}