/**
 * @file AES_Func.h
 * @brief Archivo cabecera para el cifrado AES
 * @details Este archivo contiene las definiciones de las funciones y variables necesarias para
 * la implementación del cifrado AES-128. Incluye la definición de tipos de datos, variables globales,
 * y prototipos de funciones necesarias para el cifrado en AES.
 * 
 * @authors Maria Del Mar Arbelaez, Julian Sanchez
 * @date 2024-08-27
 * @version 1.0
 * 
 */


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

    /**
     * @brief Clave expandida de 176 bytes (16 bytes por cada ronda).
     * 
     * Esta variable externa representa la clave expandida para AES-128, la cual tiene una longitud
     * total de 176 bytes. Está definida en el archivo de implementación y es utilizada en la
     * encriptación y desencriptación de datos. La clave expandida se genera a partir de la clave
     * original de 16 bytes (128 bits) mediante el proceso de expansión de clave.
    */
    extern uint8_t RoundKey[AES128_keyExpSize]; 

    /**
     * @brief Tipo de dato para el estado en AES.
     * 
     * Este tipo de dato representa el estado de 4x4 bytes utilizado en el algoritmo de cifrado
     * AES-128. La matriz `state_t` es una matriz bidimensional de bytes (uint8_t), donde cada elemento
     * corresponde a un byte del estado en el proceso de encriptación o desencriptación.
     * 
     * @note La matriz de estado se manipula en la implementación del algoritmo de cifrado AES-128.
    */
    typedef uint8_t state_t[4][4];  
    
    void print_state(state_t* state);
    void subBytes(state_t* state);
    void MixColumns (state_t* state);
    void ShiftRows(state_t* state); 
    void AddRoundKey(uint8_t round, state_t* state, uint8_t* RoundKey);

    void KeyExpansion (const uint8_t* key, uint8_t* RoundKey);
    void AES128_Encrypt(state_t* state, uint8_t* Roundkey);

    void readKey(uint8_t* key,char* pathkey, bool way);

    void openFiles(char* file_name_read, FILE **fptr_read,FILE **fptr_write);
    void readState(state_t* state, bool*flag, bool hex, FILE **fptr);
    void writeState(state_t* state, bool hex,FILE **fptr);
    void closeFiles(FILE **fptr_read,FILE **fptr_write);

#endif