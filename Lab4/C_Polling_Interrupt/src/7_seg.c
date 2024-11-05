/**
 * @file ./C_Polling_Interrupt/src/7_seg.c
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

void write_value(uint8_t value, bool dp){
    gpio_put_masked(SEGMENTS_MASK,(lookup[value] | dp<<7)<<START_PIN);
}

void write_decimals(uint16_t value){
    static uint32_t start;
    static uint8_t en;
    uint8_t enables[]={EN_1,EN_2,EN_3,EN_1};
    uint8_t val_2_wr;

    if (value / 1000){
        val_2_wr= en==1 ? 1 : 0; //si es las cents, es 0
        if((time_us_32()-start)>6000){
            gpio_put(enables[en],false);
            write_value(val_2_wr, 0); //00,01,10 -> solo es true cuando es 1.
            gpio_put(enables[en+1],true);
            start=time_us_32();
            en++;
            if(en>2){en=0;}
        }
    }
    else{
        switch (en)
        {
        case 0: //units
            val_2_wr=value % 10;
            break;
        case 1: //decimals <- este va con dp
            val_2_wr=(value%100)/10;
            break;
        case 2: //cents
            val_2_wr=value/100;
            break;
        }
        if((time_us_32()-start)>6000){
            gpio_put(enables[en],false);
            write_value(val_2_wr, !en); //00,01,10 -> solo es true cuando es 1.
            gpio_put(enables[en+1],true);
            start=time_us_32();
            en++;
            if(en>2){en=0;}
        }
    }
}