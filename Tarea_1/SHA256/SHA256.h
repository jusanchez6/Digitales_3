/**
 * \file SHA256_LIB.h 
 * \brief Hardware library for RP2350 SHA-256 implementation
 * \details ...
 * \author      Maria del Mar Arbelaez
 * \version     0.0.1
 * \date        07/10/2024
 * \copyright   Unlicensed
 * 
 * 
 * This header file declarates the data types, constants, macros, and the module structure
 * for controlling the memory mapped register for the SHA-256 module. The defined data 
 * structures follow a standard naming notation.
 * 
 * The naming notation is as follows:
 * 
 * REGISTER TYPE             ==>   __ +  MODULEname + _ + REGISTERname + _t
 * STRUCTURE TYPE            ==>   __ +  MODULEname + _ + _t
 * 
 * Notación para constantes y máscaras de bits y campos de bits
 * BITFIELD CONTANT VALUEs   ==>   k +   MODULEname + _ + BITFIELDname {+ _ +REGISTERname} + _ + CONSTANTname
 * MODULE MASKs              ==>   m +   MODULEname + _ + BITFIELDname {+ _ +REGISTERname}
 * 
 * Notación para macros de acceso corto
 * MODULE STRUCTURE          ==>   s +   MODULEname + [MODULEnumber]
 * MMIO REGISTER             ==>   r +   MODULEname + [MODULEnumber] + _ + REGISTERname + [REGISTERnumber]
 * REGISTER BITFIELD or BIT  ==>   b +   MODULEname + [MODULEnumber] + _ + BITFIELDname {+ _ +REGISTERname + [REGISTERnumber]}
 * 
 * The structure of this file is as follows:
 * 
 * 1. Declaración de la unión para cada registro del modulo
 *   a. Tipo de dato para el registro utilizando unión y estructura de bits
 *   b. Mascaras para cada bit y campo de bit en el registro
 *   c. Macros de valores constantes que pueden tomar los campos de bits
 * 2. Declaración de la estructura del modulo
 *   a. Tipo de dato del módulo completo utilizando una estructura
 *   b. Macro de acceso a estructura para cada módulo del tipo seleccionado
 * 3. Declaración de macros para acceso corto a registros y campos de bits
 *   a. Macros de acceso corto a registros
 *   b. Macros de acceso corto a bits y campos de bits
 * 
 */

#ifndef __SHA256_LIB_
#define __SHA256_LIB_
#include <stdint.h>

/**
 * \addtogroup SHA-256 RP2350 MODULE
 * SHA-256 groups all register of the module, typedefs, macros, etc.
 * @{
 * \brief The RP2350 SHA256 module produces a fixed-size result, called a hash,
 * when digesting a stream of data, called a message.
*/

/**
 * \addtogroup SHA256_CSR SHA-256 CONTROL AND STATUS REGISTER
 * Typedef, constants and macros associated to the SHA256_CSR register
 * @{
 * \brief Control and status register for the SHA256 module.
*/

/**
 * \typedef __SHA256_CSR_t
 * Type definition for control and status register
*/
typedef union{
    uint32_t WORD;
    struct BITS{
        uint32_t START              :1; //SC, if 1, prepares for new checksum
        uint32_t WDATA_RDY          :1; //RO, is write data ready to write?
        uint32_t SUM_VLD            :1; //RO, is the sum valid?
        uint32_t                    :1; //reserved
        uint32_t ERR_WDATA_NOT_RDY  :1; //W2C 
        uint32_t                    :3; //reserved
        uint32_t DMA_SIZE           :2; //RW, configure for correct DMA size
        uint32_t                    :2; //reserved
        uint32_t BSWAP              :1; //RW, enable byte swapping
        uint32_t                    :19;//reserved
    } BITS;
} __SHA256_CSR_t;

/**
 * Mask definition for SHA256 CSR register
 */
#define mSHA256_START               0x00000001
#define mSHA256_WDATA_RDY           0x00000002
#define mSHA256_SUM_VLD             0x00000004
#define mSHA256_ERR_WDATA_NOT_RDY   0x00000010
#define mSHA256_DMA_SIZE            0x00000003<<8
#define mSHA256_BSWAP               0x00000001<<12

/**
 * Constant definition for SHA256 CSR register
 */

#define kSHA256_START                            1
#define kSHA256_mSHA256_ERR_WDATA_NOT_RDY_CLEAR  1
#define kSHA256_mSHA256_DMA_SIZE_8BIT            0
#define kSHA256_mSHA256_DMA_SIZE_16BIT           1
#define kSHA256_mSHA256_DMA_SIZE_32BIT           2
#define kSHA256_mSHA256_BSWAP_enable             1
#define kSHA256_mSHA256_BSWAP_disable            0
/**@} */

/**
 * \typedef __SHA256_t
 */

typedef struct{
    volatile __SHA256_CSR_t CSR;    //Control and status register
    volatile uint32_t       WDATA;  //Write Data register
    volatile uint32_t       SUM0;   //256-BIT checksum result
    volatile uint32_t       SUM1;   //256-BIT checksum result
    volatile uint32_t       SUM2;   //256-BIT checksum result
    volatile uint32_t       SUM3;   //256-BIT checksum result
    volatile uint32_t       SUM4;   //256-BIT checksum result
    volatile uint32_t       SUM5;   //256-BIT checksum result
    volatile uint32_t       SUM6;   //256-BIT checksum result
    volatile uint32_t       SUM7;   //256-BIT checksum result

}__SHA256_t;

#define sSHA256 (*((__SHA256_t *)( 0x400f8000)))       ///< Normal RW access struct for BUS FABRIC CONTROL module
//dunno if it has other accesses

/**
 * \addtogroup SHA256_CSR
 * @{
 */
#define rSHA256_CSR                 sSHA256.CSR.WORD
#define bSHA256_START               sSHA256.CSR.BITS.START
#define bSHA256_WDATA_RDY           sSHA256.CSR.BITS.WDATA_RDY
#define bSHA256_SUM_VLD             sSHA256.CSR.BITS.SUM_VLD
#define bSHA256_ERR_WDATA_NOT_RDY   sSHA256.CSR.BITS.ERR_WDATA_NOT_RDY
#define bSHA256_DMA_SIZE            sSHA256.CSR.BITS.DMA_SIZE
#define bSHA256_BSWAP               sSHA256.CSR.BITS.BSWAP
/**@} */

/**
 * \addtogroup SHA256 EXTRA REGISTERS
 * @{
 */
#define rSHA256_WDATA               sSHA256.WDATA
#define rSHA256_SUM0                sSHA256.SUM0
#define rSHA256_SUM1                sSHA256.SUM1
#define rSHA256_SUM2                sSHA256.SUM2
#define rSHA256_SUM3                sSHA256.SUM3
#define rSHA256_SUM4                sSHA256.SUM4
#define rSHA256_SUM5                sSHA256.SUM5
#define rSHA256_SUM6                sSHA256.SUM6
#define rSHA256_SUM7                sSHA256.SUM7

/**@} */
/**@} */

#endif