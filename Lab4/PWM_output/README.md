# Implementación de generador de PWM

## Descripción

Esta implementación genera un PWM teniendo una frecuencia y un ciclo de dureza, se utiliza el módulo hardware del PWM.
  
## Contenidos

- **`main.c`**: Archivo principal que contiene la función principal del programa, inicializa y empieza la ejecución del programa.
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

1. En la carpeta `PWM_output` ejecutar el siguiente comando:
   ```bash
   doxygen Doxyfile
   ```
2. Se generará una carpeta con el nombre `html` en esta carpeta hay un archivo llamado `index.html` al abrir ese archivo se obtendrá la documentación en doxygen.

D: