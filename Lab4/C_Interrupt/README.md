# Implementación con Interrupciones

## Descripción

Esta implementación se hace siguiendo el flujo de desarrollo con interrupciones de GPIO.
  
## Contenidos

- [main.c](#./C_Interrupt/src/main.c): Archivo principal que contiene la función principal del programa, inicializa y empieza la ejecución del programa.
- [7_seg.h](#./C_Interrupt/include/7_seg.h): Archivo con las declaraciones de las funciones y variables utilizadas para la visualización en los displays de 7 segmentos.
- [7_seg.c](#./C_Interrupt/src/7_seg.c): Archivo que contiene las funciones utilizadas para la visualización en los displays de 7 segmentos.
- [detect_pwm.h](#./C_Interrupt/include/detect_pwm.h): Archivo con las declaraciones de las funciones y variables utilizadas para la lectura del ciclo de dureza.
- [detect_pwm.c](#./C_Interrupt/src/detect_pwm.c): Archivo que contiene las funciones utilizadas para la visualización en los displays de 7 segmentos.
- [globals.h](#./C_Interrupt/include/globals.h): Archivo que contiene variables globales.
- **`page_int.dox`**: Archivo con el contenido de la página de interrupciones.
  

## Instrucciones de Uso
De este laboratorio en adelante se utilizará la extensión de la Raspberry Pi Pico en VScode que contiene la versión 2.0 del SDK.

1. **Preparación:**
   - Instalar correctamente la extensión e importar la carpeta como un proyecto de Raspberry Pi Pico.

2. **Compilación:**
   Presionar el botón inferior derecho `Compile`.

3. **Ejecución:**
   Presionar el botón de `Run` con la Raspberry Pi Pico conectada, si no nota la board conectada, es necesario conectarla en modo boot, como se suele hacer.

D: