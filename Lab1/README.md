# Laboratorio 1: Implementación de Cifrado AES-128

## Descripción

Este proyecto implementa el algoritmo de cifrado AES-128 en lenguaje C. El objetivo es cifrar datos utilizando el estándar AES (Advanced Encryption Standard) para generar un primer acercamiento a la programación en lenguaje C, el manejo de tipos de datos, arreglos, punteros y operaciones a nivel de bit. Conceptos de utilidad para el transcurso del laboratorio de la asignatura Electrónica Digital 3.

## Contenidos

- **`main.c`**: Archivo principal que contiene la función principal del programa. Gestiona la lectura de la clave y la generación del state que es una matriz de 4x4, expande la clave para el cifrado, encripta el estado y guarda el resultado en un archivo de salida. Tiene dos argumentos de entrada, el archivo que se desea encriptar y la clave con que se hara la encriptación. 
- **`AES128_Func.c`**: Archivo que contiene las funciones implementadas por la función `Cypher` encargada de llevar a cabo la encriptación bajo el estandar AES128.
- **`AES128_Func.h`**: Archivo de cabecera con las declaraciones de las funciones y variables utilizadas en el proceso de encriptación.
- **`Doxyfile`**: Archivo de configuración para generar la documentación.
- **`MainPage.dox`**: Archivo con el contenido de la página principal.
  

## Instrucciones de Uso

1. **Preparación:**
   - Asegúrate de tener los archivos de entrada adecuados (`key.txt` y `text.txt`) en la carpeta `Textfiles`.
   - El archivo `key.txt` debe contener la clave de 16 bytes en formato hexadecimal o ASCII.
   - El archivo `text.txt` debe contener el texto que se desea encriptar.

2. **Compilación:**
   Ejecuta el siguiente comando en la carpeta de `src`:
   ```bash
   gcc main.c AES_Func.c -o main.exe

3. **Ejecución:**
   En la carpeta de src ejecutar el siguiente comando, teniendo en cuenta que el path que se maneja para el proyecto es `../TextFiles/archivo.txt`:
   ```bash
   ./main.exe PATH_TO_FILE_TO_ENCRYPT PATH_TO_KEY

Dentro de la carpeta `textFiles` debe existir el nombre del archivo que se desea cifrar, asi como la clave. 

4. **Tiempos de ejecución:**
   Despues de 20 ejecuciones, los resultados obtenidos se muestran en la siguiente tabla:
   
   | Tamaño del archivo | Tiempo promediado (s) | Desviación estándar (s) | Valor minimo (s) | Valor máximo (s)
   | --- | --- | --- | --- | --- |
   | 1 Gb | 190.001 | 3.5848 | 187.439 | 203.292 |
   | 100 Mb | 19.28885 | 0.5747 | 18.262 | 20.67 |
   | 10 Mb  | 1.929 | 0.0578 | 1.808 | 2.046 |

## Instrucciones para la generación de la documentación

1. En la carpeta `Lab_1` ejecutar el siguiente comando:
   ```bash
   doxygen Doxyfile
2. Se generará una carpeta con el nombre `html` en esta carpeta hay un archivo llamado `index.html` al abrir ese archivo se obtendrá la documentación en doxygen.

:) 