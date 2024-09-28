/**
 * @file libs.c
 * 
 * @brief Implementación de las funciones de la librería
 * 
 * 
 * 
 * @authors Maria Del Mar Arbelaez Sandoval
 *         Julian Mauricio Sanchez Ceballos
 * 
 * @date 2024-09-18
 */

// Standard libraries
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "pico/stdlib.h"

// Libs header file
#include "libs.h"

volatile bool reading=false; 

void init_mat(void)
{
    gpio_init_mask(MAT_READ_PINS);
    gpio_set_dir_in_masked(MAT_READ_PINS);
    
    gpio_init_mask(MAT_WRITE_PINS);
    gpio_set_dir_out_masked(MAT_WRITE_PINS);

    // Set pull down resistors
    gpio_pull_down(6);
    gpio_pull_down(7);
    gpio_pull_down(8);
    gpio_pull_down(9);
}

void init_callback(void){
    gpio_set_irq_enabled_with_callback(6,GPIO_IRQ_EDGE_RISE,true,&mat_callback);
    gpio_set_irq_enabled(7,GPIO_IRQ_EDGE_RISE,true);
    gpio_set_irq_enabled(8,GPIO_IRQ_EDGE_RISE,true);
    gpio_set_irq_enabled(9,GPIO_IRQ_EDGE_RISE,true);
}

void mat_callback(uint gpio, uint32_t events){
    printf("a gpio %d was clicked\n",gpio);
    reading=true;
}

void change_mat(volatile uint8_t* cnt){
    uint8_t masky=1<<((++(*cnt))%4);
    //printf("mask %d for printing: %x\n",*cnt,masky);
    gpio_put_masked(MAT_WRITE_PINS,0);
    gpio_put_masked(MAT_WRITE_PINS,masky<<2);
}

bool repeating_timer_callback(repeating_timer_t *t) {
    //change output on matrix :0
    //printf("Repeat at %lld\n", time_us_64());
    t->user_data=(void*)true;
    return true;
}

void read_mat(uint8_t c){
    sleep_ms(50);
    char dic_mat[16]={'1','2','3','A','4','5','6','B','7','8','9','C','*','0','#','D'};
    uint8_t log[9]={0,0,1,0,2,0,0,0,3};
    char read=log[(gpio_get_all() & MAT_READ_PINS)>>6];
    read = dic_mat[(c%4)*4+read];
    printf("Raw read value is: %c\n",read);

    sleep_ms(100);
    reading=false;
}