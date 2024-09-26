/**
 * @file ADC.H
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
 * \addtogroup ADC RP2350 ADC module
 * ADC module for the RP2350 board.
 * 
 * @{
 * \brief Hardware library for the RP2350 ADC module.
 */


/**
 * \addtogroup __ADC_CS ADC Control and Status Register
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
        uint32_t ADC_EN             : 1; /**< ADC Enable */
        uint32_t ADCTS_EN           : 1; /**< POWER TEMPERATURE SENSOR */
        uint32_t ADC_START_ONCE     : 1; /**< SINGLE CONVERSION */
        uint32_t ADC_START_MANY     : 1; /**< MANY CONVERSIONS */
        uint32_t                    : 4; /**< Reserved */
        uint32_t ADC_Ready          : 1; /**< ADC Ready */
        uint32_t ADC_ERR            : 1; /**< ADC Error */
        uint32_t ADC_STICKY         : 1; /**< ADC Sticky Error */
        uint32_t                    : 1; /**< Reserved */
        uint32_t ADC_AINSEL         : 4; /**< ADC Channel Select */
        uint32_t ADC_RROBIN         : 9; /**< ADC Round Robin */
        uint32_t                    : 7; /**< Reserved */
    } BITS; /**< Bitfield structure */

} __ADC_CS_t;

/**
 * Mask for the ADC Control and Status Register.
 */
#define mADC_CS_ADC_EN              (0x00000001) /**< ADC Enable */
#define mADC_CS_ADCTS_EN            (0x00000002) /**< POWER TEMPERATURE SENSOR */
#define mADC_CS_ADC_START_ONCE      (0x00000004) /**< SINGLE CONVERSION */
#define mADC_CS_ADC_START_MANY      (0x00000008) /**< MANY CONVERSIONS */
#define mADC_CS_ADC_Ready           (0x00000100) /**< ADC Ready */
#define mADC_CS_ADC_ERR             (0x00000200) /**< ADC Error */
#define mADC_CS_ADC_STICKY          (0x00000400) /**< ADC Sticky Error */
#define mADC_CS_ADC_AINSEL          (0x0000F000) /**< ADC Channel Select */
#define mADC_CS_ADC_RROBIN          (0x01FF0000) /**< ADC Round Robin */

/**
 * Constants for the ADC Control and Status Register.
 */
#define kADC_CS_ADC_ENABLE                  (0x00000001) /**< ADC Enable */
#define kADC_CS_ADC_DISABLE                 (0x00000000) /**< ADC Disable */
#define kADC_CS_ADCTS_ENABLE                (0x00000002) /**< POWER TEMPERATURE SENSOR */
#define kADC_CS_ADCTS_DISABLE               (0x00000000) /**< POWER TEMPERATURE SENSOR */
#define kADC_CS_ADC_START_ONCE_SC           (0x00000004) /**< SINGLE CONVERSION SELF CLEANING*/
#define kADC_CS_ADC_START_MANY_CONTINUE     (0x00000008) /**< MANY CONVERSIONS CONTINUE*/
#define kADC_CS_ADC_STYCKY_CLR              (0x00000400) /**< ADC Sticky Error Clear */


/** * @} */


/**
 * \addtogroup __ADC_RESULT.  ADC_RESULT Register for the RP2350 ADC module
 * Typedef, constants, and macros associated with the ADC_RESULT register
 * @{
 * \brief Result register of the most recent the ADC module.
 */


/**
 * \typedef __ADC_RESULT_t
 * Type definition for [descripción del registro]
*/
typedef union{
    uint32_t WORD;                                  ///< Whole register access
    struct BITS{
        uint32_t ADC_RESULT              : 12;      ///< ADC Result
        uint32_t                         : 20;      ///< Reserved

    } BITS;
} __ADC_RESULT_t;

/**
 * Masks definition for __ADC_RESULT_t
*/
#define mADC_RESULT              (0x00000FFF)        ///< ADC Result

/**
 * Constants definition for __ADC_RESULT_t
*/

/** @} */


/**
 * \addtogroup __ADC_FCS_REGISTER. FCS Register for the RP2350 ADC module
 * Typedef, constants, and macros associated with the FCS_REGISTER register
 * @{
 * \brief FIFO Control and Status Register for the ADC module.
*/

/**
 * \typedef __ADC_FCS_REGISTER_t
 * Type definition for the FCS register
*/
typedef union{
    uint32_t WORD;                          ///< Whole register access
    struct BITS{
        uint32_t FCS_EN         : 1;    ///< FIFO Enable
        uint32_t FCS_SHIFT      : 1;    ///< FIFO Shift
        uint32_t FCS_ERR        : 1;    ///< FIFO Error
        uint32_t FCS_DREQ_EN    : 1;    ///< FIFO DMA Request Enable
        uint32_t                : 4;    ///< Reserved
        uint32_t FCS_EMPTY      : 1;    ///< FIFO Empty
        uint32_t FCS_FULL       : 1;    ///< FIFO Full
        uint32_t FCS_UNDER      : 1;    ///< FIFO Underflow
        uint32_t FCS_OVER       : 1;    ///< FIFO Overflow
        uint32_t                : 4;    ///< Reserved
        uint32_t FCS_LEVEL      : 4;    ///< FIFO Level
        uint32_t                : 4;    ///< Reserved
        uint32_t FCS_THRESH     : 4;    ///< FIFO Threshold
        uint32_t                : 4;    ///< Reserved
    } BITS;
} __ADC_FCS_REGISTER_t;

/**
 * Masks definition for __ADC_FCS_REGISTER_t
*/
#define mADC_FCS_EN                (0x00000001)        ///< FIFO Enable
#define mADC_FCS_SHIFT             (0x00000002)        ///< FIFO Shift
#define mADC_FCS_ERR               (0x00000004)        ///< FIFO Error
#define mADC_FCS_DREQ_EN           (0x00000008)        ///< FIFO DMA Request Enable
#define mADC_FCS_EMPTY             (0x00000100)        ///< FIFO Empty
#define mADC_FCS_FULL              (0x00000200)        ///< FIFO Full
#define mADC_FCS_UNDER             (0x00000400)        ///< FIFO Underflow
#define mADC_FCS_OVER              (0x00000800)        ///< FIFO Overflow
#define mADC_FCS_LEVEL             (0x000F0000)        ///< FIFO Level
#define mADC_FCS_THRESH            (0x0F000000)        ///< FIFO Threshold

/**
 * Constants definition for __ADC_FCS_REGISTER_t
*/
#define kADC_FCS_ENABLE                 (0x00000001)        ///< FIFO Enable
#define kADC_FCS_SHIFT_ENABLE           (0x00000002)        ///< FIFO Shift
#define kADC_FCS_ERR_ENABLE             (0x00000004)        ///< FIFO Error
#define kADC_FCS_DREQ_ASSERT            (0x00000008)        ///< FIFO DMA Request Enable
#define kADC_FCS_UNDER_CLEAR            (0x00000400)        ///< FIFO Underflow Clear
#define kADC_FCS_OVER_CLEAR             (0x00000800)        ///< FIFO Overflow Clear

/** @} */


/**
 * \addtogroup __ADC_FIFO_REGISTER. FIFO Register for the RP2350 ADC module
 * Typedef, constants, and macros associated with the ADC FIFO  register
 * @{
 * \brief Conversion result FIFO
*/

/**
 * \typedef __ADC_FIFO_REGISTER_t
 * Type definition for the FIFO register
*/
typedef union{
    uint32_t WORD;                          ///< Whole register access
    struct BITS{
        uint32_t FIFO_DATA      : 12;   ///< FIFO Data
        uint32_t                :  3;   ///< Reserved
        uint32_t FIFO_ERR       :  1;   ///< FIFO Error
        uint32_t                : 16;   ///< Reserved
    } BITS;
} __ADC_FIFO_REGISTER_t;

/**
 * Masks definition for __FIFO_REGISTER_t
*/
#define mFIFO_REGISTER_FIFO_DATA            (0x00000FFF)        ///< FIFO Data
#define mFIFO_REGISTER_FIFO_ERR             (0x00008000)        ///< FIFO Error


/**
 * Constants definition for __FIFO_REGISTER_t
*/

/** @} */


/**
 * \addtogroup __ADC_DIV_REGISTER. DIV Register for the RP2350 ADC module
 * Typedef, constants, and macros associated with the ADC DIV register
 * @{
 * \brief Clock divider. If non-zero, CS_START_MANY will start
 conversions at regular intervals rather than back-to-back.
 The divider is reset when either of these fields are written.
 Total period is 1 + INT + FRAC / 256

*/

/**
 * \typedef __ADC_DIV_REGISTER_t
 * Type definition for the DIV register
*/
typedef union{
    uint32_t WORD;                          ///< Whole register access
    struct BITS{
        uint32_t DIV_FRAC        :  8;   ///< Frac part of divider
        uint32_t DIV_INT         : 16;   ///< Int part of divider
        uint32_t                 :  8;   ///< Reserved
    } BITS;
} __ADC_DIV_REGISTER_t;

/**
 * Masks definition for __ADC_DIV_REGISTER_t
*/
#define mDIV_REGISTER_DIV_FRAC              (0x000000FF)        ///< Frac part of divider
#define mDIV_REGISTER_DIV_INT               (0x00FFFF00)        ///< Int part of divider

/**
 * Constants definition for __ADC_DIV_REGISTER_t
*/

/** @} */


/**
 * \addtogroup __ADC_INTR_REGISTER. INTR Register for the RP2350 ADC module
 * Typedef, constants, and macros associated with the ADC INTR register
 * @{
 * \brief Raw interrupt register for the ADC module
*/

/**
 * \typedef __ADC_INTR_REGISTER_t
 * Type definition for the INTR register
*/
typedef union{
    uint32_t WORD;                          ///< Whole register access
    struct BITS{
        uint32_t INTR_FIFO      :  1;   ///< FIFO interrupt
        uint32_t                : 31;   ///< Reserved
    } BITS;
} __ADC_INT_REGISTER_t;

/**
 * Masks definition for __ADC_INTR_REGISTER_t
*/
#define mINTR_REGISTER_INTR_FIFO             (0x00000001)        ///< FIFO interrupt

/**
 * Constants definition for __ADC_INTR_REGISTER_t
*/


/** @} */


/**
 * \addtogroup __ADC_INTE_REGISTER. INTE Register for the RP2350 ADC module
 * Typedef, constants, and macros associated with the ADC INTE register
 * @{
 * \brief Interrupt enable
*/

/**
 * \typedef __ADC_INTE_REGISTER_t
 * Type definition for [descripción del registro]
*/
typedef union{
    uint32_t WORD;                          ///< Whole register access
    struct BITS{
        uint32_t INTE_FIFO      :  1;   ///< FIFO interrupt enable
        uint32_t                : 31;   ///< Reserved
        
    } BITS;
} __ADC_INTE_REGISTER_t;

/**
 * Masks definition for __ADC_INTE_REGISTER_t
*/
#define mINTE_REGISTER_INTE_FIFO             (0x00000001)        ///< FIFO interrupt enable

/**
 * Constants definition for __ADC_INTE_REGISTER_t
*/

/** @} */


/**
 * \addtogroup __ADC_INTF_REGISTER. INTF Register for the RP2350 ADC module
 * Typedef, constants, and macros associated with the ADC INTF register
 * @{
 * \brief Interrupt force
*/

/**
 * \typedef __ADC_INTF_REGISTER_t
 * Type definition for INTF register
*/
typedef union{
    uint32_t WORD;                          ///< Whole register access
    struct BITS{
        uint32_t INTF_FIFO      :  1;   ///< FIFO interrupt force
        uint32_t                : 31;   ///< Reserved
    
    } BITS;
} __ADC_INTF_REGISTER_t;

/**
 * Masks definition for __ADC_INTF_REGISTER_t
*/
#define mINTF_REGISTER_INTF_FIFO             (0x00000001)        ///< FIFO interrupt force
/**
 * Constants definition for __ADC_INTF_REGISTER_t
*/

/** @} */

/**
 * \addtogroup __ADC_INTS_REGISTER. INTS Register for the RP2350 ADC module
 * Typedef, constants, and macros associated with the ADC INTS register
 * @{
 * \brief Interrupt status after masking and forcing
*/

/**
 * \typedef __ADC_INTS_REGISTER_t
 * Type definition for INTS register
*/
typedef union{
    uint32_t WORD;                          ///< Whole register access
    struct BITS{
        uint32_t INTS_FIFO      :  1;   ///< FIFO interrupt status
        uint32_t                : 31;   ///< Reserved
    } BITS;
} __ADC_INTS_REGISTER_t;

/**
 * Masks definition for __ADC_INTS_REGISTER_t
*/
#define mINTS_REGISTER_INTS_FIFO             (0x00000001)        ///< FIFO interrupt status

/**
 * Constants definition for __ADC_INTS_REGISTER_t
*/

/** @} */


/**
 * \typedef __ADC_t
 */
typedef struct {
    volatile __ADC_CS_t             CS_R;
    volatile __ADC_RESULT_t         RST_R;
    volatile __ADC_FCS_REGISTER_t   FCS_R;
    volatile __ADC_FIFO_REGISTER_t  FIFO_R;
    volatile __ADC_DIV_REGISTER_t   DIV_R;
    volatile __ADC_INT_REGISTER_t   INTR_R;
    volatile __ADC_INTE_REGISTER_t  INTE_R;
    volatile __ADC_INTF_REGISTER_t  INTF_R;
    volatile __ADC_INTS_REGISTER_t  INTS_R;
};

#define sADC        (*((__ADC_t *) (0x400a0000)))       ///< Normal RW access struct for ADC structure module
#define sADC_XOR    (*((__ADC_t *) (0x400a1000)))       ///< Atomic XOR access struct for ADC structure module
#define sADC_SET    (*((__ADC_t *) (0x400a2000)))       ///< Atomic SET access struct for ADC structure module
#define sADC_CLR    (*((__ADC_t *) (0x400a3000)))       ///< Atomic CLR access struct for ADC structure module


/**
 * \addtogroup Normal Access Macros
 * @{
 * \brief Normal access macros for the ADC module
 */

/**
 * \addtogroup __ADC_CS_REGISTER. CS Register for the RP2350 ADC module
 * @{
 * \brief Normal access for ADC Control and Status Register 
 */


#define rADC_CS                 (sADC.CS_R.WORD)                        ///< ADC Control and Status Register
#define bADC_CS_ADC_EN           (sADC.CS_R.BITS.ADC_EN)                ///< ADC Enable
#define bADC_CS_ADSCTS_EN       (sADC.CS_R.BITS.ADCTS_EN)               ///< POWER TEMPERATURE SENSOR
#define bADC_CS_ADC_START_ONCE  (sADC.CS_R.BITS.ADC_START_ONCE)         ///< SINGLE CONVERSION
#define bADC_CS_START_MANY      (sADC.CS_R.BITS.ADC_START_MANY)         ///< MANY CONVERSIONS
#define bADC_CS_ADC_Ready       (sADC.CS_R.BITS.ADC_Ready)              ///< ADC Ready
#define bADC_CS_ADC_ERR         (sADC.CS_R.BITS.ADC_ERR)                ///< ADC Error
#define bADC_CS_ADC_STICKY      (sADC.CS_R.BITS.ADC_STICKY)             ///< ADC Sticky Error
#define bADC_CS_ADC_AINSEL      (sADC.CS_R.BITS.ADC_AINSEL)             ///< ADC Channel Select
#define bADC_CS_ADC_RROBIN      (sADC.CS_R.BITS.ADC_RROBIN)             ///< ADC Round Robin

/**@} */

/**
 * \addtogroup __ADC_RESULT_REGISTER. RST Register for the RP2350 ADC module
 * @{
 * \brief Normal access for ADC Result Register
 */
#define rADC_RESULT (sADC.RST_R.WORD)                   ///< ADC Result Register
#define bADC_RESULT (sADC.RST_R.BITS.ADC_RESULT)        ///< ADC Result

/**@} */


/**
 * \addtogroup __ADC_FCS_REGISTER. FCS Register for the RP2350 ADC module
 * @{
 * \brief Normal access for ADC FIFO Control and Status Register
 */
#define rADC_FCS            (sADC.FCS_R.WORD)                   ///< FIFO Control and Status Register
#define bADC_FCS_EN         (sADC.FCS_R.BITS.FCS_EN)            ///< FIFO Enable
#define bADC_FCS_SHIFT      (sADC.FCS_R.BITS.FCS_SHIFT)         ///< FIFO Shift
#define bADC_FCS_ERR        (sADC.FCS_R.BITS.FCS_ERR)           ///< FIFO Error
#define bADC_FCS_DREQ_EN    (sADC.FCS_R.BITS.FCS_DREQ_EN)       ///< FIFO DMA Request Enable
#define bADC_FCS_EMPTY      (sADC.FCS_R.BITS.FCS_EMPTY)         ///< FIFO Empty
#define bADC_FCS_FULL       (sADC.FCS_R.BITS.FCS_FULL)          ///< FIFO Full
#define bADC_FCS_UNDER      (sADC.FCS_R.BITS.FCS_UNDER)         ///< FIFO Underflow
#define bADC_FCS_OVER       (sADC.FCS_R.BITS.FCS_OVER)          ///< FIFO Overflow
#define bADC_FCS_LEVEL      (sADC.FCS_R.BITS.FCS_LEVEL)         ///< FIFO Level
#define bADC_FCS_THRESH     (sADC.FCS_R.BITS.FCS_THRESH)        ///< FIFO Threshold

/**@} */


/**
 * \addtogroup __ADC_FIFO_REGISTER. FIFO Register for the RP2350 ADC module
 * @{
 * \brief Normal access for ADC FIFO Register 
 */
#define rADC_FIFO           (sADC.FIFO_R.WORD)                  ///< FIFO Data Register
#define bADC_FIFO_DATA      (sADC.FIFO_R.BITS.FIFO_DATA)        ///< FIFO Data
#define bADC_FIFO_ERR       (sADC.FIFO_R.BITS.FIFO_ERR)         ///< FIFO Error

/**@} */


/**
 * \addtogroup __ADC_DIV_REGISTER. DIV Register for the RP2350 ADC module
 * @{
 * \brief Normal access for ADC DIV Register
 */
#define rADC_DIV            (sADC.DIV_R.WORD)                   ///< Clock Divider Register
#define bADC_DIV_FRAC       (sADC.DIV_R.BITS.DIV_FRAC)          ///< Frac part of divider
#define bADC_DIV_INT        (sADC.DIV_R.BITS.DIV_INT)           ///< Int part of divider

/**@} */

/**
 * \addtogroup __ADC_INTR_REGISTER. INTR Register for the RP2350 ADC module
 * @{
 * \brief Normal access for ADC INTR Register
 */
#define rADC_INTR           (sADC.INTR_R.WORD)                  ///< Raw interrupt register
#define bADC_INTR_FIFO      (sADC.INTR_R.BITS.INTR_FIFO)        ///< FIFO interrupt

/**@} */

/**
 * \addtogroup __ADC_INTE_REGISTER. INTE Register for the RP2350 ADC module
 * @{
 * \brief Interrupt enable register
 */
#define rADC_INTE           (sADC.INTE_R.WORD)                  ///< Interrupt enable register
#define bADC_INTE_FIFO      (sADC.INTE_R.BITS.INTE_FIFO)        ///< FIFO interrupt enable

/**@} */

/**
 * \addtogroup __ADC_INTF_REGISTER. INTF Register for the RP2350 ADC module
 * @{
 * \brief Interrupt force register
 */
#define rADC_INTF           (sADC.INTF_R.WORD)                  ///< Interrupt force register
#define bADC_INTF_FIFO      (sADC.INTF_R.BITS.INTF_FIFO)        ///< FIFO interrupt force

/**@} */

/**
 * \addtogroup __ADC_INTS_REGISTER. INTS Register for the RP2350 ADC module
 * @{
 * \brief Interrupt status after masking and forcing
 */
#define rADC_INTS           (sADC.INTS_R.WORD)                  ///< Interrupt status after masking and forcing
#define bADC_INTS_FIFO      (sADC.INTS_R.BITS.INTS_FIFO)        ///< FIFO interrupt status

/**@} */

/** @} */

/** @} */

#endif // __ADC_H_
