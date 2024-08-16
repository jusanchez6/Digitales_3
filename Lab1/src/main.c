/** Principal program for AES encryption and decryption
 *  @file AES.c
 *  @date 14/8/2024
 *  @authors: Maria Del Mar Arbelaez Sandoval
 *  @authors: Julian Mauricio Sanchez Ceballos
 *  @brief This program encrypts and decrypts a message using the AES algorithm.
*/



#include <stdio.h>
#include "../include/AES_Func.h"


int main (void) {
	// generación de la s-box
	generate_sbox(sbox);

	// Imprimir la S-box generada
	printf("S-box:\n");
	for (int i = 0; i < 256; i++) {
		printf("%02x ", sbox[i]);
		if ((i + 1) % 16 == 0) {
			printf("\n");
		}
	}

	return 0;
}