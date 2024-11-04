# Implementación con Arduino

## Descripción

Esta implementación se hace siguiendo el flujo de desarrollo polling, utilizando el módulo hardware de PWM para hacer la lectura.
Se utiliza el ArduinoCore Mbed para la integración con el RP2040, manteniendo ciertas funciones del SDK.
  
## Contenidos

- [Arduino.ino](#Arduino.ino): Archivo principal que contiene la función principal del programa, inicializa y empieza la ejecución del programa.
- [7_seg.h](#./Arduino/src/7_seg/7_seg.h): Archivo con las declaraciones de las funciones y variables utilizadas para la visualización en los displays de 7 segmentos.
- [7_seg.cpp](#7_seg.cpp): Archivo que contiene las funciones utilizadas para la visualización en los displays de 7 segmentos.
- [detect_pwm.h](#./Arduino/src/detect_pwm/detect_pwm.h): Archivo con las declaraciones de las funciones y variables utilizadas para la lectura del ciclo de dureza.
- [detect_pwm.cpp](#detect_pwm.cpp):  Archivo que contiene las funciones utilizadas para la visualización en los displays de 7 segmentos.
- **`page_ard.dox`**: Archivo con el contenido de la página de ArduinoS.
  
## Instrucciones de Uso

1. **Preparación:**
   - Se debe abrir el documento principal `Arduino.ino` en el IDE de Arduino

2. **Ejecución:**
   Presionar el botón de `Upload` con la Raspberry Pi Pico conectada.

D: