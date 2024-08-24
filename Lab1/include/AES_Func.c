#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>
#include "AES_Func.h"

#define get_sbox_value(num) (sbox[num])         // Funcion diabolica que retorna el valor de la s-box en la posición num

uint32_t w[44]; // Arreglo de 44 palabras de 32 bits

static const uint8_t sbox[256] = {
  //0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
  0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
  0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
  0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
  0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
  0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
  0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
  0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
  0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
  0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
  0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
  0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
  0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
  0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
  0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
  0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
  0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 
};

// Constantes de ronda
static const uint8_t Rcon[10] = {
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36
};

static uint8_t xtime (uint8_t x) {
    // Funcion de multiplicacion en GF(2^8) que le robe a un gringo marica en internet
    return ((x<<1) ^ (((x>>7) & 1) * 0x1b));
}

static uint32_t RotWord (uint32_t word) {
    return (word << 8)|(word >> 24);
}

static uint32_t SubWord (uint32_t word) {
    uint8_t *bytes = (uint8_t *)&word;
    for (int i = 0; i < 4; i++)
    {
        bytes[i]= sbox[bytes[i]];
    }
    
    return word;

}

static uint8_t getHex(uint8_t c){
    int rtVal;
        if(c >= '0' && c <= '9') {
            rtVal = c - '0';
        } else {
            rtVal = c - 'a' + 10;
        }
    return rtVal;
}

void print_state(state_t* state) {
    uint8_t i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            printf("%02X ", (*state)[i][j]);
        }
        printf("\n");
    }
}

void subBytes(state_t* state) {
    uint8_t i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            (*state)[j][i] = get_sbox_value((*state)[j][i]);
        }
    }
}

void MixColumns (state_t* state) {
   uint8_t i, t, temp, tm;


    for (i = 0; i < 4; i++) {
        t = (*state)[i][0];                                                         //Guardo el valor de la primera fila de la columa i
        temp = (*state)[i][0] ^ (*state)[i][1] ^ (*state)[i][2] ^ (*state)[i][3];   // Xor sobre todas las posiciones de la columna (Para simplificar el calculo)

        // Cambio de cada posicion de la columna 
        // Primera posicion de la columna
        tm = (*state)[i][0] ^ (*state)[0][1];       // Tm hace el calculo de 0x02*a2 XOR 0x03*a3
        tm = xtime(tm);                             // Multiplica Tm por 2
        (*state)[i][0] ^= tm ^ temp;

        // Segunda posicion de la columna
        tm = (*state)[i][1] ^ (*state)[0][2];       
        tm = xtime(tm);                             
        (*state)[i][1] ^= tm ^ temp; 

        // tercera posicion de la colimna
        tm = (*state)[i][2] ^ (*state)[0][3];       
        tm = xtime(tm);                             
        (*state)[i][2] ^= tm ^ temp;

        // cuarta posicion de la columna
        tm = (*state)[i][3] ^ t;
        tm = xtime(tm);
        (*state)[i][3] ^= tm ^ temp;
        
    }
}

void ShiftRows(state_t* state){
    uint8_t i, j;
    uint8_t row[4];
    for (int i=0; i<4;i++){
        for (int j=0; j<4 ; j++){
            row[j]=(*state)[i][(j+i)% 4];
        }
        for (int j=0; j<4;j++){
            (*state)[i][j]=row[j];
        }
    }
}

void AddRoundKey(uint8_t round, state_t* state, uint8_t* RoundKey){
    int i, j;
    for (i = 0; i < 4; i++){
        for (j = 0; j < 4; j++){
            (*state)[i][j] ^= RoundKey[(round* 4 * Nb)+(i + Nb) + j];
        }
    }
}

void KeyExpansion (const uint8_t* key, uint8_t* RoundKey) {
    int i, j, k;
    

    uint8_t temp[4];    // Variable temporal para las operaciones columna/fila

    // Copia de la clave original en las primeras Nk palabras de la clave expandida
    for (i = 0; i < Nk; i++) {
        RoundKey[(i*4) + 0] = key[(i*4) + 0];
        RoundKey[(i*4) + 1] = key[(i*4) + 1];
        RoundKey[(i*4) + 2] = key[(i*4) + 2];
        RoundKey[(i*4) + 3] = key[(i*4) + 3];
    }

    // Generación de las claves de ronda
    for (i = Nk; i < Nb*(Nr+1); i++) {
        

        k = (i-1)*4;
        temp[0] = RoundKey[k + 0];
        temp[1] = RoundKey[k + 1];
        temp[2] = RoundKey[k + 2];
        temp[3] = RoundKey[k + 3];

        if (i % Nk == 0) {

            // RotWord
            uint8_t temp2 = temp[0];
            temp[0] = temp[1];
            temp[1] = temp[2];
            temp[2] = temp[3];
            temp[3] = temp2;

            // SubWord
            temp[0] = get_sbox_value(temp[0]);
            temp[1] = get_sbox_value(temp[1]);
            temp[2] = get_sbox_value(temp[2]);
            temp[3] = get_sbox_value(temp[3]);

            // Rcon
            temp[0] = temp[0] ^ Rcon[i/Nk];
        }
        
        // Clave de ronda y actualización de RoundKey
        j = i * 4;
        k = (i - Nk) * 4;

        RoundKey[j + 0] = RoundKey[k + 0] ^ temp[0];
        RoundKey[j + 1] = RoundKey[k + 1] ^ temp[1];
        RoundKey[j + 2] = RoundKey[k + 2] ^ temp[2];
        RoundKey[j + 3] = RoundKey[k + 3] ^ temp[3];

    }

}

void AES128_Encrypt(state_t* state, uint8_t* key){
    int round = 0;
    AddRoundKey(round, state, key);
    for (round = 1; round < Nr; round++){
        subBytes(state);
        ShiftRows(state);
        MixColumns(state);
        AddRoundKey(round, state, key);
    }
    subBytes(state);
    ShiftRows(state);
    AddRoundKey(round, state, key);
}

void readKey(uint8_t* key, bool way){
    //if way is true, the txt is written in hex
    //if false, it is written in ascii
    FILE *filePointer = NULL; //pointer to file
    uint8_t val, c;
    uint8_t i=0;

    // open the file to be read, in read mode "r"
    filePointer = fopen("../TextFiles/key.txt", "r");

    //leer de a caracter y pasar a ascii
    while ((c = fgetc(filePointer)) != 0XFF){
        //print the character to a string
        if(way){
            key[i]=16*getHex(c)+getHex(fgetc(filePointer));
        }
        else{
            key[i]=c;
        }
        i++;

    }
    fclose(filePointer);
    filePointer = NULL; //soltar el espacio
}

void writeState(state_t* state){
    FILE *fptr;
    fptr = fopen("../TextFiles/encripted.txt", "a");
    // Write some text to the file
    for (int i=0;i<4;i++){
        for (int j=0; j<4;j++){
            fprintf(fptr, "%c",(*state)[i][j]);
        }
    }
    // Close the file
    fclose(fptr);
}

void readState(state_t* state,uint32_t* round,bool*flag){
    FILE *fptr;
    uint8_t i=0;
    uint8_t c;
    fptr = fopen("../TextFiles/text.txt", "r");
    fseek(fptr,16*(*round),0);
    // Write some text to the file
    while ((c=fgetc(fptr)) != 0xFF && i<16){
        (*state)[i%4][i-(i%4)*4]=c;
        i++;
    }
    if(i==0){*flag=true;}
    while (i<16 && i!=0){
        (*state)[i%4][i-(i%4)*4]=0xFF;
        i++;
    }
    // Close the file
    fclose(fptr);
    (*round)++;
}

void eraseEncripted(){
    //como se abre en escribir, se borra lo anterior
    fclose(fopen("../TextFiles/encripted.txt", "w"));
}
