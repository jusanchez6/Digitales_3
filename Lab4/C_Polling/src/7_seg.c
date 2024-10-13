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

//Standard Libraries
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

//Pico Libraries
#include "pico/stdlib.h"
#include "7_seg.h"

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
    printf("Writing:%d \n",value);
    gpio_put_masked(SEGMENTS_MASK,lookup[value]<<START_PIN);
}

void write_decimals(uint8_t value, uint8_t* run){
    static uint32_t start;
    uint8_t enables[]={EN_1,EN_2,EN_3,EN_1};
    uint8_t val_2_wr;
    if (*run==0)
    {
        start=time_us_32();
        *run=1;
    }
    
    switch (*run)
    {
    case 0:
        val_2_wr=value % 10;
        break;
    case 1:
        val_2_wr=(value%100)/10;
        break;
    case 2:
        val_2_wr=value/100;
        break;
    case 3:
        val_2_wr=value % 10;
        break;
    }
    printf("Round:%d Value:%d\n",*run, val_2_wr);
    if((time_us_32()-start)/1000>2){
        gpio_put(enables[*run-1],false);
        write_value(val_2_wr);
        gpio_put(enables[*run],true);
        start=time_us_32();
        (*run)++;
        if(*run>3){*run=1;}
    }
}