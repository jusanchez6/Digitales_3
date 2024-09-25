/**
 * @file ADC.c
 * 
 * @brief Hardware library for the RP2350 ADC module.
 * @details This file contains the functions for the ADC module of the RP2350 board.
 * @author Julian Mauricio Sanchez Ceballos
 * @version 1.0
 * @date 24/9/2024
 * @copyright Unlicensed
 * 
 * This header file declarates the data types, constants, macros, and the module structure
 * for controlling the memory mapped register for the RP2350 ADC module. The defined data 
 * structures follow a standard naming notation.
 * 
 * The naming notation is as follows:
 * 
 * MODULE STRUCTURE                 ==>   s + MODULEname + [MODULEnumber]
 * MMIO REGISTER                    ==>   r + MODULEname + [MODULEnumber] + _ + REGISTERname + [REGISTERnumber]
 * MMIO REGISTER ATOMIC WRITE XOR   ==>   xor + MODULEname + [MODULEnumber] + _ + REGISTERname + [REGISTERnumber]
 * MMIO REGISTER ATOMIC WRITE SET   ==>   set + MODULEname + [MODULEnumber] + _ + REGISTERname + [REGISTERnumber]
 * MMIO REGISTER ATOMIC WRITE CLR   ==>   clr + MODULEname + [MODULEnumber] + _ + REGISTERname + [REGISTERnumber]
 * REGISTER BITFIELD or BIT         ==>   b + MODULEname + [MODULEnumber] + _ + BITFIELDname
 * BITFIELD CONTANT VALUEs          ==>   k + MODULEname + _ + BITFIELDname + _ + CONSTANTname
 * MODULE MASKs                     ==>   m + MODULEname + _ + MASKname
 * REGISTER TYPE                    ==>   __ + MODULEname + _ + REGISTERname + _t
 * STRUCTURE TYPE                   ==>   __ + MODULEname + _ + _t
 * 
 * The structure of this file is as follows:
 * 
 * 1. Register definition
 *    a. Data type
 *    b. Register masks
 *    c. Bitifield constant values
 * 2. Module structure definition
 *    a. Data type
 *    b. Module masks
 *    c. Structure access macro
 * 3. Register access macros
 *    a. Whole register access macro
 *    b. Bitfields access macro
 * 
 * 
 * 
 */

#ifndef __ADC_H_
#define __ADC_H_

#include <stdint.h>

/**
 * \addtogroup ADC rp2350 ADC module
 * ADC module for the RP2350 board.
 * 
 * @{
 * \brief Hardware library for the RP2350 ADC module.
 */


/**
 * \addtogroup ADC_CS ADC Control and Status Register
 * Type definition, constants and macros associatesd to the ADC Control and Status Register.
 * @{
 * \brief ADC Control and Status Register
 */

/**
 * \typedef __ADC_CS_t
 * typedef for ADC Control and Status Register.
 */
typedef union {
    uint32_t WORD; /**< Whole register */
    struct BITS{
        uint32_t ADCEN              : 1; /**< ADC Enable */
        uint32_t ADCTS_EN           : 1; /**< POWER TEMPERATURE SENSOR */
        uint32_t ADC_START_ONCE     : 1; /**< SINGLE CONVERSION */
        uint32_t ADC_START_MANY     : 1; /**< MANY CONVERSIONS */
        uint32_t RESERVE            : 4; /**< Reserved */
        uint32_t ADC_Ready          : 1; /**< ADC Ready */
        uint32_t ADC_ERR            : 1; /**< ADC Error */
        uint32_t ADC_STICKY         : 1; /**< ADC Sticky Error */
        uint32_t RESERVED           : 1; /**< Reserved */
        uint32_t ADC_AINSEL         : 4; /**< ADC Channel Select */
        uint32_t ADC_RROBIN         : 9; /**< ADC Round Robin */
        uint32_t                    : 7; /**< Reserved */
    } BITS; /**< Bitfield structure */

} __ADC_CS_t;

/**
 * Mask for the ADC Control and Status Register.
 */
#define mADC_CS_ADCEN           (0x00000001) /**< ADC Enable */
#define mADC_CS_ADCTS_EN        (0x00000002) /**< POWER TEMPERATURE SENSOR */
#define mADC_CS_ADC_START_ONCE  (0x00000004) /**< SINGLE CONVERSION */
#define mADC_CS_ADC_START_MANY  (0x00000008) /**< MANY CONVERSIONS */
#define mADC_CS_ADC_Ready       (0x00000080) /**< ADC Ready */
#define mADC_CS_ADC_ERR         (0x00000100) /**< ADC Error */
#define mADC_CS_ADC_STICKY      (0x00000200) /**< ADC Sticky Error */
#define mADC_CS_ADC_AINSEL      (0x0000F000) /**< ADC Channel Select */
#define mADC_CS_ADC_RROBIN      (0x1FF00000) /**< ADC Round Robin */

/**
 * Constants for the ADC Control and Status Register.
 */
#define kADC_CS_ADCEN           (0x00000001) /**< ADC Enable */
#define kADC_CS_ADCDIS          (0x00000000) /**< ADC Disable */
#define kADC_CS_ADCTS_EN        (0x00000002) /**< POWER TEMPERATURE SENSOR */
#define kADC_CS_ADCTS_DIS       (0x00000000) /**< POWER TEMPERATURE SENSOR */
#define kADC_CS_ADC_START_ONCE  (0x00000004) /**< SINGLE CONVERSION */
#define kADC_CS_ADC_START_MANY  (0x00000008) /**< MANY CONVERSIONS */
#define kADC_CS_ADC_STYCKY_CLR  (0x00000200) /**< ADC Sticky Error Clear */


/**
 * @}
 */






#endif // __ADC_H_
