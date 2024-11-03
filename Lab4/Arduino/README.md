# Implementación con Arduino

## Descripción

Esta implementación se hace siguiendo el flujo de desarrollo polling, utilizando el módulo hardware de PWM para hacer la lectura.
Se utiliza el ArduinoCore Mbed para la integración con el RP2040, manteniendo ciertas funciones del SDK.
  
## Contenidos

- **`Arduino.ino`**: Archivo principal que contiene la función principal del programa, inicializa y empieza la ejecución del programa.
- **`7_seg.h`**: Archivo con las declaraciones de las funciones y variables utilizadas para la visualización en los displays de 7 segmentos.
- **`7_seg.c`**: Archivo que contiene las funciones utilizadas para la visualización en los displays de 7 segmentos.
- **`detect_pwm.c`**: Archivo con las declaraciones de las funciones y variables utilizadas para la lectura del ciclo de dureza.
- **`detect_pwm.h`**:  Archivo que contiene las funciones utilizadas para la visualización en los displays de 7 segmentos.
- **`Doxyfile`**: Archivo de configuración para generar la documentación.
- **`MainPage.dox`**: Archivo con el contenido de la página principal.
  
## Instrucciones de Uso

1. **Preparación:**
   - Se debe abrir el documento principal `Arduino.ino` en el IDE de Arduino

2. **Ejecución:**
   Presionar el botón de `Upload` con la Raspberry Pi Pico conectada.

## Instrucciones para la generación de la documentación

1. En la carpeta `Arduino` ejecutar el siguiente comando:
   ```bash
   doxygen Doxyfile
2. Se generará una carpeta con el nombre `html` en esta carpeta hay un archivo llamado `index.html` al abrir ese archivo se obtendrá la documentación en doxygen.

D: