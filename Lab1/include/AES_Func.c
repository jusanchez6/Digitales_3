#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>
#include "AES_Func.h"


uint8_t gf_mult (uint8_t a, uint8_t b) {
    uint8_t product = 0;                    //Inicializa el producto como 0  

    if (b & 1) {
        product = a;                        //Si el bit menos significativo de b es 1, suma a al producto
    }
    if (a & 0x80) {
        a = (a << 1) ^ 0x1b;                //Si el bit más significativo de a es 1, desplaza a a la izquierda y reduce con el polinomio irreducible
    } else {
        a <<= 1;                            //Desplaza a a la izquierda sin reducción
    }
    b >>= 1;                                //Desplaza b a la derecha para el siguiente bit

    return product;                         //Retorna el producto final en GF(2^8)
}

uint8_t gf_mult_inverse (uint8_t x) {
    // Calcula el inverso multiplicativo en GF(2^8) usando la propiedad:
    // x * x^(254) = 1 en GF(2^8), excepto para 0.

    if (x == 0) return 0;                       // El inverso multiplicativo de 0 no existe

    uint8_t inv = 1;                            // Inicializar el inverso
    for (int i = 0; i < 254; i++) {             // Multiplicar 254 veces para encontrar el inverso
        inv = gf_mult(inv, x);                  // Multiplicar el inverso por x
    }
}

uint8_t affine_transform(uint8_t x) {
    // Obtiene la transformada afin del valor inverso (b)
    // b = b_0 ^ b_i+4 ^ b_i+5 ^ b_i+6 ^ b_i+7 ^ C_i

    uint8_t output = 0;
    // Recorrido de los bits de x
    for (int i = 0; i < 8; i++) {
        // Extracción de los bits
        uint8_t b_i = (x >> i) & 0x01;
        uint8_t b_i_4 = (x >> ((i + 4) % 8)) & 0x01;
        uint8_t b_i_5 = (x >> ((i + 5) % 8)) & 0x01;
        uint8_t b_i_6 = (x >> ((i + 6) % 8)) & 0x01;
        uint8_t b_i_7 = (x >> ((i + 7) % 8)) & 0x01;
        uint8_t C_i = (0x63 >> i) & 0x01;

        // Aplicación de la transformada afin
        output |= ((b_i ^ b_i_4 ^ b_i_5 ^ b_i_6 ^ b_i_7 ^ C_i) << i);
    }
    return output;
}

void generate_sbox(uint8_t* sbox) {
    // Genera la S-box para el cifrado AES
    
    for (int i = 0; i < 256; i++) {
        // Inicializa la S-box con los valores de 0 a 255
        uint8_t inv = gf_mult_inverse(i);       // Calcula el inverso multiplicativo de i

        sbox[i] = affine_transform(inv);        // Aplica la transformada afin al inverso multiplicativo
    }
    
}

void sub_bytes(uint8_t* state, const uint8_t* sbox) {
    // Substituye cada byte del estado por el valor correspondiente en la S-box
    
    for (int i = 0; i < 16; i++) {
        state[i] = sbox[state[i]];               // Substituye el byte por el valor en la S-box
    }
}

