/**
 * @file 7_seg.cpp
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


#include "7_seg.h"

/** @brief Look-up table de las máscaras de salida del 7 segmentos*/
uint8_t lookup[10] = {
    0x3f, 0x06, 0x5b, 0x4f, 0x66,
    0x6d, 0x7d, 0x07, 0x7f, 0x6f
};


static inline void write_value(uint8_t value,bool dp){
  for (int8_t i=0; i<=7;i++){
    digitalWrite(i+START_PIN,((lookup[value] | dp<< 7 )>>i)&1);
  }
}

void init_7_seg(){
  for (int8_t i=START_PIN; i<=START_PIN+7;i++){
    pinMode(i,OUTPUT);
  }
  pinMode(EN_1, OUTPUT);
  pinMode(EN_2, OUTPUT);
  pinMode(EN_3, OUTPUT);
}

void write_decimals(uint16_t value){
    static uint32_t start;
    static uint8_t en;
    uint8_t enables[]={EN_1,EN_2,EN_3,EN_1};
    uint8_t val_2_wr;

    if (value / 1000){
        val_2_wr= en==1 ? 1 : 0; //si es las cents, es 0
        if((time_us_32()-start)>6000){
            digitalWrite(enables[en],false);
            write_value(val_2_wr, 0); //00,01,10 -> solo es true cuando es 1.
            digitalWrite(enables[en+1],true);
            start=time_us_32();
            en++;
            if(en>2){en=0;}
        }
    }
    else{
        switch (en)
        {
        case 2: //units
            val_2_wr=value % 10;
            break;
        case 0: //decimals <- este va con dp
            val_2_wr=(value%100)/10;
            break;
        case 1: //cents
            val_2_wr=value/100;
            break;
        }
        if((time_us_32()-start)>6000){
            digitalWrite(enables[en],false);
            write_value(val_2_wr, !en); //00,01,10 -> solo es true cuando es 1.
            digitalWrite(enables[en+1],true);
            start=time_us_32();
            en++;
            if(en>2){en=0;}
        }
    }
}