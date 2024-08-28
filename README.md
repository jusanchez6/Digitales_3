# Digitales_3
# Laboratorio 1: Implementación de Cifrado AES-128

## Descripción

Este proyecto implementa el algoritmo de cifrado AES-128 en lenguaje C. El objetivo es cifrar datos utilizando el estándar AES (Advanced Encryption Standard) para garantizar la confidencialidad de la información. El proyecto incluye la expansión de la clave, el cifrado del estado y la gestión de archivos para la entrada y salida de datos.

## Contenidos

- **`main.c`**: Archivo principal que contiene la función principal del programa. Gestiona la lectura de la clave y la generación del state que es una matriz de 4x4, expande la clave para el cifrado, encripta el estado y guarda el resultado en un archivo de salida.
- **`AES128_Func.c`**: Archivo que contiene las funciones que implementadas por la función `Cypher` encargada de llevar a cabo la encriptación bajo el estandar AES128
- **`AES128_Func.h`**: Archivo de cabecera con las declaraciones de las funciones y variables utilizadas en el proceso de encriptación.


## Instrucciones de Uso

1. **Preparación:**
   - Asegúrate de tener los archivos de entrada adecuados (`key.txt` y `state.txt`).
   - El archivo `key.txt` debe contener la clave de 16 bytes en formato hexadecimal o ASCII.

2. **Compilación:**
   Ejecuta el siguiente comando para compilar el proyecto:
   ```bash
   gcc -o aes128 main.c 
