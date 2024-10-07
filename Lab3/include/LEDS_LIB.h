/**
 * @file LEDS_LIB.h
 * @brief Archivo de cabecera de las funciones de la libreria que controla
 * los leds
 * 
 * Archivo de cabecera de las funciones de la libreria que controla
 * los leds
 * 
 * @authors Maria Del Mar Arbelaez
 *          Julian Mauricio Sanchez
 * 
 * @date 2024-10-2
 */

#include <stdint.h>

// Avoid duplication in code
#ifndef __LED_LIB_H_
#define __LED_LIB_H_

#define LEDS_PINS 0x07 << 10            //0x0000 1110 0000 0000 
#define LED_RED 0x01 << 10              //0x0000 0010 0000 0000
#define LED_GREEN 0x01 << 11            //0x0000 0100 0000 0000
#define LED_YELLOW 0x01 << 12           //0x0000 1000 0000 0000
    

/**
 * @brief Inicializa los pines de los leds
 * 
 * Inicializa los pines de los leds como salidas
 */
void init_leds(void);


/**
 * @brief Enciende el LED verde durante un tiempo determinado
 * 
 * Enciende el LED verde durante un tiempo determinado
 * 
 * @param ms Tiempo en milisegundos que se encendera el LED
 * 
 * @return void
 */
void signal_success();

/**
 * @brief Enciende el LED rojo durante un tiempo determinado
 * 
 * Enciende el LED rojo durante un tiempo determinado
 * 
 * @param ms Tiempo en milisegundos que se encendera el LED
 * 
 * @return void
 */
void signal_error();

/**
 * @brief Controla el estado del LED amarillo (encender, apagar, titilar)
 * 
 * @param state Estado del LED amarillo (0: apagado, 1: encendido, 2: titilar)
 */
void control_yellow_led(uint8_t state);

/**
 * @brief apaga los leds
 */
void turn_off_leds(void);

    


#endif