/**
 * @file libs.h
 * @brief Archivo de cabecera de las funciones de la libreria.
 * 
 * Archivo de cabecera de las funciones de la libreria.
 * 
 * @authors Maria Del Mar Arbelaez
 *         Julian Mauricio Sanchez
 * 
 * @date 2024-09-18
 */

#include <stdint.h>

// Avoid duplication in code
#ifndef _LIBS_H_
    #define _LIBS_H_

    /**
    * @brief Definición de los pines de lectura de los botones
    * 
    * Mascara con la cual de definen los pines que se utilizan para ingresar
    * la posición de los jugadores.
    */
    #define READ_PINS 0x0E300000 // 0000 1110 0011 0000 0000 0000 0000 0000(en binario)
    
    /**
     * @brief Definición del pin del botón
     * 
     * Pin que se utiliza para activar la lectura de la posición de los jugadores.
     */
    #define BUTTON_PIN  28
    

    /**
     * @brief Definición de los pines de los leds
     * 
     * Mascara con la cual se definen el pin con el que se indica que jugador
     * tiene el turno actual
     */
    #define PLAYERS_PIN 20

    /**
     * @brief Definición de los pines de los leds
     * 
     * Mascara con la cual se definen los pines que se utilizan para indicar
     * la posición de los jugadores.
     */
    #define LEDS_PIN 0x001FFFFC // 0000 0010 0001 1111 1111 1111 1111 1100

    /**
     * @brief Definición de los pines de los leds jugador 0
     * 
     * Mascara con la cual se definen los pines que se utilizan para indicar
     * la posición de los jugadores.
     * 
     * 1010 1010 1010 1010 1000 (en binario)
     */
    #define LEDS_PIN_PLAYER_0 0x000AAAA8

    /**
     * @brief Definición de los pines de los leds jugador 1
     * 
     * Mascara con la cual se definen los pines que se utilizan para indicar
     * la posición de los jugadores.
     * 
     * 0101 0101 0101 0101 0100 (en binario)
     */  
    #define LEDS_PIN_PLAYER_1 0x00055554 

    /**
     * @brief Definición del pin indicador de posición invalida
     * 
     * Pin que se utiliza para indicar que la posición ingresada por el jugador
     * es invalida.  
    */ 
    #define INNER_LED 25 //LED interno



    #define striped_pattern   0xFFF77777
    #define a_delay 500


    /**
     * @brief Definición para la posición ingresada
     * 
     * Variable que almacena la posición ingresada por el jugador.
     * 
     */
    extern volatile uint8_t position;
    
    /**
     * @brief Definición para el estado del jugador
     * 
     * Indica si el jugador es el 0 o el 1.
     * 
     */
    extern volatile bool g_state_player;

    /**
     * @brief Definición para el estado de los leds
     * 
     * Indica mediante una mascara que posiciones ha encendido el jugador 0.
     * 
     */
    extern volatile uint16_t g_state_leds_0;
    
    /**
     * @brief Definición para el estado de los leds
     * 
     * Indica mediante una mascara que posiciones ha encendido el jugador 1.
     * 
     */
    extern volatile uint16_t g_state_leds_1;

    /**
     * @brief Definición de bandera para el boton de confirmación
     * 
     * Bandera que indica si el boton de confirmación ha sido presionado.
     * 
     */
    extern volatile bool button_pressed;




    /**
     * @brief Inicialización de los pines de lectura de los botones
     * 
     * Inicializa los pines que se utilizan para ingresar la posición de los jugadores.
     * 
     * @note Se inicializan los pines 23, 24, 25 y 28. Y la lectura se realiza binario 
     * 
     * @return void
     */
    void init_read_gpio (void );

    /**
     * @brief Inicialización de los pines de los leds
     * 
     * Inicializa los pines que se utilizan para indicar la posición de los jugadores.
     * Tambien los leds que muestran el turno del jugador, y si la posición ingresada es invalida.
     * 
     * @note Se inicializan los gpio 2-20 y 25.
     * 
     * @return void
     */
    void init_leds (void );

    /**
     * @brief Enciende un led
     * 
     * Enciende un led en la posición indicada.
     * 
     * @param position Posición del led a encender.
     * @param player Jugador al que pertenece el led.
     * 
     * @return void
     */
    void set_led (uint8_t position, bool player);

    /**
     * @brief check_bitmask
     * 
     * Verifica si el bit en la posición indicada esta encendido.
     * 
     * @param bitmask Mascara a verificar.
     * @param position Posición del bit a verificar.
     * 
     * @return bool
     */
    bool check_bitmask (uint16_t bitmask, uint8_t position);

    /**
     * @brief read_binary_input
     * 
     * Lee la posición ingresada por el jugador.
     * 
     * @note La lectura se realiza en binario.
     * 
     * @return int8_t
     */
    int8_t read_binary_input (void );

    /**
     * @brief button_isr
     * 
     * Función de interrupción que se activa cuando el boton de confirmación es presionado.
     * 
     * @param gpio Pin del boton.
     * @param events Eventos que activan la interrupción.
     * 
     * @return void
     */
    void button_isr (uint gpio, uint32_t events);

    /**
     * @brief change_player
     * 
     * Cambia el turno del jugador.
     * 
     * @return void
     */
    void change_player (void);

    /**
     * @brief reset_game
     * 
     * Reinicia el juego.
     * 
     * @return void
     */
    void reset_game (void);

    /**
     * @brief check_winner
     * 
     * Verifica si hay un ganador.
     * 
     * @return void
     */
    void check_winner (void);

    /**
     * @brief process_game
     * 
     * Procesa el juego.
     * 
     * @return void
     */
    void process_game (void);

    /**
     * @brief process_time
     * 
     * Procesa el tiempo.
     * 
     * @param moment Momento del juego.
     * 
     * @return void
     */
    void process_time(uint8_t*);

    /**
     * @brief choose_player
     * 
     * Elige el jugador que inicia el juego.
     * 
     * @return void
     */
    void choose_player(void);


#endif