#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "mat.h"

volatile uint8_t reading=0; 
volatile uint8_t gpio_pressed;

static bool read_value(volatile uint8_t *value, volatile uint8_t *start){
    uint32_t start_time;
    char dic_mat[16]={'1','2','3','A','4','5','6','B','7','8','9','C','*','0','#','D'};
    //cambiar filas por columnas
    if(*start==1){
        printf("Setting up! ");
        gpio_put_masked(MAT_WRITE_PINS,0);
        set_dirs_mat(true);
        gpio_put(gpio_pressed,true);
        *start=4;
    }
    uint8_t lectura=(gpio_get_all() & MAT_WRITE_PINS)>>2;
    if (lectura){
        uint8_t c=0;
        while(!(lectura>>c & 1)){c++;}
        printf("Lectura:%d C:%d GPIO:%d \n",lectura,c,gpio_pressed);
        *value=dic_mat[c*4+gpio_pressed-6];
         //else{printf("HAY UN ERROR ");}
        //devolver a estado de lectura
        gpio_put(gpio_pressed,0);
        set_dirs_mat(false);
        gpio_put_masked(MAT_WRITE_PINS,0xF<<2);
        *start=2;
    }
}

void init_mat(void)
{
    gpio_init_mask(MAT_READ_PINS);
    gpio_set_dir_in_masked(MAT_READ_PINS);

    gpio_init_mask(MAT_WRITE_PINS);
    gpio_set_dir_out_masked(MAT_WRITE_PINS);
    // Set pull down resistors
    for (uint8_t i=6;i<=9;i++){ gpio_pull_down(i);}
}

void set_dirs_mat(bool change){
    if(change==false){
        gpio_set_dir_in_masked(MAT_READ_PINS);
        gpio_set_dir_out_masked(MAT_WRITE_PINS);
        for (uint8_t i=6;i<=9;i++){gpio_pull_down(i);}
    } else{
        gpio_set_dir_in_masked(MAT_WRITE_PINS);
        gpio_set_dir_out_masked(MAT_READ_PINS);
        for (uint8_t i=2;i<=5;i++){gpio_pull_down(i);}
    }
}

void init_callback(void){
    gpio_set_irq_enabled_with_callback(6,GPIO_IRQ_EDGE_FALL,true,&mat_callback);
    gpio_set_irq_enabled(7,GPIO_IRQ_EDGE_FALL,true);
    gpio_set_irq_enabled(8,GPIO_IRQ_EDGE_FALL,true);
    gpio_set_irq_enabled(9,GPIO_IRQ_EDGE_FALL,true);
}

void mat_callback(uint gpio, uint32_t events){
    if(reading==0){
        reading=1;
        gpio_pressed=(uint8_t)gpio;
    }
}

void change_mat(volatile uint8_t* cnt){
    uint8_t masky=1<<(((*cnt))%4);
    (*cnt)++;
    //printf("mask %d for printing: %x\n",*cnt,masky);
    //gpio_put_masked(MAT_WRITE_PINS,0);
    gpio_put_masked(MAT_WRITE_PINS,masky<<2);
}

bool repeating_timer_callback(repeating_timer_t *t) {
    //change output on matrix :0
    //printf("Repeat at %lld\n", time_us_64());
    t->user_data=(void*)true;
    return true;
}

bool read_mat(uint8_t c){
    /*
    DEBOUNCE SCHEMA
    si se presiona el boton y moment=0, moment=1 --> leer datos--> moment=2
    si hay evento y valor gpio=1, continuar en momento2
    si hay evento y valor gpio=0, empezar timer, momento3
    momento3-> revisar en 10ms -> si sigue en 0, momento0, si está en 1, momento2
    */
    static volatile uint8_t value;
    static uint32_t start;
    if(reading==1 || reading==4){
        read_value(&value,&reading);
    }
    if(!gpio_get(gpio_pressed) && reading==2){
        start=time_us_32();
        reading=3;
    }
    if(reading==3 && ((time_us_32()-start)/1000 >= 50)){
        if(gpio_get(gpio_pressed)==1){reading=2;}
        else{
            printf("Raw read value is: %c\n",value);
            reading=0;
            return true;
        }
    }
    return false;
}