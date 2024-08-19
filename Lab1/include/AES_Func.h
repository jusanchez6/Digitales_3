#include <inttypes.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef AES_FUNC_H
#define AES_FUNC_H
    // Definición de variables globales
    #define AES_BLOCK_SIZE 16       // Tamaño del bloque de AES 128
    #define AES_KEY_SIZE 16         // 16bytes = 128 bits
    #define AES_KeyExpSize 176      // Tamaño de la clave expandida

    typedef uint8_t state_t[4][4];  // Definición del tipo de variable de state para AES

    // definición de la estructura que almacena la clave expandida
    struct AES_ctx {
        uint8_t RoundKey[AES_KeyExpSize];
    };

    void print_state(state_t* state);
    void subBytes(state_t* state);
    void MixColumns (state_t* state);
    void ShiftRows(state_t* state); 

#endif