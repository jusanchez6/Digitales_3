/**
 * @file mat.c
 * 
 * @brief Implementacion de la lectura del teclado matricial
 * 
 * Este archivo contiene la implementación de la lectura del teclado matricial con inicialización y debounce.
 * 
 * @authors Maria Del Mar Arbelaez
 *          Julian Mauricio Sanchez
 * 
 * @date 2024-10-4
 */

//Standard Libraries
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

//Pico Libraries
#include "pico/stdlib.h"
#include "mat.h"

static volatile uint8_t reading; /*!< Momento de lectura del teclado. */
static volatile uint8_t gpio_pressed; /*!< GPIO que genera la interrupción. */

  /**
 * @brief Función que se ejecuta cuando se presiona una tecla
 * 
 * Callback que se ejecuta para activar la bandera de lectura.
 * 
 * @param gpio gpio que genera la interrupción.
 * @param event evento.
 * 
 * @return void
 */
void mat_callback(uint gpio, uint32_t events){
    if(reading==0){
        reading=1;
        gpio_pressed=(uint8_t)gpio;
    }
}

/**
 * @brief Inicializacion del callback
 * 
 * Descripción de pines y función a utilizar.
 * 
 * @return void
 */
void init_callback(void){
    gpio_set_irq_enabled_with_callback(6,GPIO_IRQ_EDGE_RISE,true,&mat_callback);
    gpio_set_irq_enabled(7,GPIO_IRQ_EDGE_RISE,true);
    gpio_set_irq_enabled(8,GPIO_IRQ_EDGE_RISE,true);
    gpio_set_irq_enabled(9,GPIO_IRQ_EDGE_RISE,true);
}

void init_mat(void)
{
    gpio_init_mask(MAT_READ_PINS);
    gpio_set_dir_in_masked(MAT_READ_PINS);

    gpio_init_mask(MAT_WRITE_PINS);
    gpio_set_dir_out_masked(MAT_WRITE_PINS);
    // Set pull down resistors
    for (uint8_t i=2;i<=9;i++){gpio_pull_down(i);}
    gpio_put_masked(MAT_WRITE_PINS,0xF<<2);
    reading=0;
    init_callback();
}

void set_dirs_mat(bool change){
    if(change==false){
        gpio_set_dir_in_masked(MAT_READ_PINS);
        gpio_set_dir_out_masked(MAT_WRITE_PINS);
        //for (uint8_t i=6;i<=9;i++){gpio_pull_down(i);}
    } else{
        gpio_set_dir_in_masked(MAT_WRITE_PINS);
        gpio_set_dir_out_masked(MAT_READ_PINS);
        //for (uint8_t i=2;i<=5;i++){gpio_pull_down(i);}
    }
}

bool read_mat(volatile uint8_t* value){
    /*
        DEBOUNCE SCHEMA
        si se presiona el boton y moment=0, moment=1 --> leer datos--> moment=2
        si hay evento y valor gpio=1, continuar en momento2
        si hay evento y valor gpio=0, empezar timer, momento3
        momento3-> revisar en 10ms -> si sigue en 0, momento0, si está en 1, momento2
    */
    static uint32_t start;
    if(reading==1){
        gpio_put_masked(MAT_WRITE_PINS,0);
        set_dirs_mat(true);
        gpio_put(gpio_pressed,true);
        reading=2;
    }
    else if(reading==2){
        char dic_mat[16]={'1','2','3','A','4','5','6','B','7','8','9','C','*','0','#','D'};
        uint8_t lectura=(gpio_get_all() & MAT_WRITE_PINS)>>2;
        if (lectura){
            uint8_t c=0;
            while(!(lectura>>c & 1)){c++;} //encontrar la posicion en 1
            *value=dic_mat[c*4+gpio_pressed-6];
            //devolver a estado de lectura
            gpio_put(gpio_pressed,0);
            set_dirs_mat(false);
            gpio_put_masked(MAT_WRITE_PINS,0xF<<2);
            reading=3;
    }
    }
    else if(!gpio_get(gpio_pressed) && reading==3){
        start=time_us_32();
        reading=4;
    }
    else if(reading==4 && ((time_us_32()-start)/1000 >= 50)){
        if(gpio_get(gpio_pressed)==1){reading=3;}
        else{
            reading=0;
            return true;
        }
    }
    return false;
}