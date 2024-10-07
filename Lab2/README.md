# Laboratorio 2: Tres en línea, manejo de gpio

## Descripción

Este proyecto implementa el juego Tres en Linea (Tic-Tac-Toe) en lenguaje C para la Raspberry Pi Pico. Este laboratorio busca emplear conceptos como el manejo de GPIOs de entrada y de salida, y la gestión del tiempo usando bases de tiempo y temporizadores. Conceptos de utilidad para el transcurso del laboratorio de la asignatura Electrónica Digital 3.

## Contenidos

- **`main.c`**: Archivo principal que contiene la función principal del programa. Inicializa todos lo módulos a utilizar y gestiona el flujo del botón de entrada, que da paso a toda la lógica del juego.
- **`libs.c`**: Archivo que contiene las funciones implementadas para el funcionamiento del juego Tic-Tac-Toe.
- **`libs.h`**: Archivo de cabecera con las declaraciones de las funciones y variables utilizadas para la aplicación del Tres en Línea.
- **`Doxyfile`**: Archivo de configuración para generar la documentación.
- **`MainPage.dox`**: Archivo con el contenido de la página principal.
  

## Instrucciones de Uso

1. **Preparación:**
   - El SDK de la Raspberry Pi Pico tiene que estar en funcionamiento, con el respectivo `CMakeLists` para el proyecto.
   - Asegúrate de tener todas las conecciones correctas de los LEDs, del botón y de los switches DIP:
       - **Matriz de LEDs**: va conectado de los pines 2 a 19.
       - **LED del jugador:** va conectado al pin 20.
       - **Botón:** va conectado al pin 28.
       - **DIPS:** va conectado a los pines 21, 22, 26 y 27.

2. **Compilación:**
   Presiona el botón de build en el SDK de la Raspberry Pi Pico.
   Esto debería generar una carpeta `build` en la que se encuentra el archivo `LAB2.uf2`, este será el archivo que se cargará a la Raspberry Pi Pico.

3. **Ejecución:**
   Presiona el botón de `Boot` de la RPP mientras la conectas al PC, esto abrirá una carpeta `RPI-RP2 (D:)` en la que se debe cargar el archivo mencionado anteriormente, esto se puede efectuar desde la terminal ubicándote en la carpeta `build` del proyecto:

      ```bash
    cp .\LAB2.uf2 D:/

## Instrucciones para la generación de la documentación

1. En la carpeta `Lab_2` ejecutar el siguiente comando:
   ```bash
   doxygen Doxyfile
2. Se generará una carpeta con el nombre `html` en esta carpeta hay un archivo llamado `index.html` al abrir ese archivo se obtendrá la documentación en doxygen.

:D 