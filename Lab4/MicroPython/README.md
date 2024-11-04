# Implementación con Micropython

## Descripción

Esta implementación se hace siguiendo el flujo de desarrollo con interrupciones usando Micropython.
  
## Contenidos

- **`main.py`**: Archivo principal que contiene la función principal del programa, inicializa y empieza la ejecución del programa, además de contener todas las funciones para el correcto funcionamiento del programa.
- **`RPI_PICO_W-20241025-v1.24.0.uf2`**: Ejecutable para instalar el ambiente de Micropython en la Raspbery Pi Pico W.
- **`RPI_PICO-20241025-v1.24.0.uf2`**: Ejecutable para instalar el ambiente de Micropython en la Raspbery Pi Pico.
- **`Doxyfile`**: Archivo de configuración para generar la documentación.
- **`MainPage.dox`**: Archivo con el contenido de la página principal.
  

## Instrucciones de Uso
De este laboratorio en adelante se utilizará la extensión de la Raspberry Pi Pico en VScode que contiene la versión 2.0 del SDK.

1. **Preparación:**
   - Instalar correctamente la extensión e importar la carpeta como un proyecto de Raspberry Pi Pico.
   - Presionar el botón de `Boot` de la RPP mientras se conecta al PC, esto abrirá una carpeta `RPI-RP2 (D:)` en la que se debe cargar el archivo mencionado anteriormente, esto se puede efectuar desde la terminal ubicándose en la carpeta `Micropython` del proyecto:

      ```bash
    cp .\RPI_PICO-20241025-v1.24.0.uf2.uf2 D:/
    ```
   Si se está trabajando con la Pico W, se escribe `.\RPI_PICO-20241025-v1.24.0.uf2`.

2. **Ejecución:**
   Presionar el botón de `Run` con la Raspberry Pi Pico conectada para cargar el archivo actual, que sería `main.py`.

## Instrucciones para la generación de la documentación

1. En la carpeta `Micropython` ejecutar el siguiente comando:
   ```bash
   doxygen Doxyfile
   ```
2. Se generará una carpeta con el nombre `html` en esta carpeta hay un archivo llamado `index.html` al abrir ese archivo se obtendrá la documentación en doxygen.

D: