#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>

extern volatile uint8_t update_display_flag;  // Bandera para indicar que se debe actualizar el display
extern volatile uint64_t g_duty_cycle;
#endif // GLOBALS_H