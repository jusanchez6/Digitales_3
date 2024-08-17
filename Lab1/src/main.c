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
	state_t state = {
		{0x43, 0x53, 0x63, 0x73},
		{0x44, 0x54, 0x64, 0x74},
		{0x45, 0x55, 0x65, 0x75},
		{0x46, 0x56, 0x66, 0x76}
	};

	subBytes(&state);
	print_state(&state);

	return 0;
}