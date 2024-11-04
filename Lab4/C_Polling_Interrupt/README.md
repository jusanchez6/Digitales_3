# Implementación con Polling e Interrupciones

## Descripción

Esta implementación se hace siguiendo el flujo de desarrollo con interrupciones de GPIO y polling, donde, ante una interrupción, se cambia una bandera de software que se cuestionará como polling.
  
## Contenidos

- **`main.c`**: Archivo principal que contiene la función principal del programa, inicializa y empieza la ejecución del programa.
- **`7_seg.h`**: Archivo con las declaraciones de las funciones y variables utilizadas para la visualización en los displays de 7 segmentos.
- **`7_seg.c`**: Archivo que contiene las funciones utilizadas para la visualización en los displays de 7 segmentos.
- **`detect_pwm.c`**: Archivo con las declaraciones de las funciones y variables utilizadas para la lectura del ciclo de dureza.
- **`detect_pwm.h`**: Archivo que contiene las funciones utilizadas para la visualización en los displays de 7 segmentos.
- **`Doxyfile`**: Archivo de configuración para generar la documentación.
- **`MainPage.dox`**: Archivo con el contenido de la página principal.
  

## Instrucciones de Uso
De este laboratorio en adelante se utilizará la extensión de la Raspberry Pi Pico en VScode que contiene la versión 2.0 del SDK.

1. **Preparación:**
   - Instalar correctamente la extensión e importar la carpeta como un proyecto de Raspberry Pi Pico.

2. **Compilación:**
   Presionar el botón inferior derecho `Compile`.

3. **Ejecución:**
   Presionar el botón de `Run` con la Raspberry Pi Pico conectada, si no nota la board conectada, es necesario conectarla en modo boot, como se suele hacer.

## Instrucciones para la generación de la documentación

1. En la carpeta `C_Polling_Interrupt` ejecutar el siguiente comando:
   ```bash
   doxygen Doxyfile
   ```
2. Se generará una carpeta con el nombre `html` en esta carpeta hay un archivo llamado `index.html` al abrir ese archivo se obtendrá la documentación en doxygen.

D: