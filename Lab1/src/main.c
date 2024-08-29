/**
 * @file main.c
 * @brief Archivo principal para el cifrado AES
 * @details Este archivo contiene la función principal que lee la clave, el estado y la ronda desde los archivos de texto, 
 * y encripta el estado utilizando la clave. El resultado se escribe en el archivo encripted.txt.
 * 
 * @authors Maria Del Mar Arbelaez, Julian Sanchez
 * @date 2024-08-27
 * @version 1.0
 * 
 */

#include <stdio.h>
#include <time.h>
#include "../include/AES_Func.h"

/**
 * @brief Función principal para encriptar datos usando AES-128.
 * 
 * Esta función realiza la encriptación de datos mediante el algoritmo AES-128. El proceso
 * incluye la expansión de la clave, lectura y encriptación del estado, y escritura del estado
 * encriptado. La función mide el tiempo total de ejecución del proceso.
 * 
 * - Inicializa la clave expandida y otras variables necesarias.
 * - Lee la clave desde una fuente externa y realiza la expansión de clave.
 * - En un bucle, lee el estado, encripta los datos usando AES-128 si el estado no está completo,
 *   y escribe el estado encriptado.
 * - Finalmente, imprime el tiempo total de ejecución en segundos.
 * 
 * @note La función utiliza las siguientes funciones auxiliares:
 *       - `readKey`: Para leer la clave desde una fuente externa.
 *       - `eraseEncripted`: Para borrar cualquier dato encriptado previo.
 *       - `KeyExpansion`: Para generar la clave expandida a partir de la clave original.
 *       - `readState`: Para leer el estado a ser encriptado.
 *       - `AES128_Encrypt`: Para encriptar el estado usando la clave expandida.
 *       - `writeState`: Para escribir el estado encriptado en una salida.
 * 
 * @return Retorna 0 al finalizar la ejecución.
 */
int main (void) {
	FILE *fptr_read,*fptr_write;
	time_t start, end;
	uint8_t RoundKey[AES128_keyExpSize];        // Clave expandida de 176 bytes
	bool flag=false;
	state_t state;
	uint8_t key[16];
	char path_read[]="../TextFiles/text_10M.txt";
	char path_write[]="../TextFiles/encripted.txt";
	char path_key[]="../TextFiles/key.txt";

    printf("Todos los paths deben llevar a TextFiles.\n Ingrese el path de read, write y key separados por espacios.\n");
	//ESTO FUNCIONA, pero no me gusta :(
	scanf("%s %s %s",path_read,path_write,path_key);
	start = time(NULL);
	openFiles(&path_read[0],&path_write[0],&fptr_read,&fptr_write);
	readKey(&key[0],&path_key[0],false); //true for hex, false for chars
	KeyExpansion(&key[0],&RoundKey[0]);
	while (!flag){
		readState(&state,&flag,false,&fptr_read); //true for hex, false for chars
		if(!flag){
			//AES128_Encrypt(&state,&RoundKey[0]);
			writeState(&state, false, &fptr_write); //true for hex, false for chars
		}
	}
	closeFiles(&fptr_read,&fptr_write);
	end = time(NULL);
	printf("Time taken to run is %f seconds", difftime(end, start));
}