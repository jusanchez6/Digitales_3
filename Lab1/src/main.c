/** Principal program for AES encryption and decryption
 *  @file AES.c
 *  @date 14/8/2024
 *  @authors: Maria Del Mar Arbelaez Sandoval
 *  @authors: Julian Mauricio Sanchez Ceballos
 *  @brief This program encrypts and decrypts a message using the AES algorithm.
*/

#include <stdio.h>
#include "../include/AES_Func.h"

/*
Algorithm 1 Pseudocode for CIPHER()
1: procedure CIPHER(in, Nr, w)
	2: state ← in
	3: state ← ADDROUNDKEY(state,w[0..3])
	4: for round from 1 to Nr −1 do
		5: state ← SUBBYTES(state)
		6: state ← SHIFTROWS(state)
		7: state ← MIXCOLUMNS(state)
		8: state ← ADDROUNDKEY(state,w[4 ∗ round..4 ∗ round +3])
	9: end for
	10: state ← SUBBYTES(state)
	11: state ← SHIFTROWS(state)
	12: state ← ADDROUNDKEY(state,w[4 ∗Nr..4 ∗Nr +3])
	13: return state
	14: end procedure 
*/

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