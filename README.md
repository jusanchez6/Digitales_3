![image](https://github.com/user-attachments/assets/43e13d73-60d3-4ee2-b766-231c188d9905)# Laboratorio de Digitales 3
# Laboratorio 1: Implementación de Cifrado AES-128

## Descripción

Este proyecto implementa el algoritmo de cifrado AES-128 en lenguaje C. El objetivo es cifrar datos utilizando el estándar AES (Advanced Encryption Standard) para generar un primer acercamiento a la programación en lenguaje C, el manejo de tipos de datos, arreglos, punteros y operaciones a nivel de bit. Conceptos de utilidad para el transcurso del laboratorio de la asignatura Electrónica Digital 3.

## Contenidos

- **`main.c`**: Archivo principal que contiene la función principal del programa. Gestiona la lectura de la clave y la generación del state que es una matriz de 4x4, expande la clave para el cifrado, encripta el estado y guarda el resultado en un archivo de salida.
- **`AES128_Func.c`**: Archivo que contiene las funciones que implementadas por la función `Cypher` encargada de llevar a cabo la encriptación bajo el estandar AES128
- **`AES128_Func.h`**: Archivo de cabecera con las declaraciones de las funciones y variables utilizadas en el proceso de encriptación.
- **`Doxyfile`**: Archivo de configuración para generar la documentación.
- **`MainPage.dox`**: Archivo con el contenido de la pagina principal.
  

## Instrucciones de Uso

1. **Preparación:**
   - Asegúrate de tener los archivos de entrada adecuados (`key.txt` y `text.txt`).
   - El archivo `key.txt` debe contener la clave de 16 bytes en formato hexadecimal o ASCII.
   - El archivo `text.txt` debe contener el texto que se desea encriptar

2. **Compilación:**
   Ejecuta el siguiente comando en la carpeta de src:
   ```bash
   gcc main.c AES128_Func.c -o main.exe

3. **Ejecución:**
   En la carpeta de src ejecutar el siguiente comando:
   ```bash
   ./main.exe

4. **Tiempos de ejecución:**
   | Tamaño del archivo | Tiempo promediado (s) | Desviación estándar (s) | Valor minimo (s) | Valor máximo (s)
   | --- | --- | --- | --- | --- |
   | 1 Gb | 190.001 | 3.5848 | 187.439 | 203.292 |
   | 100 Mb | 19.28885 | 0.5747 | 18.262 | 20.67 |
   | 10 Mb  | 1.929 | 0.0578 | 1.808 | 2.046 |
   | 1 Mb   |       |    |    |    |

## Instrucciones para la generación de la documentación

1. En la carpeta `Lab_1` ejecutar el siguiente comando:
   ```bash
   doxygen Doxyfile
2. Se generará una carpeta con el nombre `html` en esta carpeta hay un archivo llamado `index.html` al abrir ese archivo se obtendrá la documentación en doxygen

:) 
