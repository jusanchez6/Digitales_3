# Laboratorio 3: Sistema de Control de Acceso

## Descripción

Este proyecto implementa un sistema de control de acceso por medio de un teclado matricial. Este laboratorio tiene como objetivo la estructuración de un programa simple, junto con la configuración para la lectura del teclado matricial, y utilizar los módulos de temporización. Conceptos de utilidad para el transcurso del laboratorio de la asignatura Electrónica Digital 3.

## Contenidos

- **`main.c`**: Archivo principal que contiene la función principal del programa, inicializa y empieza la ejecución del programa.
- **`mat.h`**: Archivo de cabecera con las declaraciones de las funciones y variables utilizadas para la lectura del teclado matricial.
- **`mat.c`**: Archivo que contiene las funciones utilizadas para la lectura del teclado matricial.
- **`Access.h`**: Archivo de cabecera con las declaraciones de las funciones y variables utilizadas para la gestión del acceso.
- **`Access.c`**: Archivo que contiene las funciones utilizadas para la gestión del acceso.
- **`LEDS_LIB.h`**: Archivo de cabecera con las declaraciones de las funciones y variables utilizadas para la declaración y funcionamiento de los LEDS.
- **`LEDS_LIB.c`**: Archivo que contiene las funciones utilizadas para la declaración y funcionamiento de los LEDS.
- **`fsm.h`**: Archivo de cabecera con las declaraciones de las funciones y variables utilizadas para la interfaz de la máquina de estados.
- **`fsm.c`**: Archivo que contiene las funciones utilizadas para la interfaz de la máquina de estados.
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

1. En la carpeta `Lab_3` ejecutar el siguiente comando:
   ```bash
   doxygen Doxyfile
2. Se generará una carpeta con el nombre `html` en esta carpeta hay un archivo llamado `index.html` al abrir ese archivo se obtendrá la documentación en doxygen.

D: