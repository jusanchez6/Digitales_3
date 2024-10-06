/**
 * \file        SHA256.h 
 * \brief       Hardware library for RP2350 SHA-256 implementation
 * \details     ...
 * \author      María del Mar Arbeláez
 * \version     0.0.1
 * \date        05/10/2024
 * \copyright   Unlicensed
 * 
 * 
 * \defgroup SHA256FILE SHA-256 File Structure
 * This header file declarates the data types, constants, macros, and the module structure
 * for controlling the memory mapped register for the SHA-256 module. 
 * @{
 *  The defined data structures follow a standard naming notation.
 *  The naming notation is as follows:
 * 
 * - REGISTER TYPE             ==>   __ +  MODULEname + _ + REGISTERname + _t
 * - STRUCTURE TYPE            ==>   __ +  MODULEname + _ + _t
 * 
 * Notation for constants, bit masks and bit fields:
 * - BITFIELD CONTANT VALUEs   ==>   k +   MODULEname + _ + BITFIELDname {+ _ +REGISTERname} + _ + CONSTANTname
 * - MODULE MASKs              ==>   m +   MODULEname + _ + BITFIELDname {+ _ +REGISTERname}
 * 
 * Notation for short-access macros:
 * - MODULE STRUCTURE          ==>   s +   MODULEname + [MODULEnumber]
 * - MMIO REGISTER             ==>   r +   MODULEname + [MODULEnumber] + _ + REGISTERname + [REGISTERnumber]
 * - REGISTER BITFIELD or BIT  ==>   b +   MODULEname + [MODULEnumber] + _ + BITFIELDname {+ _ +REGISTERname + [REGISTERnumber]}
 * 
 * The structure of this file is as follows:
 * 1. Union declaration for each register of the module:
 *      - Data type for the register using a union and a bit struct.
 *      - A mask for each bit and bit field of the register.
 *      - Constant valued macros for the values that bits or bitfields may take.
 * 2. Module Struct declaration:
 *      - Data type for the complete module using a struct:
 *      - Macro for struct access for each module of the selected type.
 * 3. Macro declaration for register and bitfield short-access:
 *      - Short access macro for registers.
 *      - Short access macro for bits and bit fields.
 * @}
 */

#ifndef __SHA256_LIB_
#define __SHA256_LIB_
#include <stdint.h>

/**
 * \defgroup SHA256 SHA-256 RP2350 Module
 * SHA-256 groups all register of the module, typedefs, macros, etc.
 * @{
 * \brief The RP2350 SHA256 module produces a fixed-size result, called a hash,
 * when digesting a stream of data, called a message.
 * 
*/

/**
 * \addtogroup SHA256_CSR SHA-256 Control and Status Register
 * Typedef, constants and macros associated to the SHA256_CSR register
 * @{
 * \brief Control and status register for the SHA-256 module.
*/

/**
 * \typedef __SHA256_CSR_t
 * Type definition for control and status register
*/
typedef union{
    uint32_t WORD;                      ///< Whole register access
    struct BITS{
        uint32_t START              :1; ///<SC, if 1, prepares for new checksum
        uint32_t WDATA_RDY          :1; ///<RO, is write data ready to write?
        uint32_t SUM_VLD            :1; ///<RO, is the sum valid?
        uint32_t                    :1; ///<Reserved bit.
        uint32_t ERR_WDATA_NOT_RDY  :1; ///<W2C, 1 if data is not ready. 
        uint32_t                    :3; ///<Reserved bitfield.
        uint32_t DMA_SIZE           :2; ///<RW, configure for correct DMA size.
        uint32_t                    :2; ///<Reserved bitfield.
        uint32_t BSWAP              :1; ///<RW, enable for byte swapping.
        uint32_t                    :19;///<Reserved bitfield.
    } BITS;
} __SHA256_CSR_t;

/**
 * Mask definition for SHA256 CSR register
 */
#define mSHA256_START               0x00000001      /*!<Start mask.*/
#define mSHA256_WDATA_RDY           0x00000002      /*!<Write Data Ready mask.*/
#define mSHA256_SUM_VLD             0x00000004      /*!<Sum Valid mask.*/
#define mSHA256_ERR_WDATA_NOT_RDY   0x00000010      /*!<Error Data Not Ready mask.*/
#define mSHA256_DMA_SIZE            0x00000003<<8   /*!<DMA Size mask.*/
#define mSHA256_BSWAP               0x00000001<<12  /*!<Byte Swap mask.*/

/**
 * Constant definition for SHA256 CSR register
 */

#define kSHA256_START                            1  /*!<Start constant.*/
#define kSHA256_mSHA256_ERR_WDATA_NOT_RDY_CLEAR  1  /*!<Clear Error Data Not Ready Register.*/
#define kSHA256_mSHA256_DMA_SIZE_8BIT            0  /*!<Set 8bit DMA.*/
#define kSHA256_mSHA256_DMA_SIZE_16BIT           1  /*!<Set 16bit DMA.*/
#define kSHA256_mSHA256_DMA_SIZE_32BIT           2  /*!<Set 32bit DMA.*/
#define kSHA256_mSHA256_BSWAP_enable             1  /*!<Enable Byte Swappping.*/
#define kSHA256_mSHA256_BSWAP_disable            0  /*!<Disable Byte Swapping.*/
/**@} */

/**
 * \typedef __SHA256_t
 */

typedef struct{
    volatile __SHA256_CSR_t CSR;    /*!<Control and Status register.*/
    volatile uint32_t       WDATA;  /*!<Write Data register.*/
    volatile uint32_t       SUM0;   /*!<256-BIT checksum result.*/
    volatile uint32_t       SUM1;   /*!<256-BIT checksum result.*/
    volatile uint32_t       SUM2;   /*!<256-BIT checksum result.*/
    volatile uint32_t       SUM3;   /*!<256-BIT checksum result.*/
    volatile uint32_t       SUM4;   /*!<256-BIT checksum result.*/
    volatile uint32_t       SUM5;   /*!<256-BIT checksum result.*/
    volatile uint32_t       SUM6;   /*!<256-BIT checksum result.*/
    volatile uint32_t       SUM7;   /*!<256-BIT checksum result.*/

}__SHA256_t;

#define sSHA256 (*((__SHA256_t *)( 0x400f8000)))       /*!< Normal RW access struct for SHA-256 module.*/
#define sSHA256_XOR (*((__SHA256_t *)( 0x400f9000)))   /*!< Atomic XOR WO access struct for SHA-256 module.*/
#define sSHA256_SET (*((__SHA256_t *)( 0x400fa000)))   /*!< Atomic SET WO access struct for SHA-256 module.*/
#define sSHA256_CLR (*((__SHA256_t *)( 0x400fb000)))   /*!< Atomic CLEAR WO access struct for SHA-256 module.*/

/**
 * \addtogroup SHA256_CSR_ACC SHA256_CSR Access Macros
 * Normal, XOR, SET and CLEAR access MACROS for the SHA256_CSR register.
 * @{
 * @brief Access MACROS for the SHA256_CSR register.
 */
#define rSHA256_CSR                   sSHA256.CSR.WORD                      /*!<CSR Register Normal RWAccess Macro.*/
#define bSHA256_START                 sSHA256.CSR.BITS.START                /*!<Start Normal RW Access Macro.*/
#define bSHA256_WDATA_RDY             sSHA256.CSR.BITS.WDATA_RDY            /*!<Write Data Ready Normal RW Access Macro.*/
#define bSHA256_SUM_VLD               sSHA256.CSR.BITS.SUM_VLD              /*!<Sum Valid Normal RW Access Macro.*/
#define bSHA256_ERR_WDATA_NOT_RDY     sSHA256.CSR.BITS.ERR_WDATA_NOT_RDY    /*!<Error Data Not Ready Normal RW Access Macro.*/
#define bSHA256_DMA_SIZE              sSHA256.CSR.BITS.DMA_SIZE             /*!<DMA Size Normal RW Access Macro.*/
#define bSHA256_BSWAP                 sSHA256.CSR.BITS.BSWAP                /*!<Byte Swap Normal RW Access Macro.*/

#define xorSHA256_DMA_SIZE            sSHA256_XOR.CSR.WORD = mSHA256_DMA_SIZE  /*!<DMA Size XOR WO Access Macro.*/
#define xorSHA256_BSWAP               sSHA256_XOR.CSR.WORD = mSHA256_BSWAP     /*!<Byte Swap XOR WO Access Macro.*/

#define setSHA256_START               sSHA256_SET.CSR.WORD = mSHA256_START              /*!<Start SET WO Access Macro.*/
#define setSHA256_ERR_WDATA_NOT_RDY   sSHA256_SET.CSR.WORD = mSHA256_ERR_WDATA_NOT_RDY  /*!<Error Data Not Ready SET WO Access Macro.*/
#define setSHA256_DMA_SIZE            sSHA256_SET.CSR.WORD = mSHA256_DMA_SIZE           /*!<DMA Size SET WO Access Macro.*/
#define setSHA256_BSWAP               sSHA256_SET.CSR.WORD = mSHA256_BSWAP              /*!<Byte Swap SET W0 Access Macro.*/

#define clrSHA256_DMA_SIZE            sSHA256_CLR.CSR.WORD = mSHA256_DMA_SIZE   /*!<DMA Size CLR WO Access Macro.*/
#define clrSHA256_BSWAP               sSHA256_CLR.CSR.WORD = mSHA256_BSWAP      /*!<Byte Swap CLR WO Access Macro.*/
/**@} */

/**
 * \addtogroup SHA256_EXTRA_ACC SHA-256 Remaining Register Macros
 * Normal, XOR, SET and CLEAR access MACROS for the WDATA and SUMX registers, accordingly.
 * @{
 *  \brief MACROS for the WDATA and SHA256_SUMX registers.
 */
#define rSHA256_WDATA               sSHA256.WDATA  /*!<Write Data register.*/
#define rSHA256_SUM0                sSHA256.SUM0   /*!<256-BIT checksum result.*/
#define rSHA256_SUM1                sSHA256.SUM1   /*!<256-BIT checksum result.*/
#define rSHA256_SUM2                sSHA256.SUM2   /*!<256-BIT checksum result.*/
#define rSHA256_SUM3                sSHA256.SUM3   /*!<256-BIT checksum result.*/
#define rSHA256_SUM4                sSHA256.SUM4   /*!<256-BIT checksum result.*/
#define rSHA256_SUM5                sSHA256.SUM5   /*!<256-BIT checksum result.*/
#define rSHA256_SUM6                sSHA256.SUM6   /*!<256-BIT checksum result.*/
#define rSHA256_SUM7                sSHA256.SUM7   /*!<256-BIT checksum result.*/

#define xorSHA256_WDATA             sSHA256_XOR.WDATA /*!<XOR access for Write Data register.*/
#define setSHA256_WDATA             sSHA256_SET.WDATA /*!<SET access for Write Data register.*/
#define clrSHA256_WDATA             sSHA256_CLR.WDATA /*!<CLR access for Write Data register.*/

/**@} */
/**@} */


#endif