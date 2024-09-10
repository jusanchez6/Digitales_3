/**
 * @file main.c
 * @brief This is a brief description of the main C file.
 *
 * Detailed description of the main C file.
 */

// Standard libraries
#include <stdio.h>
#include "pico/stdlib.h"

const uint led_pin = 15;
const uint led_pin1 = 13;
const uint pin = 14;
const uint pin1 = 12;


/**
 * @brief This is a brief description of the main function.
 * 
 * This function is called when a GPIO intgerrupty occurs
 * 
 * @param pin The pin that triggered the interrupt
 * @param event The event that triggered the interrupt (falling or rising)
*/
void gpio_callback (uint gpio, uint32_t event) {
    bool button;
    switch (gpio)
    {
    case pin:
        button = gpio_get(pin);
        gpio_put(led_pin, button);
        printf("Button: %d\n", button);
        break;
    
    case pin1:
        button = gpio_get(pin1);
        gpio_put(led_pin1, button);
        printf("Button1: %d\n", button);
        break;

    default:
        break;
    }
}

/**
 * @brief Main program.
 *
 * This function initializes the MCU and does an infinite cycle.
 */
int main() {
	// STDIO initialization
    stdio_init_all();
    
	// Write your initialization code here
    gpio_init(led_pin);
    gpio_init(pin);
    gpio_init(led_pin1);
    gpio_init(pin1);

    // Set the gpio functions
    gpio_set_dir(pin, GPIO_IN);
    gpio_set_dir(pin1, GPIO_IN);
    gpio_set_dir(led_pin, GPIO_OUT);
    gpio_set_dir(led_pin1, GPIO_OUT);


    gpio_pull_down(pin);
    gpio_pull_down(pin1);

    // Set the interrupt
    gpio_set_irq_enabled_with_callback(pin, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
    gpio_set_irq_enabled_with_callback(pin1, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &gpio_callback);

	// Infinite loop. This function shouldn't finish or return
    while (1) {
        // blink 
        gpio_put(led_pin, 1);
        sleep_ms(1000);
        gpio_put(led_pin, 0);
        sleep_ms(1000);
    }
    
    return 0;    
}