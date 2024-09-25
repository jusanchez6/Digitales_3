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




