/** Principal program for AES encryption and decryption
 *  @file AES.c
 *  @date 14/8/2024
 *  @authors: Maria Del Mar Arbelaez Sandoval
 *  @authors: Julian Mauricio Sanchez Ceballos
 *  @brief This program encrypts and decrypts a message using the AES algorithm.
*/



#include <stdio.h>
#include "../include/AES_Func.h"

uint8_t sbox[256];

int main (void) {
	// generación de la s-box
	generate_sbox(sbox);


	// expandir clave
	
	return 0;
}