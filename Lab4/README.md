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
- **`C_Polling`**: Carpeta con los archivos para la implementación con Polling.
- **`C_Polling_Interrupt`**: Carpeta con los archivos para la implementación con Polling e Interrupciones.
- **`Micropython`**:Carpeta con los archivos para la implementación de MicroPython.
- **`PWM_output`**: Carpeta con los archivos para la implementación de un generador de PWM con un ciclo de dureza y frecuencia determinados.
- **`Doxyfile`**: Archivo de configuración para generar la documentación.
- **`MainPage.dox`**: Archivo con el contenido de la página principal.
  

## Instrucciones de Uso

1. **Preparación:**
   - El SDK de la Raspberry Pi Pico tiene que estar en funcionamiento, con el respectivo `CMakeLists` para el proyecto.
   - Asegúrate de tener todas las conecciones correctas de los LEDs, del botón y de los switches DIP:
       - **Teclado Matricial**: va conectado de los pines 2 a 9, con el 2 conectado al primer pin del teclado.
       - **LEDs:** El LED rojo va conectado al pin 10, el LED verde al pin 11 y el amarillo al pin 12.

2. **Compilación:**
   Presiona el botón de build en el SDK de la Raspberry Pi Pico.
   Esto debería generar una carpeta `build` en la que se encuentra el archivo `LAB3.uf2`, este será el archivo que se cargará a la Raspberry Pi Pico.

3. **Ejecución:**
   Presiona el botón de `Boot` de la RPP mientras la conectas al PC, esto abrirá una carpeta `RPI-RP2 (D:)` en la que se debe cargar el archivo mencionado anteriormente, esto se puede efectuar desde la terminal ubicándote en la carpeta `build` del proyecto:

      ```bash
    cp .\LAB3.uf2 D:/

## Instrucciones para la generación de la documentación

1. En la carpeta `Lab_4` ejecutar el siguiente comando:
   ```bash
   doxygen Doxyfile
2. Se generará una carpeta con el nombre `html` en esta carpeta hay un archivo llamado `index.html` al abrir ese archivo se obtendrá la documentación en doxygen.

D: