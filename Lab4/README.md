# Laboratorio 4: Comparación entre flujos de desarrollo

## Descripción

La aplicación que se desarrolla en esta práctica consiste en medir el porcentaje de dureza de una señal cuadrada
de cualquier frecuencia y mostrar este valor en 3 displays de 7 segmentos conectado de forma multiplexada. Esta
aplicación será implementada utilizando 5 flujos de programación para la Raspberry Pi Pico. Los flujos para los que
se implementará la medición de ciclo de dureza son:
- C con Polling.
- C con Interrupciones.
- C con Polling e Interrupciones.
- Arduino IDE.
- MicroPython.
  
## Contenidos

- [**`Arduino`**](./Arduino/README.md): Carpeta con los archivos para la implementación de Arduino.
- [**`C_Interrupt`**](./C_Interrupt/README.md): Carpeta con los archivos para la implementación con interrupciones.
- [**`C_Polling`**](./C_Polling/README.md): Carpeta con los archivos para la implementación con Polling.
- [**`C_Polling_Interrupt`**](./C_Polling_Interrupt/README.md): Carpeta con los archivos para la implementación con Polling e Interrupciones.
- [**`Micropython`**](./Micropython/README.md):Carpeta con los archivos para la implementación de MicroPython.
- [**`PWM_output`**](./PWM_output/README.md): Carpeta con los archivos para la implementación de un generador de PWM con un ciclo de dureza y frecuencia determinados.
- **`Doxyfile`**: Archivo de configuración para generar la documentación.
- **`MainPage.dox`**: Archivo con el contenido de la página principal.
  

## Comparación entre flujos de desarrollo

## Instrucciones para la generación de la documentación

1. En la carpeta `Lab_4` ejecutar el siguiente comando:
   ```bash
   doxygen Doxyfile
2. Se generará una carpeta con el nombre `html` en esta carpeta hay un archivo llamado `index.html` al abrir ese archivo se obtendrá la documentación en doxygen.

D: