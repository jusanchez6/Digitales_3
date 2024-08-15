/** Principal program for AES encryption and decryption
 *  @file AES.c
 *  @date 14/8/2024
 *  @authors: Maria Del Mar Arbelaez Sandoval
 *  @authors: Julian Mauricio Sanchez Ceballos
 *  @brief This program encrypts and decrypts a message using the AES algorithm.
*/

#include <stdio.h>
#include <stdint.h>

#define AES_BLOCK_SIZE 16
#define AES_KEY_SIZE 16

// function prototypes for AES encryption and decryption
void KeyExpansion(const uint8_t* key, uint8_t *roundKeys);
void SubBytes(uint8_t *state);
void ShiftRows(uint8_t *state);
void MixColumns(uint8_t *state);
void AddRoundKey(uint8_t *state, const uint8_t *roundKey);
void AES_Encrypt(const uint8_t *message, const uint8_t *key, uint8_t *ciphertext);


int main (void) {
    return 0;
}