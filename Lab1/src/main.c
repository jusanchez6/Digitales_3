/** Principal program for AES encryption and decryption
 *  @file AES.c
 *  @date 14/8/2024
 *  @authors: Maria Del Mar Arbelaez Sandoval
 *  @authors: Julian Mauricio Sanchez Ceballos
 *  @brief This program encrypts and decrypts (haha lol no just encrypt) a message using the AES algorithm.
*/

#include <stdio.h>
#include "../include/AES_Func.h"

int main (void) {
	uint8_t RoundKey[AES128_keyExpSize];        // Clave expandida de 176 bytes
	uint32_t readRound=0;
	bool flag=false;
	state_t state;
	uint8_t key[16];

	readKey(&key[0],false); //true for hex, false for chars
	eraseEncripted();
	KeyExpansion(&key[0],&RoundKey[0]);
	while (!flag){
		readState(&state,&readRound,&flag);
		if(!flag){
			AES128_Encrypt(&state,&RoundKey[0]);
			//print_state(&state);
			writeState(&state);
		}
	}
}