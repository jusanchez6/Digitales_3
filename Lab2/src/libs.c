/**
 * @file libs.c
 * 
 * @brief Implementación de las funciones de la librería
 * 
 * Implementación de las funciones de la librería
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

/**
 * @brief Definición de la variable que contiene la mascara de posiciones
 * 
 * Variable que contiene la mascara de posiciones seleccionadas por los jugadores.
 */

uint16_t bitmask = 0;
volatile uint8_t position = -1;
volatile bool g_state_player = 0;
volatile uint16_t g_state_leds_0 = 0;
volatile uint16_t g_state_leds_1 = 0;
volatile bool button_pressed = false;

/**

static void start_animation(void){
    printf("Initial animation start!\n");

    gpio_put_masked(LEDS_PIN, 0);  // Apagar todos los LEDs
    sleep_ms(a_delay/2);  // Esperar un segundo antes de apagar todos los LEDs

    // triki-like sequence :)
    uint8_t pos[]={5,1,2,7,4,8,6};
    for (uint8_t i=0; i<7;i++){
        set_led(pos[i],i%2);
        sleep_ms(a_delay);

    }
    sleep_ms(a_delay/2);
    gpio_put_masked(LEDS_PIN,0);
    sleep_ms(a_delay/2);

    // 0010 1001 0101 0001 1000 (tablero) --> 29518

    for (uint8_t i=0; i<3;i++){
        gpio_put_masked(LEDS_PIN,0x29518);
        sleep_ms(a_delay);

        gpio_put_masked(LEDS_PIN,0);
        sleep_ms(a_delay/4);
    }
}


static void draw_animation(void){
    // very circle-oriented since it is a draw
    // 1010 1010 1010 1010 1000 (en binario) --> PLAYER 0
    // 0101 0101 0101 0101 0100 (en binario) --> PLAYER 1
    
    printf("Draw animation start!\n");
    gpio_put_masked(LEDS_PIN, 0);  // Apagar todos los LEDs
    sleep_ms(a_delay/2);  // Esperar un segundo antes de apagar todos los LEDs

    for (uint8_t i=0; i<=3; i++){
        gpio_put_masked(LEDS_PIN_PLAYER_0,(i%2 ? 0x22220 :~0x22220) & ~0xc00 );
        gpio_put_masked(LEDS_PIN_PLAYER_1,(i%2 ? 0x44044 :~0x44044) & ~0xc00 );
        sleep_ms(a_delay);
        gpio_put_masked(LEDS_PIN_PLAYER_0,0);
        gpio_put_masked(LEDS_PIN_PLAYER_1,0);
        sleep_ms(a_delay/2);
        gpio_put_masked(LEDS_PIN_PLAYER_1, i%2 ? 0xc00 :0 );
        gpio_put_masked(LEDS_PIN_PLAYER_0, i%2 ? 0 : 0xc00 );
        sleep_ms(a_delay);
        gpio_put_masked(LEDS_PIN_PLAYER_0,0);
        gpio_put_masked(LEDS_PIN_PLAYER_1,0);
        sleep_ms(a_delay/2);
    }
}


static void win_animation(bool player){
    //thingy running around
    // 0101 0101 0101 0101 0100 (en binario) --> PLAYER 1
    // 1010 1010 1010 1010 1000 (en binario) --> PLAYER 0

    printf("Win animation start!\n");
    printf("player mask:%x\n",LEDS_PIN_PLAYER_1<<(player));

    gpio_put_masked(LEDS_PIN, 0);  // Apagar todos los LEDs
    sleep_ms(a_delay/2);  // Esperar un segundo antes de apagar todos los LEDs

    uint8_t pos[]={0,1,2,5,8,7,6,3,4,3,6,7,8,5,2,1,0};

    for (uint8_t i=0; i<=17; i++){
        if(i!=9){gpio_put(2+(player)+pos[i]*2,1);}
        if(i!=0){gpio_put(2+(player)+pos[i-1]*2,1);}
        sleep_ms(a_delay/2);

        gpio_put_masked(LEDS_PIN_PLAYER_1 << (player),0);
        sleep_ms(a_delay/5);
    }
    // 0001 0001 0101 0001 0000 --> 11510
    for(uint8_t i=0; i<3;i++){
        gpio_put_masked(LEDS_PIN_PLAYER_1 << (player), 0x11510 << (player) );
        sleep_ms(a_delay/1.5);

        gpio_put_masked(LEDS_PIN_PLAYER_1 << (player),0);
        sleep_ms(a_delay/4);
    }

}


void init_read_gpio(void)
{
    gpio_init_mask(READ_PINS);
    gpio_init(BUTTON_PIN);

    gpio_set_dir_in_masked(READ_PINS);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);

    // Set pull down resistors
    gpio_pull_down(21);
    gpio_pull_down(22);
    gpio_pull_down(26);
    gpio_pull_down(27);
    gpio_pull_down(BUTTON_PIN);
}


void init_leds(void)
{
    //pines de jugadores
    gpio_init_mask(LEDS_PIN);
    gpio_set_dir_out_masked(LEDS_PIN);

    gpio_init(INNER_LED);
    gpio_set_dir(INNER_LED,true);
}


bool check_bitmask(uint16_t bitmask, uint8_t position)
{
    return bitmask & (1 << position);
}


int8_t read_binary_input(void)
{
    position = 0;
    position |= gpio_get(21) << 0;
    position |= gpio_get(22) << 1;
    position |= gpio_get(26) << 2;
    position |= gpio_get(27) << 3;
    return position;
}


void change_player(void)
{
    g_state_player = !g_state_player;   
    gpio_put(PLAYERS_PIN, !gpio_get(PLAYERS_PIN));
}


void set_led(uint8_t position, bool player)
{
    printf("Setting LED %d for player %d \n", position, player);
    if (!player)
    {
        // Set the LED for player 0
        gpio_put_masked(LEDS_PIN, gpio_get_all() | (1 << (position * 2)));

        // Update the state of the LEDs for player 0
        g_state_leds_0 |= (1 << (position - 1));
    }
    else
    {
        // Set the LED for player 1
        gpio_put_masked(LEDS_PIN, gpio_get_all() | (1 << ((position * 2) + 1)));

        // Update the state of the LEDs for player 1
        g_state_leds_1 |= (1 << (position - 1));
    }

    sleep_ms(100);  // Esperar un segundo para el feedback
    printf("State LEDs 0: %x \n", g_state_leds_0);
    printf("State LEDs 1: %x \n", g_state_leds_1);
}


void check_winner(void)
{
    // Combinaciones ganadoras en un tablero de 3x3
    uint16_t winning_patterns[8] = {
        0x07,  // 000 000 111 - fila 1
        0x38,  // 000 111 000 - fila 2
        0x1C0, // 111 000 000 - fila 3
        0x49,  // 001 001 001 - columna 1
        0x92,  // 010 010 010 - columna 2
        0x124, // 100 100 100 - columna 3
        0x54,  // 100 010 001 - diagonal 1
        0x111  // 001 010 100 - diagonal 2
    };

    // Revisar si el jugador 0 tiene alguna combinación ganadora
    for (int i = 0; i < 8; i++)
    {
        if ((g_state_leds_0 & winning_patterns[i]) == winning_patterns[i])
        {
            printf("Player 0 wins!\n");
            sleep_ms(a_delay/2);  // Esperar un segundo antes de apagar todos los LEDs
            win_animation(false);
            reset_game();
            return;
        }
    }

    // Revisar si el jugador 1 tiene alguna combinación ganadora
    for (int i = 0; i < 8; i++)
    {
        if ((g_state_leds_1 & winning_patterns[i]) == winning_patterns[i])
        {
            printf("Player 1 wins!\n");
            sleep_ms(a_delay/2);  // Esperar un segundo antes de apagar todos los LEDs
            win_animation(true);
            reset_game();
            return;
        }
    }

    // Revisar si hay un empate
    if ((g_state_leds_0 | g_state_leds_1) == 0x1ff)  // Todas las posiciones ocupadas
    {
        printf("It's a tie!\n");
        sleep_ms(a_delay/2);  // Esperar un segundo antes de apagar todos los LEDs
        draw_animation();
        reset_game();
        return;
    }
}

/**
 * @brief Resets the game after a win or tie.
 */
void reset_game(void)
{
    gpio_put_masked(LEDS_PIN, 0); // Turn off all LEDs
    bitmask = 0;
    g_state_leds_0 = 0;
    g_state_leds_1 = 0;
    start_animation();

    bitmask = 0;
    g_state_leds_0 = 0;
    g_state_leds_1 = 0;
    choose_player();
    printf("Game reset!\n");
}


void process_game (void) {
    if (position >= 1 && position <= 9)
    {
        if (check_bitmask(bitmask, position)) 
        {
            printf("Position %d already selected \n", position);
            gpio_put(INNER_LED, 1);  // Prender LED de error
            sleep_ms(3000);
            gpio_put(INNER_LED,0);
        }
        else
        {
            bitmask |= (1 << position);
            printf("Position %d selected \n", position);
            set_led(position, g_state_player);
            check_winner();
            change_player();
        }
    }
    else
    {
        printf("Invalid input, try again \n");
        gpio_put(INNER_LED, 1);  // Prender led de error
        sleep_ms(3000);
        gpio_put(INNER_LED,0);
    }
    position = -1; // Reset position after handling
}


void button_isr(uint gpio, uint32_t events)
{
    button_pressed = true;
}


void process_time(uint8_t *moment){
    //if moment=1, RISE-> start timer
    //if moment=0, FALL-> finish timer and print
    //if diff>5000, moment=3, which is the reset moment.
    static volatile uint32_t diff;
    printf("RISE:%d\n",*moment);
    if (*moment){
        diff=time_us_32();
        *moment=0;
    }
    else{
        diff=(time_us_32()-diff)/1000;
        *moment=1;
        printf("Time button pressed in ms: %d\n",diff);
        if (diff >= 5000){
            reset_game();
            *moment=2;
        }

    }
}



void choose_player(void){
    if(time_us_32()%2){
        g_state_player=0;
    }
    else{g_state_player=1;}
    gpio_put(PLAYERS_PIN, g_state_player);
}
