#include <inttypes.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef AES_FUNC_H
#define AES_FUNC_H
    // Definición de variables globales
    #define AES_BLOCK_SIZE 16
    #define AES_KEY_SIZE 16

    uint8_t sbox[256];


    // Definición de las funciones

    // Funciones para generar S-box
    void generate_sbox(uint8_t* sbox);
    uint8_t gf_mult(uint8_t a, uint8_t b);
    uint8_t gf_mult_inverse(uint8_t x);
    uint8_t affine_transform(uint8_t x);


    void KeyExpansion(const uint8_t* key, uint8_t* roundKeys);
    void SubBytes(uint8_t* state);
    void ShiftRows(uint8_t* state);
    void MixColumns(uint8_t* state);
    void AddRoundKey(uint8_t* state, const uint8_t* roundKey);
    void AES_Encrypt(const uint8_t* message, const uint8_t* key, uint8_t* ciphertext);

#endif