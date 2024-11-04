/**
 * @file ./Arduino/src/7_seg/7_seg.h
 * @brief Archivo de cabecera de las funciones de los 7 segmentos.
 * 
 * Archivo de cabecera de las funciones de la libreria.
 * 
 * @authors María Del Mar Arbeláez
 *          Julián Mauricio Sánchez
 * 
 * @date 2024-10-12
 */
#ifndef _7_SEG_H_
    #define _7_SEG_H_

    //Standard Libraries
    #include <stdio.h>
    #include <stdint.h>
    #include <stdbool.h>
    #include <Arduino.h>

    /** @brief Offset de los gpios */
    #define START_PIN 2

    /** @brief Máscara de los gpios */
    #define SEGMENTS_MASK 0xFF<<START_PIN

    /** @brief Pines de habilitación del display 1 */
    #define EN_1 12

    /** @brief Pines de habilitación del display 1 */
    #define EN_2 11

    /** @brief Pines de habilitación del display 1 */
    #define EN_3 10
    
    /**
     * @brief Inicializa los pines de los 7 segmentos
     * 
     * Esta función inicializa los pines de los 7 segmentos.
     * Asigna los pines como salida, asi como los enables.
     * 
     * @param void
     * 
     * @return void
     */
    void init_7_seg(void);


    /**
     * @brief Escribe un valor en los 7 segmentos
     * 
     * Esta función escribe un valor en los 7 segmentos.
     * 
     * @param value Valor a escribir
     * @param dp Booleano para agregar un punto
     * 
     * @return void
     */
    static inline void write_value(uint8_t value, bool dp);
    
    /**
     * @brief Escribe un valor en los 7 segmentos
     * 
     * Esta funcion es la encargada de separar los valores que se deben
     * escribir en el display y llama la funcion write value para que genere
     * la salida correspondiente de los gpios
     * 
     * @param value Valor a escribir
     * 
     * @return void
     */
    void write_decimals(uint16_t value);

#endif
