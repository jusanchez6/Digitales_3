#include <inttypes.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef AES_FUNC_H
#define AES_FUNC_H
    // Definición de variables globales
    #define AES_BLOCK_SIZE 16       // Tamaño del bloque de AES 128
    #define AES_KEY_SIZE 16         // 16bytes = 128 bits

    #define AES128_keyExpSize 176              // Tamaño de la clave expandida
    // 16 bytes por cada clave
    #define Nb 4
    #define Nk 4     // Número de columnas de la clave
    #define Nr 10    // Número de rondas de cifrado

    uint8_t RoundKey[AES128_keyExpSize];        // Clave expandida de 176 bytes
                                            // 16 bytes por cada ronda

    typedef uint8_t state_t[4][4];  // Definición del tipo de variable de state para AES

    // definición de la estructura que almacena la clave expandida
    
    //struct AES_ctx {    //clave expandida de 176 bytes
    //    uint8_t RoundKey[AES128_keyExpSize]; //16 bytes por ronda
    //};

    void print_state(state_t* state);
    void subBytes(state_t* state);
    void MixColumns (state_t* state);
    void ShiftRows(state_t* state); 
    void AddRoundKey(uint8_t round, state_t* state, uint8_t* RoundKey);

    void KeyExpansion (const uint8_t* key, uint8_t* RoundKey);
    void AES128_Encrypt(state_t* state, uint8_t* key);

    void readKey(uint8_t* key,bool way);
    void writeState(state_t* state);
    void eraseEncripted();

    void readState(state_t* state,uint32_t* round, bool*flag);

#endif