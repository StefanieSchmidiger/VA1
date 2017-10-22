/*
** ###################################################################
**     Compilers:           Keil ARM C/C++ Compiler
**                          Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**
**     Reference manual:    MKE02Z64M20SF0RM, Rev.2.1, Apr-23 2013; KEAZ64RM, Rev.1, Sep 2013
**     Version:             rev. 1.8, 2015-10-14
**     Build:               b150207
**
**     Abstract:
**         This header file implements peripheral memory map for MKE02Z2
**         processor.
**
**     Copyright (c) 1997 - 2015 Freescale Semiconductor, Inc.
**     All Rights Reserved.
**
**     http:                 www.freescale.com
**     mail:                 support@freescale.com
**
**     Revisions:
**     - rev. 1.0 (2013-02-06)
**         Initial version.
**     - rev. 1.1 (2013-04-05)
**         Changed start of doxygen comment.
**     - rev. 1.2 (2013-05-07)
**         Update according to reference manual rev. 2.1.
**     - rev. 1.3 (2013-06-13)
**         Device types PTA,PTB,FPTA,FPTB changed to GPIOA,GPIOB,FGPIOA,FGPIOB.
**     - rev. 1.4 (2013-07-10)
**         FTM0,FTM1 - Removed registers CNTIN,STATUS,MODE,SYNC,OUTINIT,OUTMASK,COMBINE,DEADTIME,
              EXTTRIG,POL,FMS,FILTER,FLTCTRL,CONF,FLTPOL,SYNCONF,INVCTRL,SWOCTRL,PWMLOAD.
**         NV - DFPROT register renamed to EEPROT.
**         WDOG - Peripheral register layout structure has been extended with 16-bit access registers CNT, TOVAL, WIN.
**     - rev. 1.5 (2013-09-13)
**         ADC - Changed width of ADC Pin Control field from 32 to 16 bits.
**         I2C0 - Added bit SBRC into C2 register. Added bits STARTF,SSIE,STOPF,SHEN into FLT register.
**         PMC - Removed BGBDS bit from SPMSC1 register.
**         ROM - ROM module added.
**         SIM - Renamed bit PINSEL[IICPS] to I2C0PS, bit SCGC[IIC] to I2C.
**     - rev. 1.6 (2013-10-29)
**         Definition of BITBAND macros updated to support peripherals with 32-bit acces disabled.
**     - rev. 1.7 (2014-06-18)
**         NVIC - Added masks for individual bitfields of ISER,ICER,ISPR,ICPR registers.
**         SCB - Removed bitfields VECTACTIVE,ISRPENDING from ICSR register.
**     - rev. 1.8 (2015-10-14)
**         Renamed interrupt INT_Watchdog to INT_WDOG_EWM
**
** ###################################################################
*/

/*!
 * @file MKE02Z2.h
 * @version 1.8
 * @date 2015-10-14
 * @brief Peripheral memory map for MKE02Z2
 *
 * This header file implements peripheral memory map for MKE02Z2 processor.
 */


/* ----------------------------------------------------------------------------
   -- MCU activation
   ---------------------------------------------------------------------------- */

/* Prevention from multiple including the same memory map */
#if !defined(MCU_MKE02Z2) && !defined(MCU_MKE02Z4) && !defined(MCU_SKEAZN642)  /* Check if memory map has not been already included */
#define MCU_MKE02Z2
#define MCU_MKE02Z4
#define MCU_SKEAZN642

/* Check if another memory map has not been also included */
#if (defined(MCU_ACTIVE))
  #error MKE02Z2 memory map: There is already included another memory map. Only one memory map can be included.
#endif /* (defined(MCU_ACTIVE)) */
#define MCU_ACTIVE

#include <stdint.h>

/** Memory map major version (memory maps with equal major version number are
 * compatible) */
#define MCU_MEM_MAP_VERSION 0x0100u
/** Memory map minor version */
#define MCU_MEM_MAP_VERSION_MINOR 0x0008u


/* ----------------------------------------------------------------------------
   -- Interrupt vector numbers
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Interrupt_vector_numbers Interrupt vector numbers
 * @{
 */

/** Interrupt Number Definitions */
typedef enum {
  INT_Initial_Stack_Pointer    = 0,                /**< Initial Stack Pointer */
  INT_Initial_Program_Counter  = 1,                /**< Initial Program Counter */
  INT_NMI                      = 2,                /**< Non-maskable Interrupt (NMI) */
  INT_Hard_Fault               = 3,                /**< Hard Fault */
  INT_Reserved4                = 4,                /**< Reserved interrupt */
  INT_Reserved5                = 5,                /**< Reserved interrupt */
  INT_Reserved6                = 6,                /**< Reserved interrupt */
  INT_Reserved7                = 7,                /**< Reserved interrupt */
  INT_Reserved8                = 8,                /**< Reserved interrupt */
  INT_Reserved9                = 9,                /**< Reserved interrupt */
  INT_Reserved10               = 10,               /**< Reserved interrupt */
  INT_SVCall                   = 11,               /**< Supervisor call (SVCall) */
  INT_Reserved12               = 12,               /**< Reserved interrupt */
  INT_Reserved13               = 13,               /**< Reserved interrupt */
  INT_PendableSrvReq           = 14,               /**< Pendable request for system service (PendableSrvReq) */
  INT_SysTick                  = 15,               /**< System tick timer (SysTick) */
  INT_Reserved16               = 16,               /**< Reserved interrupt */
  INT_Reserved17               = 17,               /**< Reserved interrupt */
  INT_Reserved18               = 18,               /**< Reserved interrupt */
  INT_Reserved19               = 19,               /**< Reserved interrupt */
  INT_Reserved20               = 20,               /**< Reserved interrupt */
  INT_FTMRH                    = 21,               /**< FTMRH command complete and error interrupt */
  INT_LVD_LVW                  = 22,               /**< Low-voltage warning */
  INT_IRQ                      = 23,               /**< External interrupt */
  INT_I2C0                     = 24,               /**< I2C0 single interrupt vector for all sources */
  INT_Reserved25               = 25,               /**< Reserved interrupt */
  INT_SPI0                     = 26,               /**< SPI0 single interrupt vector for all sources */
  INT_SPI1                     = 27,               /**< SPI1 single interrupt vector for all sources */
  INT_UART0                    = 28,               /**< UART0 status and error */
  INT_UART1                    = 29,               /**< UART1 status and error */
  INT_UART2                    = 30,               /**< UART2 status and error */
  INT_ADC0                     = 31,               /**< ADC conversion complete interrupt */
  INT_ACMP0                    = 32,               /**< ACMP0 interrupt */
  INT_FTM0                     = 33,               /**< FTM0 single interrupt vector for all sources */
  INT_FTM1                     = 34,               /**< FTM1 single interrupt vector for all sources */
  INT_FTM2                     = 35,               /**< FTM2 single interrupt vector for all sources */
  INT_RTC                      = 36,               /**< RTC overflow */
  INT_ACMP1                    = 37,               /**< ACMP1 interrupt */
  INT_PIT_CH0                  = 38,               /**< PIT CH0 overflow */
  INT_PIT_CH1                  = 39,               /**< PIT CH1 overflow */
  INT_KBI0                     = 40,               /**< KBI0 interrupt */
  INT_KBI1                     = 41,               /**< KBI1 interrupt */
  INT_Reserved42               = 42,               /**< Reserved interrupt */
  INT_ICS                      = 43,               /**< Clock loss of lock */
  INT_WDOG_EWM                 = 44,               /**< Watchdog timeout */
  INT_Reserved45               = 45,               /**< Reserved interrupt */
  INT_Reserved46               = 46,               /**< Reserved interrupt */
  INT_Reserved47               = 47                /**< Reserved interrupt */
} IRQInterruptIndex;

/*!
 * @}
 */ /* end of group Interrupt_vector_numbers */


/* ----------------------------------------------------------------------------
   -- Peripheral type defines
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Peripheral_defines Peripheral type defines
 * @{
 */


/*
** Start of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #pragma push
  #pragma anon_unions
#elif defined(__CWCC__)
  #pragma push
  #pragma cpp_extensions on
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=extended
#else
  #error Not supported compiler type
#endif

/* ----------------------------------------------------------------------------
   -- ACMP
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ACMP_Peripheral ACMP
 * @{
 */

/** ACMP - Peripheral register structure */
typedef struct ACMP_MemMap {
  uint8_t CS;                                      /**< ACMP Control and Status Register, offset: 0x0 */
  uint8_t C0;                                      /**< ACMP Control Register 0, offset: 0x1 */
  uint8_t C1;                                      /**< ACMP Control Register 1, offset: 0x2 */
  uint8_t C2;                                      /**< ACMP Control Register 2, offset: 0x3 */
} volatile *ACMP_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- ACMP - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ACMP_Register_Accessor_Macros ACMP - Register accessor macros
 * @{
 */


/* ACMP - Register accessors */
#define ACMP_CS_REG(base)                        ((base)->CS)
#define ACMP_C0_REG(base)                        ((base)->C0)
#define ACMP_C1_REG(base)                        ((base)->C1)
#define ACMP_C2_REG(base)                        ((base)->C2)

/*!
 * @}
 */ /* end of group ACMP_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- ACMP Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ACMP_Register_Masks ACMP Register Masks
 * @{
 */

/* CS Bit Fields */
#define ACMP_CS_ACMOD_MASK                       0x3u
#define ACMP_CS_ACMOD_SHIFT                      0
#define ACMP_CS_ACMOD_WIDTH                      2
#define ACMP_CS_ACMOD(x)                         (((uint8_t)(((uint8_t)(x))<<ACMP_CS_ACMOD_SHIFT))&ACMP_CS_ACMOD_MASK)
#define ACMP_CS_ACOPE_MASK                       0x4u
#define ACMP_CS_ACOPE_SHIFT                      2
#define ACMP_CS_ACOPE_WIDTH                      1
#define ACMP_CS_ACOPE(x)                         (((uint8_t)(((uint8_t)(x))<<ACMP_CS_ACOPE_SHIFT))&ACMP_CS_ACOPE_MASK)
#define ACMP_CS_ACO_MASK                         0x8u
#define ACMP_CS_ACO_SHIFT                        3
#define ACMP_CS_ACO_WIDTH                        1
#define ACMP_CS_ACO(x)                           (((uint8_t)(((uint8_t)(x))<<ACMP_CS_ACO_SHIFT))&ACMP_CS_ACO_MASK)
#define ACMP_CS_ACIE_MASK                        0x10u
#define ACMP_CS_ACIE_SHIFT                       4
#define ACMP_CS_ACIE_WIDTH                       1
#define ACMP_CS_ACIE(x)                          (((uint8_t)(((uint8_t)(x))<<ACMP_CS_ACIE_SHIFT))&ACMP_CS_ACIE_MASK)
#define ACMP_CS_ACF_MASK                         0x20u
#define ACMP_CS_ACF_SHIFT                        5
#define ACMP_CS_ACF_WIDTH                        1
#define ACMP_CS_ACF(x)                           (((uint8_t)(((uint8_t)(x))<<ACMP_CS_ACF_SHIFT))&ACMP_CS_ACF_MASK)
#define ACMP_CS_HYST_MASK                        0x40u
#define ACMP_CS_HYST_SHIFT                       6
#define ACMP_CS_HYST_WIDTH                       1
#define ACMP_CS_HYST(x)                          (((uint8_t)(((uint8_t)(x))<<ACMP_CS_HYST_SHIFT))&ACMP_CS_HYST_MASK)
#define ACMP_CS_ACE_MASK                         0x80u
#define ACMP_CS_ACE_SHIFT                        7
#define ACMP_CS_ACE_WIDTH                        1
#define ACMP_CS_ACE(x)                           (((uint8_t)(((uint8_t)(x))<<ACMP_CS_ACE_SHIFT))&ACMP_CS_ACE_MASK)
/* C0 Bit Fields */
#define ACMP_C0_ACNSEL_MASK                      0x3u
#define ACMP_C0_ACNSEL_SHIFT                     0
#define ACMP_C0_ACNSEL_WIDTH                     2
#define ACMP_C0_ACNSEL(x)                        (((uint8_t)(((uint8_t)(x))<<ACMP_C0_ACNSEL_SHIFT))&ACMP_C0_ACNSEL_MASK)
#define ACMP_C0_ACPSEL_MASK                      0x30u
#define ACMP_C0_ACPSEL_SHIFT                     4
#define ACMP_C0_ACPSEL_WIDTH                     2
#define ACMP_C0_ACPSEL(x)                        (((uint8_t)(((uint8_t)(x))<<ACMP_C0_ACPSEL_SHIFT))&ACMP_C0_ACPSEL_MASK)
/* C1 Bit Fields */
#define ACMP_C1_DACVAL_MASK                      0x3Fu
#define ACMP_C1_DACVAL_SHIFT                     0
#define ACMP_C1_DACVAL_WIDTH                     6
#define ACMP_C1_DACVAL(x)                        (((uint8_t)(((uint8_t)(x))<<ACMP_C1_DACVAL_SHIFT))&ACMP_C1_DACVAL_MASK)
#define ACMP_C1_DACREF_MASK                      0x40u
#define ACMP_C1_DACREF_SHIFT                     6
#define ACMP_C1_DACREF_WIDTH                     1
#define ACMP_C1_DACREF(x)                        (((uint8_t)(((uint8_t)(x))<<ACMP_C1_DACREF_SHIFT))&ACMP_C1_DACREF_MASK)
#define ACMP_C1_DACEN_MASK                       0x80u
#define ACMP_C1_DACEN_SHIFT                      7
#define ACMP_C1_DACEN_WIDTH                      1
#define ACMP_C1_DACEN(x)                         (((uint8_t)(((uint8_t)(x))<<ACMP_C1_DACEN_SHIFT))&ACMP_C1_DACEN_MASK)
/* C2 Bit Fields */
#define ACMP_C2_ACIPE_MASK                       0x7u
#define ACMP_C2_ACIPE_SHIFT                      0
#define ACMP_C2_ACIPE_WIDTH                      3
#define ACMP_C2_ACIPE(x)                         (((uint8_t)(((uint8_t)(x))<<ACMP_C2_ACIPE_SHIFT))&ACMP_C2_ACIPE_MASK)

/*!
 * @}
 */ /* end of group ACMP_Register_Masks */


/* ACMP - Peripheral instance base addresses */
/** Peripheral ACMP0 base pointer */
#define ACMP0_BASE_PTR                           ((ACMP_MemMapPtr)0x40073000u)
/** Peripheral ACMP1 base pointer */
#define ACMP1_BASE_PTR                           ((ACMP_MemMapPtr)0x40074000u)
/** Array initializer of ACMP peripheral base pointers */
#define ACMP_BASE_PTRS                           { ACMP0_BASE_PTR, ACMP1_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- ACMP - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ACMP_Register_Accessor_Macros ACMP - Register accessor macros
 * @{
 */


/* ACMP - Register instance definitions */
/* ACMP0 */
#define ACMP0_CS                                 ACMP_CS_REG(ACMP0_BASE_PTR)
#define ACMP0_C0                                 ACMP_C0_REG(ACMP0_BASE_PTR)
#define ACMP0_C1                                 ACMP_C1_REG(ACMP0_BASE_PTR)
#define ACMP0_C2                                 ACMP_C2_REG(ACMP0_BASE_PTR)
/* ACMP1 */
#define ACMP1_CS                                 ACMP_CS_REG(ACMP1_BASE_PTR)
#define ACMP1_C0                                 ACMP_C0_REG(ACMP1_BASE_PTR)
#define ACMP1_C1                                 ACMP_C1_REG(ACMP1_BASE_PTR)
#define ACMP1_C2                                 ACMP_C2_REG(ACMP1_BASE_PTR)

/*!
 * @}
 */ /* end of group ACMP_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group ACMP_Peripheral */


/* ----------------------------------------------------------------------------
   -- ADC
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Peripheral ADC
 * @{
 */

/** ADC - Peripheral register structure */
typedef struct ADC_MemMap {
  uint32_t SC1;                                    /**< Status and Control Register 1, offset: 0x0 */
  uint32_t SC2;                                    /**< Status and Control Register 2, offset: 0x4 */
  uint32_t SC3;                                    /**< Status and Control Register 3, offset: 0x8 */
  uint32_t SC4;                                    /**< Status and Control Register 4, offset: 0xC */
  uint32_t R;                                      /**< Conversion Result Register, offset: 0x10 */
  uint32_t CV;                                     /**< Compare Value Register, offset: 0x14 */
  uint32_t APCTL1;                                 /**< Pin Control 1 Register, offset: 0x18 */
} volatile *ADC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- ADC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Register_Accessor_Macros ADC - Register accessor macros
 * @{
 */


/* ADC - Register accessors */
#define ADC_SC1_REG(base)                        ((base)->SC1)
#define ADC_SC2_REG(base)                        ((base)->SC2)
#define ADC_SC3_REG(base)                        ((base)->SC3)
#define ADC_SC4_REG(base)                        ((base)->SC4)
#define ADC_R_REG(base)                          ((base)->R)
#define ADC_CV_REG(base)                         ((base)->CV)
#define ADC_APCTL1_REG(base)                     ((base)->APCTL1)

/*!
 * @}
 */ /* end of group ADC_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- ADC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Register_Masks ADC Register Masks
 * @{
 */

/* SC1 Bit Fields */
#define ADC_SC1_ADCH_MASK                        0x1Fu
#define ADC_SC1_ADCH_SHIFT                       0
#define ADC_SC1_ADCH_WIDTH                       5
#define ADC_SC1_ADCH(x)                          (((uint32_t)(((uint32_t)(x))<<ADC_SC1_ADCH_SHIFT))&ADC_SC1_ADCH_MASK)
#define ADC_SC1_ADCO_MASK                        0x20u
#define ADC_SC1_ADCO_SHIFT                       5
#define ADC_SC1_ADCO_WIDTH                       1
#define ADC_SC1_ADCO(x)                          (((uint32_t)(((uint32_t)(x))<<ADC_SC1_ADCO_SHIFT))&ADC_SC1_ADCO_MASK)
#define ADC_SC1_AIEN_MASK                        0x40u
#define ADC_SC1_AIEN_SHIFT                       6
#define ADC_SC1_AIEN_WIDTH                       1
#define ADC_SC1_AIEN(x)                          (((uint32_t)(((uint32_t)(x))<<ADC_SC1_AIEN_SHIFT))&ADC_SC1_AIEN_MASK)
#define ADC_SC1_COCO_MASK                        0x80u
#define ADC_SC1_COCO_SHIFT                       7
#define ADC_SC1_COCO_WIDTH                       1
#define ADC_SC1_COCO(x)                          (((uint32_t)(((uint32_t)(x))<<ADC_SC1_COCO_SHIFT))&ADC_SC1_COCO_MASK)
/* SC2 Bit Fields */
#define ADC_SC2_REFSEL_MASK                      0x3u
#define ADC_SC2_REFSEL_SHIFT                     0
#define ADC_SC2_REFSEL_WIDTH                     2
#define ADC_SC2_REFSEL(x)                        (((uint32_t)(((uint32_t)(x))<<ADC_SC2_REFSEL_SHIFT))&ADC_SC2_REFSEL_MASK)
#define ADC_SC2_FFULL_MASK                       0x4u
#define ADC_SC2_FFULL_SHIFT                      2
#define ADC_SC2_FFULL_WIDTH                      1
#define ADC_SC2_FFULL(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_SC2_FFULL_SHIFT))&ADC_SC2_FFULL_MASK)
#define ADC_SC2_FEMPTY_MASK                      0x8u
#define ADC_SC2_FEMPTY_SHIFT                     3
#define ADC_SC2_FEMPTY_WIDTH                     1
#define ADC_SC2_FEMPTY(x)                        (((uint32_t)(((uint32_t)(x))<<ADC_SC2_FEMPTY_SHIFT))&ADC_SC2_FEMPTY_MASK)
#define ADC_SC2_ACFGT_MASK                       0x10u
#define ADC_SC2_ACFGT_SHIFT                      4
#define ADC_SC2_ACFGT_WIDTH                      1
#define ADC_SC2_ACFGT(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_SC2_ACFGT_SHIFT))&ADC_SC2_ACFGT_MASK)
#define ADC_SC2_ACFE_MASK                        0x20u
#define ADC_SC2_ACFE_SHIFT                       5
#define ADC_SC2_ACFE_WIDTH                       1
#define ADC_SC2_ACFE(x)                          (((uint32_t)(((uint32_t)(x))<<ADC_SC2_ACFE_SHIFT))&ADC_SC2_ACFE_MASK)
#define ADC_SC2_ADTRG_MASK                       0x40u
#define ADC_SC2_ADTRG_SHIFT                      6
#define ADC_SC2_ADTRG_WIDTH                      1
#define ADC_SC2_ADTRG(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_SC2_ADTRG_SHIFT))&ADC_SC2_ADTRG_MASK)
#define ADC_SC2_ADACT_MASK                       0x80u
#define ADC_SC2_ADACT_SHIFT                      7
#define ADC_SC2_ADACT_WIDTH                      1
#define ADC_SC2_ADACT(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_SC2_ADACT_SHIFT))&ADC_SC2_ADACT_MASK)
/* SC3 Bit Fields */
#define ADC_SC3_ADICLK_MASK                      0x3u
#define ADC_SC3_ADICLK_SHIFT                     0
#define ADC_SC3_ADICLK_WIDTH                     2
#define ADC_SC3_ADICLK(x)                        (((uint32_t)(((uint32_t)(x))<<ADC_SC3_ADICLK_SHIFT))&ADC_SC3_ADICLK_MASK)
#define ADC_SC3_MODE_MASK                        0xCu
#define ADC_SC3_MODE_SHIFT                       2
#define ADC_SC3_MODE_WIDTH                       2
#define ADC_SC3_MODE(x)                          (((uint32_t)(((uint32_t)(x))<<ADC_SC3_MODE_SHIFT))&ADC_SC3_MODE_MASK)
#define ADC_SC3_ADLSMP_MASK                      0x10u
#define ADC_SC3_ADLSMP_SHIFT                     4
#define ADC_SC3_ADLSMP_WIDTH                     1
#define ADC_SC3_ADLSMP(x)                        (((uint32_t)(((uint32_t)(x))<<ADC_SC3_ADLSMP_SHIFT))&ADC_SC3_ADLSMP_MASK)
#define ADC_SC3_ADIV_MASK                        0x60u
#define ADC_SC3_ADIV_SHIFT                       5
#define ADC_SC3_ADIV_WIDTH                       2
#define ADC_SC3_ADIV(x)                          (((uint32_t)(((uint32_t)(x))<<ADC_SC3_ADIV_SHIFT))&ADC_SC3_ADIV_MASK)
#define ADC_SC3_ADLPC_MASK                       0x80u
#define ADC_SC3_ADLPC_SHIFT                      7
#define ADC_SC3_ADLPC_WIDTH                      1
#define ADC_SC3_ADLPC(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_SC3_ADLPC_SHIFT))&ADC_SC3_ADLPC_MASK)
/* SC4 Bit Fields */
#define ADC_SC4_AFDEP_MASK                       0x7u
#define ADC_SC4_AFDEP_SHIFT                      0
#define ADC_SC4_AFDEP_WIDTH                      3
#define ADC_SC4_AFDEP(x)                         (((uint32_t)(((uint32_t)(x))<<ADC_SC4_AFDEP_SHIFT))&ADC_SC4_AFDEP_MASK)
#define ADC_SC4_ACFSEL_MASK                      0x20u
#define ADC_SC4_ACFSEL_SHIFT                     5
#define ADC_SC4_ACFSEL_WIDTH                     1
#define ADC_SC4_ACFSEL(x)                        (((uint32_t)(((uint32_t)(x))<<ADC_SC4_ACFSEL_SHIFT))&ADC_SC4_ACFSEL_MASK)
#define ADC_SC4_ASCANE_MASK                      0x40u
#define ADC_SC4_ASCANE_SHIFT                     6
#define ADC_SC4_ASCANE_WIDTH                     1
#define ADC_SC4_ASCANE(x)                        (((uint32_t)(((uint32_t)(x))<<ADC_SC4_ASCANE_SHIFT))&ADC_SC4_ASCANE_MASK)
/* R Bit Fields */
#define ADC_R_ADR_MASK                           0xFFFu
#define ADC_R_ADR_SHIFT                          0
#define ADC_R_ADR_WIDTH                          12
#define ADC_R_ADR(x)                             (((uint32_t)(((uint32_t)(x))<<ADC_R_ADR_SHIFT))&ADC_R_ADR_MASK)
/* CV Bit Fields */
#define ADC_CV_CV_MASK                           0xFFFu
#define ADC_CV_CV_SHIFT                          0
#define ADC_CV_CV_WIDTH                          12
#define ADC_CV_CV(x)                             (((uint32_t)(((uint32_t)(x))<<ADC_CV_CV_SHIFT))&ADC_CV_CV_MASK)
/* APCTL1 Bit Fields */
#define ADC_APCTL1_ADPC_MASK                     0xFFFFu
#define ADC_APCTL1_ADPC_SHIFT                    0
#define ADC_APCTL1_ADPC_WIDTH                    16
#define ADC_APCTL1_ADPC(x)                       (((uint32_t)(((uint32_t)(x))<<ADC_APCTL1_ADPC_SHIFT))&ADC_APCTL1_ADPC_MASK)

/*!
 * @}
 */ /* end of group ADC_Register_Masks */


/* ADC - Peripheral instance base addresses */
/** Peripheral ADC base pointer */
#define ADC_BASE_PTR                             ((ADC_MemMapPtr)0x4003B000u)
/** Array initializer of ADC peripheral base pointers */
#define ADC_BASE_PTRS                            { ADC_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- ADC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Register_Accessor_Macros ADC - Register accessor macros
 * @{
 */


/* ADC - Register instance definitions */
/* ADC */
#define ADC_SC1                                  ADC_SC1_REG(ADC_BASE_PTR)
#define ADC_SC2                                  ADC_SC2_REG(ADC_BASE_PTR)
#define ADC_SC3                                  ADC_SC3_REG(ADC_BASE_PTR)
#define ADC_SC4                                  ADC_SC4_REG(ADC_BASE_PTR)
#define ADC_R                                    ADC_R_REG(ADC_BASE_PTR)
#define ADC_CV                                   ADC_CV_REG(ADC_BASE_PTR)
#define ADC_APCTL1                               ADC_APCTL1_REG(ADC_BASE_PTR)

/*!
 * @}
 */ /* end of group ADC_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group ADC_Peripheral */


/* ----------------------------------------------------------------------------
   -- BP
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup BP_Peripheral BP
 * @{
 */

/** BP - Peripheral register structure */
typedef struct BP_MemMap {
  uint32_t CTRL;                                   /**< FlashPatch Control Register, offset: 0x0 */
  uint8_t RESERVED_0[4];
  uint32_t COMP[2];                                /**< FlashPatch Comparator Register 0..FlashPatch Comparator Register 1, array offset: 0x8, array step: 0x4 */
  uint8_t RESERVED_1[4032];
  uint32_t PID4;                                   /**< Peripheral Identification Register 4., offset: 0xFD0 */
  uint32_t PID5;                                   /**< Peripheral Identification Register 5., offset: 0xFD4 */
  uint32_t PID6;                                   /**< Peripheral Identification Register 6., offset: 0xFD8 */
  uint32_t PID7;                                   /**< Peripheral Identification Register 7., offset: 0xFDC */
  uint32_t PID0;                                   /**< Peripheral Identification Register 0., offset: 0xFE0 */
  uint32_t PID1;                                   /**< Peripheral Identification Register 1., offset: 0xFE4 */
  uint32_t PID2;                                   /**< Peripheral Identification Register 2., offset: 0xFE8 */
  uint32_t PID3;                                   /**< Peripheral Identification Register 3., offset: 0xFEC */
  uint32_t CID0;                                   /**< Component Identification Register 0., offset: 0xFF0 */
  uint32_t CID1;                                   /**< Component Identification Register 1., offset: 0xFF4 */
  uint32_t CID2;                                   /**< Component Identification Register 2., offset: 0xFF8 */
  uint32_t CID3;                                   /**< Component Identification Register 3., offset: 0xFFC */
} volatile *BP_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- BP - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup BP_Register_Accessor_Macros BP - Register accessor macros
 * @{
 */


/* BP - Register accessors */
#define BP_CTRL_REG(base)                        ((base)->CTRL)
#define BP_COMP_REG(base,index)                  ((base)->COMP[index])
#define BP_COMP_COUNT                            2
#define BP_PID4_REG(base)                        ((base)->PID4)
#define BP_PID5_REG(base)                        ((base)->PID5)
#define BP_PID6_REG(base)                        ((base)->PID6)
#define BP_PID7_REG(base)                        ((base)->PID7)
#define BP_PID0_REG(base)                        ((base)->PID0)
#define BP_PID1_REG(base)                        ((base)->PID1)
#define BP_PID2_REG(base)                        ((base)->PID2)
#define BP_PID3_REG(base)                        ((base)->PID3)
#define BP_CID0_REG(base)                        ((base)->CID0)
#define BP_CID1_REG(base)                        ((base)->CID1)
#define BP_CID2_REG(base)                        ((base)->CID2)
#define BP_CID3_REG(base)                        ((base)->CID3)

/*!
 * @}
 */ /* end of group BP_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- BP Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup BP_Register_Masks BP Register Masks
 * @{
 */


/*!
 * @}
 */ /* end of group BP_Register_Masks */


/* BP - Peripheral instance base addresses */
/** Peripheral BP base pointer */
#define BP_BASE_PTR                              ((BP_MemMapPtr)0xE0002000u)
/** Array initializer of BP peripheral base pointers */
#define BP_BASE_PTRS                             { BP_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- BP - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup BP_Register_Accessor_Macros BP - Register accessor macros
 * @{
 */


/* BP - Register instance definitions */
/* BP */
#define BP_CTRL                                  BP_CTRL_REG(BP_BASE_PTR)
#define BP_COMP0                                 BP_COMP_REG(BP_BASE_PTR,0)
#define BP_COMP1                                 BP_COMP_REG(BP_BASE_PTR,1)
#define BP_PID4                                  BP_PID4_REG(BP_BASE_PTR)
#define BP_PID5                                  BP_PID5_REG(BP_BASE_PTR)
#define BP_PID6                                  BP_PID6_REG(BP_BASE_PTR)
#define BP_PID7                                  BP_PID7_REG(BP_BASE_PTR)
#define BP_PID0                                  BP_PID0_REG(BP_BASE_PTR)
#define BP_PID1                                  BP_PID1_REG(BP_BASE_PTR)
#define BP_PID2                                  BP_PID2_REG(BP_BASE_PTR)
#define BP_PID3                                  BP_PID3_REG(BP_BASE_PTR)
#define BP_CID0                                  BP_CID0_REG(BP_BASE_PTR)
#define BP_CID1                                  BP_CID1_REG(BP_BASE_PTR)
#define BP_CID2                                  BP_CID2_REG(BP_BASE_PTR)
#define BP_CID3                                  BP_CID3_REG(BP_BASE_PTR)

/* BP - Register array accessors */
#define BP_COMP(index)                           BP_COMP_REG(BP_BASE_PTR,index)

/*!
 * @}
 */ /* end of group BP_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group BP_Peripheral */


/* ----------------------------------------------------------------------------
   -- CRC
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CRC_Peripheral CRC
 * @{
 */

/** CRC - Peripheral register structure */
typedef struct CRC_MemMap {
  union {                                          /* offset: 0x0 */
    struct {                                         /* offset: 0x0 */
      uint16_t DATAL;                                  /**< CRC_DATAL register., offset: 0x0 */
      uint16_t DATAH;                                  /**< CRC_DATAH register., offset: 0x2 */
    } ACCESS16BIT;
    uint32_t DATA;                                   /**< CRC Data register, offset: 0x0 */
    struct {                                         /* offset: 0x0 */
      uint8_t DATALL;                                  /**< CRC_DATALL register., offset: 0x0 */
      uint8_t DATALU;                                  /**< CRC_DATALU register., offset: 0x1 */
      uint8_t DATAHL;                                  /**< CRC_DATAHL register., offset: 0x2 */
      uint8_t DATAHU;                                  /**< CRC_DATAHU register., offset: 0x3 */
    } ACCESS8BIT;
  };
  union {                                          /* offset: 0x4 */
    struct {                                         /* offset: 0x4 */
      uint16_t GPOLYL;                                 /**< CRC_GPOLYL register., offset: 0x4 */
      uint16_t GPOLYH;                                 /**< CRC_GPOLYH register., offset: 0x6 */
    } GPOLY_ACCESS16BIT;
    uint32_t GPOLY;                                  /**< CRC Polynomial register, offset: 0x4 */
    struct {                                         /* offset: 0x4 */
      uint8_t GPOLYLL;                                 /**< CRC_GPOLYLL register., offset: 0x4 */
      uint8_t GPOLYLU;                                 /**< CRC_GPOLYLU register., offset: 0x5 */
      uint8_t GPOLYHL;                                 /**< CRC_GPOLYHL register., offset: 0x6 */
      uint8_t GPOLYHU;                                 /**< CRC_GPOLYHU register., offset: 0x7 */
    } GPOLY_ACCESS8BIT;
  };
  union {                                          /* offset: 0x8 */
    uint32_t CTRL;                                   /**< CRC Control register, offset: 0x8 */
    struct {                                         /* offset: 0x8 */
      uint8_t RESERVED_0[3];
      uint8_t CTRLHU;                                  /**< CRC_CTRLHU register., offset: 0xB */
    } CTRL_ACCESS8BIT;
  };
} volatile *CRC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- CRC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CRC_Register_Accessor_Macros CRC - Register accessor macros
 * @{
 */


/* CRC - Register accessors */
#define CRC_DATAL_REG(base)                      ((base)->ACCESS16BIT.DATAL)
#define CRC_DATAH_REG(base)                      ((base)->ACCESS16BIT.DATAH)
#define CRC_DATA_REG(base)                       ((base)->DATA)
#define CRC_DATALL_REG(base)                     ((base)->ACCESS8BIT.DATALL)
#define CRC_DATALU_REG(base)                     ((base)->ACCESS8BIT.DATALU)
#define CRC_DATAHL_REG(base)                     ((base)->ACCESS8BIT.DATAHL)
#define CRC_DATAHU_REG(base)                     ((base)->ACCESS8BIT.DATAHU)
#define CRC_GPOLYL_REG(base)                     ((base)->GPOLY_ACCESS16BIT.GPOLYL)
#define CRC_GPOLYH_REG(base)                     ((base)->GPOLY_ACCESS16BIT.GPOLYH)
#define CRC_GPOLY_REG(base)                      ((base)->GPOLY)
#define CRC_GPOLYLL_REG(base)                    ((base)->GPOLY_ACCESS8BIT.GPOLYLL)
#define CRC_GPOLYLU_REG(base)                    ((base)->GPOLY_ACCESS8BIT.GPOLYLU)
#define CRC_GPOLYHL_REG(base)                    ((base)->GPOLY_ACCESS8BIT.GPOLYHL)
#define CRC_GPOLYHU_REG(base)                    ((base)->GPOLY_ACCESS8BIT.GPOLYHU)
#define CRC_CTRL_REG(base)                       ((base)->CTRL)
#define CRC_CTRLHU_REG(base)                     ((base)->CTRL_ACCESS8BIT.CTRLHU)

/*!
 * @}
 */ /* end of group CRC_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- CRC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CRC_Register_Masks CRC Register Masks
 * @{
 */

/* DATAL Bit Fields */
#define CRC_DATAL_DATAL_MASK                     0xFFFFu
#define CRC_DATAL_DATAL_SHIFT                    0
#define CRC_DATAL_DATAL_WIDTH                    16
#define CRC_DATAL_DATAL(x)                       (((uint16_t)(((uint16_t)(x))<<CRC_DATAL_DATAL_SHIFT))&CRC_DATAL_DATAL_MASK)
/* DATAH Bit Fields */
#define CRC_DATAH_DATAH_MASK                     0xFFFFu
#define CRC_DATAH_DATAH_SHIFT                    0
#define CRC_DATAH_DATAH_WIDTH                    16
#define CRC_DATAH_DATAH(x)                       (((uint16_t)(((uint16_t)(x))<<CRC_DATAH_DATAH_SHIFT))&CRC_DATAH_DATAH_MASK)
/* DATA Bit Fields */
#define CRC_DATA_LL_MASK                         0xFFu
#define CRC_DATA_LL_SHIFT                        0
#define CRC_DATA_LL_WIDTH                        8
#define CRC_DATA_LL(x)                           (((uint32_t)(((uint32_t)(x))<<CRC_DATA_LL_SHIFT))&CRC_DATA_LL_MASK)
#define CRC_DATA_LU_MASK                         0xFF00u
#define CRC_DATA_LU_SHIFT                        8
#define CRC_DATA_LU_WIDTH                        8
#define CRC_DATA_LU(x)                           (((uint32_t)(((uint32_t)(x))<<CRC_DATA_LU_SHIFT))&CRC_DATA_LU_MASK)
#define CRC_DATA_HL_MASK                         0xFF0000u
#define CRC_DATA_HL_SHIFT                        16
#define CRC_DATA_HL_WIDTH                        8
#define CRC_DATA_HL(x)                           (((uint32_t)(((uint32_t)(x))<<CRC_DATA_HL_SHIFT))&CRC_DATA_HL_MASK)
#define CRC_DATA_HU_MASK                         0xFF000000u
#define CRC_DATA_HU_SHIFT                        24
#define CRC_DATA_HU_WIDTH                        8
#define CRC_DATA_HU(x)                           (((uint32_t)(((uint32_t)(x))<<CRC_DATA_HU_SHIFT))&CRC_DATA_HU_MASK)
/* DATALL Bit Fields */
#define CRC_DATALL_DATALL_MASK                   0xFFu
#define CRC_DATALL_DATALL_SHIFT                  0
#define CRC_DATALL_DATALL_WIDTH                  8
#define CRC_DATALL_DATALL(x)                     (((uint8_t)(((uint8_t)(x))<<CRC_DATALL_DATALL_SHIFT))&CRC_DATALL_DATALL_MASK)
/* DATALU Bit Fields */
#define CRC_DATALU_DATALU_MASK                   0xFFu
#define CRC_DATALU_DATALU_SHIFT                  0
#define CRC_DATALU_DATALU_WIDTH                  8
#define CRC_DATALU_DATALU(x)                     (((uint8_t)(((uint8_t)(x))<<CRC_DATALU_DATALU_SHIFT))&CRC_DATALU_DATALU_MASK)
/* DATAHL Bit Fields */
#define CRC_DATAHL_DATAHL_MASK                   0xFFu
#define CRC_DATAHL_DATAHL_SHIFT                  0
#define CRC_DATAHL_DATAHL_WIDTH                  8
#define CRC_DATAHL_DATAHL(x)                     (((uint8_t)(((uint8_t)(x))<<CRC_DATAHL_DATAHL_SHIFT))&CRC_DATAHL_DATAHL_MASK)
/* DATAHU Bit Fields */
#define CRC_DATAHU_DATAHU_MASK                   0xFFu
#define CRC_DATAHU_DATAHU_SHIFT                  0
#define CRC_DATAHU_DATAHU_WIDTH                  8
#define CRC_DATAHU_DATAHU(x)                     (((uint8_t)(((uint8_t)(x))<<CRC_DATAHU_DATAHU_SHIFT))&CRC_DATAHU_DATAHU_MASK)
/* GPOLYL Bit Fields */
#define CRC_GPOLYL_GPOLYL_MASK                   0xFFFFu
#define CRC_GPOLYL_GPOLYL_SHIFT                  0
#define CRC_GPOLYL_GPOLYL_WIDTH                  16
#define CRC_GPOLYL_GPOLYL(x)                     (((uint16_t)(((uint16_t)(x))<<CRC_GPOLYL_GPOLYL_SHIFT))&CRC_GPOLYL_GPOLYL_MASK)
/* GPOLYH Bit Fields */
#define CRC_GPOLYH_GPOLYH_MASK                   0xFFFFu
#define CRC_GPOLYH_GPOLYH_SHIFT                  0
#define CRC_GPOLYH_GPOLYH_WIDTH                  16
#define CRC_GPOLYH_GPOLYH(x)                     (((uint16_t)(((uint16_t)(x))<<CRC_GPOLYH_GPOLYH_SHIFT))&CRC_GPOLYH_GPOLYH_MASK)
/* GPOLY Bit Fields */
#define CRC_GPOLY_LOW_MASK                       0xFFFFu
#define CRC_GPOLY_LOW_SHIFT                      0
#define CRC_GPOLY_LOW_WIDTH                      16
#define CRC_GPOLY_LOW(x)                         (((uint32_t)(((uint32_t)(x))<<CRC_GPOLY_LOW_SHIFT))&CRC_GPOLY_LOW_MASK)
#define CRC_GPOLY_HIGH_MASK                      0xFFFF0000u
#define CRC_GPOLY_HIGH_SHIFT                     16
#define CRC_GPOLY_HIGH_WIDTH                     16
#define CRC_GPOLY_HIGH(x)                        (((uint32_t)(((uint32_t)(x))<<CRC_GPOLY_HIGH_SHIFT))&CRC_GPOLY_HIGH_MASK)
/* GPOLYLL Bit Fields */
#define CRC_GPOLYLL_GPOLYLL_MASK                 0xFFu
#define CRC_GPOLYLL_GPOLYLL_SHIFT                0
#define CRC_GPOLYLL_GPOLYLL_WIDTH                8
#define CRC_GPOLYLL_GPOLYLL(x)                   (((uint8_t)(((uint8_t)(x))<<CRC_GPOLYLL_GPOLYLL_SHIFT))&CRC_GPOLYLL_GPOLYLL_MASK)
/* GPOLYLU Bit Fields */
#define CRC_GPOLYLU_GPOLYLU_MASK                 0xFFu
#define CRC_GPOLYLU_GPOLYLU_SHIFT                0
#define CRC_GPOLYLU_GPOLYLU_WIDTH                8
#define CRC_GPOLYLU_GPOLYLU(x)                   (((uint8_t)(((uint8_t)(x))<<CRC_GPOLYLU_GPOLYLU_SHIFT))&CRC_GPOLYLU_GPOLYLU_MASK)
/* GPOLYHL Bit Fields */
#define CRC_GPOLYHL_GPOLYHL_MASK                 0xFFu
#define CRC_GPOLYHL_GPOLYHL_SHIFT                0
#define CRC_GPOLYHL_GPOLYHL_WIDTH                8
#define CRC_GPOLYHL_GPOLYHL(x)                   (((uint8_t)(((uint8_t)(x))<<CRC_GPOLYHL_GPOLYHL_SHIFT))&CRC_GPOLYHL_GPOLYHL_MASK)
/* GPOLYHU Bit Fields */
#define CRC_GPOLYHU_GPOLYHU_MASK                 0xFFu
#define CRC_GPOLYHU_GPOLYHU_SHIFT                0
#define CRC_GPOLYHU_GPOLYHU_WIDTH                8
#define CRC_GPOLYHU_GPOLYHU(x)                   (((uint8_t)(((uint8_t)(x))<<CRC_GPOLYHU_GPOLYHU_SHIFT))&CRC_GPOLYHU_GPOLYHU_MASK)
/* CTRL Bit Fields */
#define CRC_CTRL_TCRC_MASK                       0x1000000u
#define CRC_CTRL_TCRC_SHIFT                      24
#define CRC_CTRL_TCRC_WIDTH                      1
#define CRC_CTRL_TCRC(x)                         (((uint32_t)(((uint32_t)(x))<<CRC_CTRL_TCRC_SHIFT))&CRC_CTRL_TCRC_MASK)
#define CRC_CTRL_WAS_MASK                        0x2000000u
#define CRC_CTRL_WAS_SHIFT                       25
#define CRC_CTRL_WAS_WIDTH                       1
#define CRC_CTRL_WAS(x)                          (((uint32_t)(((uint32_t)(x))<<CRC_CTRL_WAS_SHIFT))&CRC_CTRL_WAS_MASK)
#define CRC_CTRL_FXOR_MASK                       0x4000000u
#define CRC_CTRL_FXOR_SHIFT                      26
#define CRC_CTRL_FXOR_WIDTH                      1
#define CRC_CTRL_FXOR(x)                         (((uint32_t)(((uint32_t)(x))<<CRC_CTRL_FXOR_SHIFT))&CRC_CTRL_FXOR_MASK)
#define CRC_CTRL_TOTR_MASK                       0x30000000u
#define CRC_CTRL_TOTR_SHIFT                      28
#define CRC_CTRL_TOTR_WIDTH                      2
#define CRC_CTRL_TOTR(x)                         (((uint32_t)(((uint32_t)(x))<<CRC_CTRL_TOTR_SHIFT))&CRC_CTRL_TOTR_MASK)
#define CRC_CTRL_TOT_MASK                        0xC0000000u
#define CRC_CTRL_TOT_SHIFT                       30
#define CRC_CTRL_TOT_WIDTH                       2
#define CRC_CTRL_TOT(x)                          (((uint32_t)(((uint32_t)(x))<<CRC_CTRL_TOT_SHIFT))&CRC_CTRL_TOT_MASK)
/* CTRLHU Bit Fields */
#define CRC_CTRLHU_TCRC_MASK                     0x1u
#define CRC_CTRLHU_TCRC_SHIFT                    0
#define CRC_CTRLHU_TCRC_WIDTH                    1
#define CRC_CTRLHU_TCRC(x)                       (((uint8_t)(((uint8_t)(x))<<CRC_CTRLHU_TCRC_SHIFT))&CRC_CTRLHU_TCRC_MASK)
#define CRC_CTRLHU_WAS_MASK                      0x2u
#define CRC_CTRLHU_WAS_SHIFT                     1
#define CRC_CTRLHU_WAS_WIDTH                     1
#define CRC_CTRLHU_WAS(x)                        (((uint8_t)(((uint8_t)(x))<<CRC_CTRLHU_WAS_SHIFT))&CRC_CTRLHU_WAS_MASK)
#define CRC_CTRLHU_FXOR_MASK                     0x4u
#define CRC_CTRLHU_FXOR_SHIFT                    2
#define CRC_CTRLHU_FXOR_WIDTH                    1
#define CRC_CTRLHU_FXOR(x)                       (((uint8_t)(((uint8_t)(x))<<CRC_CTRLHU_FXOR_SHIFT))&CRC_CTRLHU_FXOR_MASK)
#define CRC_CTRLHU_TOTR_MASK                     0x30u
#define CRC_CTRLHU_TOTR_SHIFT                    4
#define CRC_CTRLHU_TOTR_WIDTH                    2
#define CRC_CTRLHU_TOTR(x)                       (((uint8_t)(((uint8_t)(x))<<CRC_CTRLHU_TOTR_SHIFT))&CRC_CTRLHU_TOTR_MASK)
#define CRC_CTRLHU_TOT_MASK                      0xC0u
#define CRC_CTRLHU_TOT_SHIFT                     6
#define CRC_CTRLHU_TOT_WIDTH                     2
#define CRC_CTRLHU_TOT(x)                        (((uint8_t)(((uint8_t)(x))<<CRC_CTRLHU_TOT_SHIFT))&CRC_CTRLHU_TOT_MASK)

/*!
 * @}
 */ /* end of group CRC_Register_Masks */


/* CRC - Peripheral instance base addresses */
/** Peripheral CRC base pointer */
#define CRC_BASE_PTR                             ((CRC_MemMapPtr)0x40032000u)
/** Array initializer of CRC peripheral base pointers */
#define CRC_BASE_PTRS                            { CRC_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- CRC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CRC_Register_Accessor_Macros CRC - Register accessor macros
 * @{
 */


/* CRC - Register instance definitions */
/* CRC */
#define CRC_DATA                                 CRC_DATA_REG(CRC_BASE_PTR)
#define CRC_DATAL                                CRC_DATAL_REG(CRC_BASE_PTR)
#define CRC_DATALL                               CRC_DATALL_REG(CRC_BASE_PTR)
#define CRC_DATALU                               CRC_DATALU_REG(CRC_BASE_PTR)
#define CRC_DATAH                                CRC_DATAH_REG(CRC_BASE_PTR)
#define CRC_DATAHL                               CRC_DATAHL_REG(CRC_BASE_PTR)
#define CRC_DATAHU                               CRC_DATAHU_REG(CRC_BASE_PTR)
#define CRC_GPOLY                                CRC_GPOLY_REG(CRC_BASE_PTR)
#define CRC_GPOLYL                               CRC_GPOLYL_REG(CRC_BASE_PTR)
#define CRC_GPOLYLL                              CRC_GPOLYLL_REG(CRC_BASE_PTR)
#define CRC_GPOLYLU                              CRC_GPOLYLU_REG(CRC_BASE_PTR)
#define CRC_GPOLYH                               CRC_GPOLYH_REG(CRC_BASE_PTR)
#define CRC_GPOLYHL                              CRC_GPOLYHL_REG(CRC_BASE_PTR)
#define CRC_GPOLYHU                              CRC_GPOLYHU_REG(CRC_BASE_PTR)
#define CRC_CTRL                                 CRC_CTRL_REG(CRC_BASE_PTR)
#define CRC_CTRLHU                               CRC_CTRLHU_REG(CRC_BASE_PTR)

/*!
 * @}
 */ /* end of group CRC_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group CRC_Peripheral */


/* ----------------------------------------------------------------------------
   -- CoreDebug
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CoreDebug_Peripheral CoreDebug
 * @{
 */

/** CoreDebug - Peripheral register structure */
typedef struct CoreDebug_MemMap {
  union {                                          /* offset: 0x0 */
    uint32_t base_DHCSR_Read;                        /**< Debug Halting Control and Status Register, offset: 0x0 */
    uint32_t base_DHCSR_Write;                       /**< Debug Halting Control and Status Register, offset: 0x0 */
  };
  uint32_t base_DCRSR;                             /**< Debug Core Register Selector Register, offset: 0x4 */
  uint32_t base_DCRDR;                             /**< Debug Core Register Data Register, offset: 0x8 */
  uint32_t base_DEMCR;                             /**< Debug Exception and Monitor Control Register, offset: 0xC */
} volatile *CoreDebug_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- CoreDebug - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CoreDebug_Register_Accessor_Macros CoreDebug - Register accessor macros
 * @{
 */


/* CoreDebug - Register accessors */
#define CoreDebug_base_DHCSR_Read_REG(base)      ((base)->base_DHCSR_Read)
#define CoreDebug_base_DHCSR_Write_REG(base)     ((base)->base_DHCSR_Write)
#define CoreDebug_base_DCRSR_REG(base)           ((base)->base_DCRSR)
#define CoreDebug_base_DCRDR_REG(base)           ((base)->base_DCRDR)
#define CoreDebug_base_DEMCR_REG(base)           ((base)->base_DEMCR)

/*!
 * @}
 */ /* end of group CoreDebug_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- CoreDebug Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CoreDebug_Register_Masks CoreDebug Register Masks
 * @{
 */


/*!
 * @}
 */ /* end of group CoreDebug_Register_Masks */


/* CoreDebug - Peripheral instance base addresses */
/** Peripheral CoreDebug base pointer */
#define CoreDebug_BASE_PTR                       ((CoreDebug_MemMapPtr)0xE000EDF0u)
/** Array initializer of CoreDebug peripheral base pointers */
#define CoreDebug_BASE_PTRS                      { CoreDebug_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- CoreDebug - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CoreDebug_Register_Accessor_Macros CoreDebug - Register accessor macros
 * @{
 */


/* CoreDebug - Register instance definitions */
/* CoreDebug */
#define DHCSR_Read                               CoreDebug_base_DHCSR_Read_REG(CoreDebug_BASE_PTR)
#define DHCSR_Write                              CoreDebug_base_DHCSR_Write_REG(CoreDebug_BASE_PTR)
#define DCRSR                                    CoreDebug_base_DCRSR_REG(CoreDebug_BASE_PTR)
#define DCRDR                                    CoreDebug_base_DCRDR_REG(CoreDebug_BASE_PTR)
#define DEMCR                                    CoreDebug_base_DEMCR_REG(CoreDebug_BASE_PTR)

/*!
 * @}
 */ /* end of group CoreDebug_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group CoreDebug_Peripheral */


/* ----------------------------------------------------------------------------
   -- DWT
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DWT_Peripheral DWT
 * @{
 */

/** DWT - Peripheral register structure */
typedef struct DWT_MemMap {
  uint32_t CTRL;                                   /**< Control Register, offset: 0x0 */
  uint8_t RESERVED_0[24];
  uint32_t PCSR;                                   /**< Program Counter Sample Register, offset: 0x1C */
  struct {                                         /* offset: 0x20, array step: 0x10 */
    uint32_t COMP;                                   /**< Comparator Register 0..Comparator Register 1, array offset: 0x20, array step: 0x10 */
    uint32_t MASK;                                   /**< Mask Register 0..Mask Register 1, array offset: 0x24, array step: 0x10 */
    uint32_t FUNCTION;                               /**< Function Register 0..Function Register 1, array offset: 0x28, array step: 0x10 */
    uint8_t RESERVED_0[4];
  } COMPARATOR[2];
} volatile *DWT_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- DWT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DWT_Register_Accessor_Macros DWT - Register accessor macros
 * @{
 */


/* DWT - Register accessors */
#define DWT_CTRL_REG(base)                       ((base)->CTRL)
#define DWT_PCSR_REG(base)                       ((base)->PCSR)
#define DWT_COMP_REG(base,index)                 ((base)->COMPARATOR[index].COMP)
#define DWT_COMP_COUNT                           2
#define DWT_MASK_REG(base,index)                 ((base)->COMPARATOR[index].MASK)
#define DWT_MASK_COUNT                           2
#define DWT_FUNCTION_REG(base,index)             ((base)->COMPARATOR[index].FUNCTION)
#define DWT_FUNCTION_COUNT                       2

/*!
 * @}
 */ /* end of group DWT_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- DWT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DWT_Register_Masks DWT Register Masks
 * @{
 */


/*!
 * @}
 */ /* end of group DWT_Register_Masks */


/* DWT - Peripheral instance base addresses */
/** Peripheral DWT base pointer */
#define DWT_BASE_PTR                             ((DWT_MemMapPtr)0xE0001000u)
/** Array initializer of DWT peripheral base pointers */
#define DWT_BASE_PTRS                            { DWT_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- DWT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DWT_Register_Accessor_Macros DWT - Register accessor macros
 * @{
 */


/* DWT - Register instance definitions */
/* DWT */
#define DWT_CTRL                                 DWT_CTRL_REG(DWT_BASE_PTR)
#define DWT_PCSR                                 DWT_PCSR_REG(DWT_BASE_PTR)
#define DWT_COMP0                                DWT_COMP_REG(DWT_BASE_PTR,0)
#define DWT_MASK0                                DWT_MASK_REG(DWT_BASE_PTR,0)
#define DWT_FUNCTION0                            DWT_FUNCTION_REG(DWT_BASE_PTR,0)
#define DWT_COMP1                                DWT_COMP_REG(DWT_BASE_PTR,1)
#define DWT_MASK1                                DWT_MASK_REG(DWT_BASE_PTR,1)
#define DWT_FUNCTION1                            DWT_FUNCTION_REG(DWT_BASE_PTR,1)

/* DWT - Register array accessors */
#define DWT_COMP(index)                          DWT_COMP_REG(DWT_BASE_PTR,index)
#define DWT_MASK(index)                          DWT_MASK_REG(DWT_BASE_PTR,index)
#define DWT_FUNCTION(index)                      DWT_FUNCTION_REG(DWT_BASE_PTR,index)

/*!
 * @}
 */ /* end of group DWT_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group DWT_Peripheral */


/* ----------------------------------------------------------------------------
   -- FGPIO
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FGPIO_Peripheral FGPIO
 * @{
 */

/** FGPIO - Peripheral register structure */
typedef struct FGPIO_MemMap {
  uint32_t PDOR;                                   /**< Port Data Output Register, offset: 0x0 */
  uint32_t PSOR;                                   /**< Port Set Output Register, offset: 0x4 */
  uint32_t PCOR;                                   /**< Port Clear Output Register, offset: 0x8 */
  uint32_t PTOR;                                   /**< Port Toggle Output Register, offset: 0xC */
  uint32_t PDIR;                                   /**< Port Data Input Register, offset: 0x10 */
  uint32_t PDDR;                                   /**< Port Data Direction Register, offset: 0x14 */
  uint32_t PIDR;                                   /**< Port Input Disable Register, offset: 0x18 */
} volatile *FGPIO_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- FGPIO - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FGPIO_Register_Accessor_Macros FGPIO - Register accessor macros
 * @{
 */


/* FGPIO - Register accessors */
#define FGPIO_PDOR_REG(base)                     ((base)->PDOR)
#define FGPIO_PSOR_REG(base)                     ((base)->PSOR)
#define FGPIO_PCOR_REG(base)                     ((base)->PCOR)
#define FGPIO_PTOR_REG(base)                     ((base)->PTOR)
#define FGPIO_PDIR_REG(base)                     ((base)->PDIR)
#define FGPIO_PDDR_REG(base)                     ((base)->PDDR)
#define FGPIO_PIDR_REG(base)                     ((base)->PIDR)

/*!
 * @}
 */ /* end of group FGPIO_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- FGPIO Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FGPIO_Register_Masks FGPIO Register Masks
 * @{
 */

/* PDOR Bit Fields */
#define FGPIO_PDOR_PDO_MASK                      0xFFFFFFFFu
#define FGPIO_PDOR_PDO_SHIFT                     0
#define FGPIO_PDOR_PDO_WIDTH                     32
#define FGPIO_PDOR_PDO(x)                        (((uint32_t)(((uint32_t)(x))<<FGPIO_PDOR_PDO_SHIFT))&FGPIO_PDOR_PDO_MASK)
/* PSOR Bit Fields */
#define FGPIO_PSOR_PTSO_MASK                     0xFFFFFFFFu
#define FGPIO_PSOR_PTSO_SHIFT                    0
#define FGPIO_PSOR_PTSO_WIDTH                    32
#define FGPIO_PSOR_PTSO(x)                       (((uint32_t)(((uint32_t)(x))<<FGPIO_PSOR_PTSO_SHIFT))&FGPIO_PSOR_PTSO_MASK)
/* PCOR Bit Fields */
#define FGPIO_PCOR_PTCO_MASK                     0xFFFFFFFFu
#define FGPIO_PCOR_PTCO_SHIFT                    0
#define FGPIO_PCOR_PTCO_WIDTH                    32
#define FGPIO_PCOR_PTCO(x)                       (((uint32_t)(((uint32_t)(x))<<FGPIO_PCOR_PTCO_SHIFT))&FGPIO_PCOR_PTCO_MASK)
/* PTOR Bit Fields */
#define FGPIO_PTOR_PTTO_MASK                     0xFFFFFFFFu
#define FGPIO_PTOR_PTTO_SHIFT                    0
#define FGPIO_PTOR_PTTO_WIDTH                    32
#define FGPIO_PTOR_PTTO(x)                       (((uint32_t)(((uint32_t)(x))<<FGPIO_PTOR_PTTO_SHIFT))&FGPIO_PTOR_PTTO_MASK)
/* PDIR Bit Fields */
#define FGPIO_PDIR_PDI_MASK                      0xFFFFFFFFu
#define FGPIO_PDIR_PDI_SHIFT                     0
#define FGPIO_PDIR_PDI_WIDTH                     32
#define FGPIO_PDIR_PDI(x)                        (((uint32_t)(((uint32_t)(x))<<FGPIO_PDIR_PDI_SHIFT))&FGPIO_PDIR_PDI_MASK)
/* PDDR Bit Fields */
#define FGPIO_PDDR_PDD_MASK                      0xFFFFFFFFu
#define FGPIO_PDDR_PDD_SHIFT                     0
#define FGPIO_PDDR_PDD_WIDTH                     32
#define FGPIO_PDDR_PDD(x)                        (((uint32_t)(((uint32_t)(x))<<FGPIO_PDDR_PDD_SHIFT))&FGPIO_PDDR_PDD_MASK)
/* PIDR Bit Fields */
#define FGPIO_PIDR_PID_MASK                      0xFFFFFFFFu
#define FGPIO_PIDR_PID_SHIFT                     0
#define FGPIO_PIDR_PID_WIDTH                     32
#define FGPIO_PIDR_PID(x)                        (((uint32_t)(((uint32_t)(x))<<FGPIO_PIDR_PID_SHIFT))&FGPIO_PIDR_PID_MASK)

/*!
 * @}
 */ /* end of group FGPIO_Register_Masks */


/* FGPIO - Peripheral instance base addresses */
/** Peripheral FGPIOA base pointer */
#define FGPIOA_BASE_PTR                          ((FGPIO_MemMapPtr)0xF8000000u)
/** Peripheral FGPIOB base pointer */
#define FGPIOB_BASE_PTR                          ((FGPIO_MemMapPtr)0xF8000040u)
/** Array initializer of FGPIO peripheral base pointers */
#define FGPIO_BASE_PTRS                          { FGPIOA_BASE_PTR, FGPIOB_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- FGPIO - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FGPIO_Register_Accessor_Macros FGPIO - Register accessor macros
 * @{
 */


/* FGPIO - Register instance definitions */
/* FGPIOA */
#define FGPIOA_PDOR                              FGPIO_PDOR_REG(FGPIOA_BASE_PTR)
#define FGPIOA_PSOR                              FGPIO_PSOR_REG(FGPIOA_BASE_PTR)
#define FGPIOA_PCOR                              FGPIO_PCOR_REG(FGPIOA_BASE_PTR)
#define FGPIOA_PTOR                              FGPIO_PTOR_REG(FGPIOA_BASE_PTR)
#define FGPIOA_PDIR                              FGPIO_PDIR_REG(FGPIOA_BASE_PTR)
#define FGPIOA_PDDR                              FGPIO_PDDR_REG(FGPIOA_BASE_PTR)
#define FGPIOA_PIDR                              FGPIO_PIDR_REG(FGPIOA_BASE_PTR)
/* FGPIOB */
#define FGPIOB_PDOR                              FGPIO_PDOR_REG(FGPIOB_BASE_PTR)
#define FGPIOB_PSOR                              FGPIO_PSOR_REG(FGPIOB_BASE_PTR)
#define FGPIOB_PCOR                              FGPIO_PCOR_REG(FGPIOB_BASE_PTR)
#define FGPIOB_PTOR                              FGPIO_PTOR_REG(FGPIOB_BASE_PTR)
#define FGPIOB_PDIR                              FGPIO_PDIR_REG(FGPIOB_BASE_PTR)
#define FGPIOB_PDDR                              FGPIO_PDDR_REG(FGPIOB_BASE_PTR)
#define FGPIOB_PIDR                              FGPIO_PIDR_REG(FGPIOB_BASE_PTR)

/*!
 * @}
 */ /* end of group FGPIO_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group FGPIO_Peripheral */


/* ----------------------------------------------------------------------------
   -- FTM
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTM_Peripheral FTM
 * @{
 */

/** FTM - Peripheral register structure */
typedef struct FTM_MemMap {
  uint32_t SC;                                     /**< Status And Control, offset: 0x0 */
  uint32_t CNT;                                    /**< Counter, offset: 0x4 */
  uint32_t MOD;                                    /**< Modulo, offset: 0x8 */
  struct {                                         /* offset: 0xC, array step: 0x8 */
    uint32_t CnSC;                                   /**< Channel (n) Status And Control, array offset: 0xC, array step: 0x8 */
    uint32_t CnV;                                    /**< Channel (n) Value, array offset: 0x10, array step: 0x8 */
  } CONTROLS[6];
  uint8_t RESERVED_0[16];
  uint32_t CNTIN;                                  /**< Counter Initial Value, offset: 0x4C */
  uint32_t STATUS;                                 /**< Capture And Compare Status, offset: 0x50 */
  uint32_t MODE;                                   /**< Features Mode Selection, offset: 0x54 */
  uint32_t SYNC;                                   /**< Synchronization, offset: 0x58 */
  uint32_t OUTINIT;                                /**< Initial State For Channels Output, offset: 0x5C */
  uint32_t OUTMASK;                                /**< Output Mask, offset: 0x60 */
  uint32_t COMBINE;                                /**< Function For Linked Channels, offset: 0x64 */
  uint32_t DEADTIME;                               /**< Deadtime Insertion Control, offset: 0x68 */
  uint32_t EXTTRIG;                                /**< FTM External Trigger, offset: 0x6C */
  uint32_t POL;                                    /**< Channels Polarity, offset: 0x70 */
  uint32_t FMS;                                    /**< Fault Mode Status, offset: 0x74 */
  uint32_t FILTER;                                 /**< Input Capture Filter Control, offset: 0x78 */
  uint32_t FLTCTRL;                                /**< Fault Control, offset: 0x7C */
  uint8_t RESERVED_1[4];
  uint32_t CONF;                                   /**< Configuration, offset: 0x84 */
  uint32_t FLTPOL;                                 /**< FTM Fault Input Polarity, offset: 0x88 */
  uint32_t SYNCONF;                                /**< Synchronization Configuration, offset: 0x8C */
  uint32_t INVCTRL;                                /**< FTM Inverting Control, offset: 0x90 */
  uint32_t SWOCTRL;                                /**< FTM Software Output Control, offset: 0x94 */
  uint32_t PWMLOAD;                                /**< FTM PWM Load, offset: 0x98 */
} volatile *FTM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- FTM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTM_Register_Accessor_Macros FTM - Register accessor macros
 * @{
 */


/* FTM - Register accessors */
#define FTM_SC_REG(base)                         ((base)->SC)
#define FTM_CNT_REG(base)                        ((base)->CNT)
#define FTM_MOD_REG(base)                        ((base)->MOD)
#define FTM_CnSC_REG(base,index)                 ((base)->CONTROLS[index].CnSC)
#define FTM_CnSC_COUNT                           6
#define FTM_CnV_REG(base,index)                  ((base)->CONTROLS[index].CnV)
#define FTM_CnV_COUNT                            6
#define FTM_CNTIN_REG(base)                      ((base)->CNTIN)
#define FTM_STATUS_REG(base)                     ((base)->STATUS)
#define FTM_MODE_REG(base)                       ((base)->MODE)
#define FTM_SYNC_REG(base)                       ((base)->SYNC)
#define FTM_OUTINIT_REG(base)                    ((base)->OUTINIT)
#define FTM_OUTMASK_REG(base)                    ((base)->OUTMASK)
#define FTM_COMBINE_REG(base)                    ((base)->COMBINE)
#define FTM_DEADTIME_REG(base)                   ((base)->DEADTIME)
#define FTM_EXTTRIG_REG(base)                    ((base)->EXTTRIG)
#define FTM_POL_REG(base)                        ((base)->POL)
#define FTM_FMS_REG(base)                        ((base)->FMS)
#define FTM_FILTER_REG(base)                     ((base)->FILTER)
#define FTM_FLTCTRL_REG(base)                    ((base)->FLTCTRL)
#define FTM_CONF_REG(base)                       ((base)->CONF)
#define FTM_FLTPOL_REG(base)                     ((base)->FLTPOL)
#define FTM_SYNCONF_REG(base)                    ((base)->SYNCONF)
#define FTM_INVCTRL_REG(base)                    ((base)->INVCTRL)
#define FTM_SWOCTRL_REG(base)                    ((base)->SWOCTRL)
#define FTM_PWMLOAD_REG(base)                    ((base)->PWMLOAD)

/*!
 * @}
 */ /* end of group FTM_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- FTM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTM_Register_Masks FTM Register Masks
 * @{
 */

/* SC Bit Fields */
#define FTM_SC_PS_MASK                           0x7u
#define FTM_SC_PS_SHIFT                          0
#define FTM_SC_PS_WIDTH                          3
#define FTM_SC_PS(x)                             (((uint32_t)(((uint32_t)(x))<<FTM_SC_PS_SHIFT))&FTM_SC_PS_MASK)
#define FTM_SC_CLKS_MASK                         0x18u
#define FTM_SC_CLKS_SHIFT                        3
#define FTM_SC_CLKS_WIDTH                        2
#define FTM_SC_CLKS(x)                           (((uint32_t)(((uint32_t)(x))<<FTM_SC_CLKS_SHIFT))&FTM_SC_CLKS_MASK)
#define FTM_SC_CPWMS_MASK                        0x20u
#define FTM_SC_CPWMS_SHIFT                       5
#define FTM_SC_CPWMS_WIDTH                       1
#define FTM_SC_CPWMS(x)                          (((uint32_t)(((uint32_t)(x))<<FTM_SC_CPWMS_SHIFT))&FTM_SC_CPWMS_MASK)
#define FTM_SC_TOIE_MASK                         0x40u
#define FTM_SC_TOIE_SHIFT                        6
#define FTM_SC_TOIE_WIDTH                        1
#define FTM_SC_TOIE(x)                           (((uint32_t)(((uint32_t)(x))<<FTM_SC_TOIE_SHIFT))&FTM_SC_TOIE_MASK)
#define FTM_SC_TOF_MASK                          0x80u
#define FTM_SC_TOF_SHIFT                         7
#define FTM_SC_TOF_WIDTH                         1
#define FTM_SC_TOF(x)                            (((uint32_t)(((uint32_t)(x))<<FTM_SC_TOF_SHIFT))&FTM_SC_TOF_MASK)
/* CNT Bit Fields */
#define FTM_CNT_COUNT_MASK                       0xFFFFu
#define FTM_CNT_COUNT_SHIFT                      0
#define FTM_CNT_COUNT_WIDTH                      16
#define FTM_CNT_COUNT(x)                         (((uint32_t)(((uint32_t)(x))<<FTM_CNT_COUNT_SHIFT))&FTM_CNT_COUNT_MASK)
/* MOD Bit Fields */
#define FTM_MOD_MOD_MASK                         0xFFFFu
#define FTM_MOD_MOD_SHIFT                        0
#define FTM_MOD_MOD_WIDTH                        16
#define FTM_MOD_MOD(x)                           (((uint32_t)(((uint32_t)(x))<<FTM_MOD_MOD_SHIFT))&FTM_MOD_MOD_MASK)
/* CnSC Bit Fields */
#define FTM_CnSC_ELSA_MASK                       0x4u
#define FTM_CnSC_ELSA_SHIFT                      2
#define FTM_CnSC_ELSA_WIDTH                      1
#define FTM_CnSC_ELSA(x)                         (((uint32_t)(((uint32_t)(x))<<FTM_CnSC_ELSA_SHIFT))&FTM_CnSC_ELSA_MASK)
#define FTM_CnSC_ELSB_MASK                       0x8u
#define FTM_CnSC_ELSB_SHIFT                      3
#define FTM_CnSC_ELSB_WIDTH                      1
#define FTM_CnSC_ELSB(x)                         (((uint32_t)(((uint32_t)(x))<<FTM_CnSC_ELSB_SHIFT))&FTM_CnSC_ELSB_MASK)
#define FTM_CnSC_MSA_MASK                        0x10u
#define FTM_CnSC_MSA_SHIFT                       4
#define FTM_CnSC_MSA_WIDTH                       1
#define FTM_CnSC_MSA(x)                          (((uint32_t)(((uint32_t)(x))<<FTM_CnSC_MSA_SHIFT))&FTM_CnSC_MSA_MASK)
#define FTM_CnSC_MSB_MASK                        0x20u
#define FTM_CnSC_MSB_SHIFT                       5
#define FTM_CnSC_MSB_WIDTH                       1
#define FTM_CnSC_MSB(x)                          (((uint32_t)(((uint32_t)(x))<<FTM_CnSC_MSB_SHIFT))&FTM_CnSC_MSB_MASK)
#define FTM_CnSC_CHIE_MASK                       0x40u
#define FTM_CnSC_CHIE_SHIFT                      6
#define FTM_CnSC_CHIE_WIDTH                      1
#define FTM_CnSC_CHIE(x)                         (((uint32_t)(((uint32_t)(x))<<FTM_CnSC_CHIE_SHIFT))&FTM_CnSC_CHIE_MASK)
#define FTM_CnSC_CHF_MASK                        0x80u
#define FTM_CnSC_CHF_SHIFT                       7
#define FTM_CnSC_CHF_WIDTH                       1
#define FTM_CnSC_CHF(x)                          (((uint32_t)(((uint32_t)(x))<<FTM_CnSC_CHF_SHIFT))&FTM_CnSC_CHF_MASK)
/* CnV Bit Fields */
#define FTM_CnV_VAL_MASK                         0xFFFFu
#define FTM_CnV_VAL_SHIFT                        0
#define FTM_CnV_VAL_WIDTH                        16
#define FTM_CnV_VAL(x)                           (((uint32_t)(((uint32_t)(x))<<FTM_CnV_VAL_SHIFT))&FTM_CnV_VAL_MASK)
/* CNTIN Bit Fields */
#define FTM_CNTIN_INIT_MASK                      0xFFFFu
#define FTM_CNTIN_INIT_SHIFT                     0
#define FTM_CNTIN_INIT_WIDTH                     16
#define FTM_CNTIN_INIT(x)                        (((uint32_t)(((uint32_t)(x))<<FTM_CNTIN_INIT_SHIFT))&FTM_CNTIN_INIT_MASK)
/* STATUS Bit Fields */
#define FTM_STATUS_CH0F_MASK                     0x1u
#define FTM_STATUS_CH0F_SHIFT                    0
#define FTM_STATUS_CH0F_WIDTH                    1
#define FTM_STATUS_CH0F(x)                       (((uint32_t)(((uint32_t)(x))<<FTM_STATUS_CH0F_SHIFT))&FTM_STATUS_CH0F_MASK)
#define FTM_STATUS_CH1F_MASK                     0x2u
#define FTM_STATUS_CH1F_SHIFT                    1
#define FTM_STATUS_CH1F_WIDTH                    1
#define FTM_STATUS_CH1F(x)                       (((uint32_t)(((uint32_t)(x))<<FTM_STATUS_CH1F_SHIFT))&FTM_STATUS_CH1F_MASK)
#define FTM_STATUS_CH2F_MASK                     0x4u
#define FTM_STATUS_CH2F_SHIFT                    2
#define FTM_STATUS_CH2F_WIDTH                    1
#define FTM_STATUS_CH2F(x)                       (((uint32_t)(((uint32_t)(x))<<FTM_STATUS_CH2F_SHIFT))&FTM_STATUS_CH2F_MASK)
#define FTM_STATUS_CH3F_MASK                     0x8u
#define FTM_STATUS_CH3F_SHIFT                    3
#define FTM_STATUS_CH3F_WIDTH                    1
#define FTM_STATUS_CH3F(x)                       (((uint32_t)(((uint32_t)(x))<<FTM_STATUS_CH3F_SHIFT))&FTM_STATUS_CH3F_MASK)
#define FTM_STATUS_CH4F_MASK                     0x10u
#define FTM_STATUS_CH4F_SHIFT                    4
#define FTM_STATUS_CH4F_WIDTH                    1
#define FTM_STATUS_CH4F(x)                       (((uint32_t)(((uint32_t)(x))<<FTM_STATUS_CH4F_SHIFT))&FTM_STATUS_CH4F_MASK)
#define FTM_STATUS_CH5F_MASK                     0x20u
#define FTM_STATUS_CH5F_SHIFT                    5
#define FTM_STATUS_CH5F_WIDTH                    1
#define FTM_STATUS_CH5F(x)                       (((uint32_t)(((uint32_t)(x))<<FTM_STATUS_CH5F_SHIFT))&FTM_STATUS_CH5F_MASK)
#define FTM_STATUS_CH6F_MASK                     0x40u
#define FTM_STATUS_CH6F_SHIFT                    6
#define FTM_STATUS_CH6F_WIDTH                    1
#define FTM_STATUS_CH6F(x)                       (((uint32_t)(((uint32_t)(x))<<FTM_STATUS_CH6F_SHIFT))&FTM_STATUS_CH6F_MASK)
#define FTM_STATUS_CH7F_MASK                     0x80u
#define FTM_STATUS_CH7F_SHIFT                    7
#define FTM_STATUS_CH7F_WIDTH                    1
#define FTM_STATUS_CH7F(x)                       (((uint32_t)(((uint32_t)(x))<<FTM_STATUS_CH7F_SHIFT))&FTM_STATUS_CH7F_MASK)
/* MODE Bit Fields */
#define FTM_MODE_FTMEN_MASK                      0x1u
#define FTM_MODE_FTMEN_SHIFT                     0
#define FTM_MODE_FTMEN_WIDTH                     1
#define FTM_MODE_FTMEN(x)                        (((uint32_t)(((uint32_t)(x))<<FTM_MODE_FTMEN_SHIFT))&FTM_MODE_FTMEN_MASK)
#define FTM_MODE_INIT_MASK                       0x2u
#define FTM_MODE_INIT_SHIFT                      1
#define FTM_MODE_INIT_WIDTH                      1
#define FTM_MODE_INIT(x)                         (((uint32_t)(((uint32_t)(x))<<FTM_MODE_INIT_SHIFT))&FTM_MODE_INIT_MASK)
#define FTM_MODE_WPDIS_MASK                      0x4u
#define FTM_MODE_WPDIS_SHIFT                     2
#define FTM_MODE_WPDIS_WIDTH                     1
#define FTM_MODE_WPDIS(x)                        (((uint32_t)(((uint32_t)(x))<<FTM_MODE_WPDIS_SHIFT))&FTM_MODE_WPDIS_MASK)
#define FTM_MODE_PWMSYNC_MASK                    0x8u
#define FTM_MODE_PWMSYNC_SHIFT                   3
#define FTM_MODE_PWMSYNC_WIDTH                   1
#define FTM_MODE_PWMSYNC(x)                      (((uint32_t)(((uint32_t)(x))<<FTM_MODE_PWMSYNC_SHIFT))&FTM_MODE_PWMSYNC_MASK)
#define FTM_MODE_CAPTEST_MASK                    0x10u
#define FTM_MODE_CAPTEST_SHIFT                   4
#define FTM_MODE_CAPTEST_WIDTH                   1
#define FTM_MODE_CAPTEST(x)                      (((uint32_t)(((uint32_t)(x))<<FTM_MODE_CAPTEST_SHIFT))&FTM_MODE_CAPTEST_MASK)
#define FTM_MODE_FAULTM_MASK                     0x60u
#define FTM_MODE_FAULTM_SHIFT                    5
#define FTM_MODE_FAULTM_WIDTH                    2
#define FTM_MODE_FAULTM(x)                       (((uint32_t)(((uint32_t)(x))<<FTM_MODE_FAULTM_SHIFT))&FTM_MODE_FAULTM_MASK)
#define FTM_MODE_FAULTIE_MASK                    0x80u
#define FTM_MODE_FAULTIE_SHIFT                   7
#define FTM_MODE_FAULTIE_WIDTH                   1
#define FTM_MODE_FAULTIE(x)                      (((uint32_t)(((uint32_t)(x))<<FTM_MODE_FAULTIE_SHIFT))&FTM_MODE_FAULTIE_MASK)
/* SYNC Bit Fields */
#define FTM_SYNC_CNTMIN_MASK                     0x1u
#define FTM_SYNC_CNTMIN_SHIFT                    0
#define FTM_SYNC_CNTMIN_WIDTH                    1
#define FTM_SYNC_CNTMIN(x)                       (((uint32_t)(((uint32_t)(x))<<FTM_SYNC_CNTMIN_SHIFT))&FTM_SYNC_CNTMIN_MASK)
#define FTM_SYNC_CNTMAX_MASK                     0x2u
#define FTM_SYNC_CNTMAX_SHIFT                    1
#define FTM_SYNC_CNTMAX_WIDTH                    1
#define FTM_SYNC_CNTMAX(x)                       (((uint32_t)(((uint32_t)(x))<<FTM_SYNC_CNTMAX_SHIFT))&FTM_SYNC_CNTMAX_MASK)
#define FTM_SYNC_REINIT_MASK                     0x4u
#define FTM_SYNC_REINIT_SHIFT                    2
#define FTM_SYNC_REINIT_WIDTH                    1
#define FTM_SYNC_REINIT(x)                       (((uint32_t)(((uint32_t)(x))<<FTM_SYNC_REINIT_SHIFT))&FTM_SYNC_REINIT_MASK)
#define FTM_SYNC_SYNCHOM_MASK                    0x8u
#define FTM_SYNC_SYNCHOM_SHIFT                   3
#define FTM_SYNC_SYNCHOM_WIDTH                   1
#define FTM_SYNC_SYNCHOM(x)                      (((uint32_t)(((uint32_t)(x))<<FTM_SYNC_SYNCHOM_SHIFT))&FTM_SYNC_SYNCHOM_MASK)
#define FTM_SYNC_TRIG0_MASK                      0x10u
#define FTM_SYNC_TRIG0_SHIFT                     4
#define FTM_SYNC_TRIG0_WIDTH                     1
#define FTM_SYNC_TRIG0(x)                        (((uint32_t)(((uint32_t)(x))<<FTM_SYNC_TRIG0_SHIFT))&FTM_SYNC_TRIG0_MASK)
#define FTM_SYNC_TRIG1_MASK                      0x20u
#define FTM_SYNC_TRIG1_SHIFT                     5
#define FTM_SYNC_TRIG1_WIDTH                     1
#define FTM_SYNC_TRIG1(x)                        (((uint32_t)(((uint32_t)(x))<<FTM_SYNC_TRIG1_SHIFT))&FTM_SYNC_TRIG1_MASK)
#define FTM_SYNC_TRIG2_MASK                      0x40u
#define FTM_SYNC_TRIG2_SHIFT                     6
#define FTM_SYNC_TRIG2_WIDTH                     1
#define FTM_SYNC_TRIG2(x)                        (((uint32_t)(((uint32_t)(x))<<FTM_SYNC_TRIG2_SHIFT))&FTM_SYNC_TRIG2_MASK)
#define FTM_SYNC_SWSYNC_MASK                     0x80u
#define FTM_SYNC_SWSYNC_SHIFT                    7
#define FTM_SYNC_SWSYNC_WIDTH                    1
#define FTM_SYNC_SWSYNC(x)                       (((uint32_t)(((uint32_t)(x))<<FTM_SYNC_SWSYNC_SHIFT))&FTM_SYNC_SWSYNC_MASK)
/* OUTINIT Bit Fields */
#define FTM_OUTINIT_CH0OI_MASK                   0x1u
#define FTM_OUTINIT_CH0OI_SHIFT                  0
#define FTM_OUTINIT_CH0OI_WIDTH                  1
#define FTM_OUTINIT_CH0OI(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_OUTINIT_CH0OI_SHIFT))&FTM_OUTINIT_CH0OI_MASK)
#define FTM_OUTINIT_CH1OI_MASK                   0x2u
#define FTM_OUTINIT_CH1OI_SHIFT                  1
#define FTM_OUTINIT_CH1OI_WIDTH                  1
#define FTM_OUTINIT_CH1OI(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_OUTINIT_CH1OI_SHIFT))&FTM_OUTINIT_CH1OI_MASK)
#define FTM_OUTINIT_CH2OI_MASK                   0x4u
#define FTM_OUTINIT_CH2OI_SHIFT                  2
#define FTM_OUTINIT_CH2OI_WIDTH                  1
#define FTM_OUTINIT_CH2OI(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_OUTINIT_CH2OI_SHIFT))&FTM_OUTINIT_CH2OI_MASK)
#define FTM_OUTINIT_CH3OI_MASK                   0x8u
#define FTM_OUTINIT_CH3OI_SHIFT                  3
#define FTM_OUTINIT_CH3OI_WIDTH                  1
#define FTM_OUTINIT_CH3OI(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_OUTINIT_CH3OI_SHIFT))&FTM_OUTINIT_CH3OI_MASK)
#define FTM_OUTINIT_CH4OI_MASK                   0x10u
#define FTM_OUTINIT_CH4OI_SHIFT                  4
#define FTM_OUTINIT_CH4OI_WIDTH                  1
#define FTM_OUTINIT_CH4OI(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_OUTINIT_CH4OI_SHIFT))&FTM_OUTINIT_CH4OI_MASK)
#define FTM_OUTINIT_CH5OI_MASK                   0x20u
#define FTM_OUTINIT_CH5OI_SHIFT                  5
#define FTM_OUTINIT_CH5OI_WIDTH                  1
#define FTM_OUTINIT_CH5OI(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_OUTINIT_CH5OI_SHIFT))&FTM_OUTINIT_CH5OI_MASK)
#define FTM_OUTINIT_CH6OI_MASK                   0x40u
#define FTM_OUTINIT_CH6OI_SHIFT                  6
#define FTM_OUTINIT_CH6OI_WIDTH                  1
#define FTM_OUTINIT_CH6OI(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_OUTINIT_CH6OI_SHIFT))&FTM_OUTINIT_CH6OI_MASK)
#define FTM_OUTINIT_CH7OI_MASK                   0x80u
#define FTM_OUTINIT_CH7OI_SHIFT                  7
#define FTM_OUTINIT_CH7OI_WIDTH                  1
#define FTM_OUTINIT_CH7OI(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_OUTINIT_CH7OI_SHIFT))&FTM_OUTINIT_CH7OI_MASK)
/* OUTMASK Bit Fields */
#define FTM_OUTMASK_CH0OM_MASK                   0x1u
#define FTM_OUTMASK_CH0OM_SHIFT                  0
#define FTM_OUTMASK_CH0OM_WIDTH                  1
#define FTM_OUTMASK_CH0OM(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_OUTMASK_CH0OM_SHIFT))&FTM_OUTMASK_CH0OM_MASK)
#define FTM_OUTMASK_CH1OM_MASK                   0x2u
#define FTM_OUTMASK_CH1OM_SHIFT                  1
#define FTM_OUTMASK_CH1OM_WIDTH                  1
#define FTM_OUTMASK_CH1OM(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_OUTMASK_CH1OM_SHIFT))&FTM_OUTMASK_CH1OM_MASK)
#define FTM_OUTMASK_CH2OM_MASK                   0x4u
#define FTM_OUTMASK_CH2OM_SHIFT                  2
#define FTM_OUTMASK_CH2OM_WIDTH                  1
#define FTM_OUTMASK_CH2OM(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_OUTMASK_CH2OM_SHIFT))&FTM_OUTMASK_CH2OM_MASK)
#define FTM_OUTMASK_CH3OM_MASK                   0x8u
#define FTM_OUTMASK_CH3OM_SHIFT                  3
#define FTM_OUTMASK_CH3OM_WIDTH                  1
#define FTM_OUTMASK_CH3OM(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_OUTMASK_CH3OM_SHIFT))&FTM_OUTMASK_CH3OM_MASK)
#define FTM_OUTMASK_CH4OM_MASK                   0x10u
#define FTM_OUTMASK_CH4OM_SHIFT                  4
#define FTM_OUTMASK_CH4OM_WIDTH                  1
#define FTM_OUTMASK_CH4OM(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_OUTMASK_CH4OM_SHIFT))&FTM_OUTMASK_CH4OM_MASK)
#define FTM_OUTMASK_CH5OM_MASK                   0x20u
#define FTM_OUTMASK_CH5OM_SHIFT                  5
#define FTM_OUTMASK_CH5OM_WIDTH                  1
#define FTM_OUTMASK_CH5OM(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_OUTMASK_CH5OM_SHIFT))&FTM_OUTMASK_CH5OM_MASK)
#define FTM_OUTMASK_CH6OM_MASK                   0x40u
#define FTM_OUTMASK_CH6OM_SHIFT                  6
#define FTM_OUTMASK_CH6OM_WIDTH                  1
#define FTM_OUTMASK_CH6OM(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_OUTMASK_CH6OM_SHIFT))&FTM_OUTMASK_CH6OM_MASK)
#define FTM_OUTMASK_CH7OM_MASK                   0x80u
#define FTM_OUTMASK_CH7OM_SHIFT                  7
#define FTM_OUTMASK_CH7OM_WIDTH                  1
#define FTM_OUTMASK_CH7OM(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_OUTMASK_CH7OM_SHIFT))&FTM_OUTMASK_CH7OM_MASK)
/* COMBINE Bit Fields */
#define FTM_COMBINE_COMBINE0_MASK                0x1u
#define FTM_COMBINE_COMBINE0_SHIFT               0
#define FTM_COMBINE_COMBINE0_WIDTH               1
#define FTM_COMBINE_COMBINE0(x)                  (((uint32_t)(((uint32_t)(x))<<FTM_COMBINE_COMBINE0_SHIFT))&FTM_COMBINE_COMBINE0_MASK)
#define FTM_COMBINE_COMP0_MASK                   0x2u
#define FTM_COMBINE_COMP0_SHIFT                  1
#define FTM_COMBINE_COMP0_WIDTH                  1
#define FTM_COMBINE_COMP0(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_COMBINE_COMP0_SHIFT))&FTM_COMBINE_COMP0_MASK)
#define FTM_COMBINE_DECAPEN0_MASK                0x4u
#define FTM_COMBINE_DECAPEN0_SHIFT               2
#define FTM_COMBINE_DECAPEN0_WIDTH               1
#define FTM_COMBINE_DECAPEN0(x)                  (((uint32_t)(((uint32_t)(x))<<FTM_COMBINE_DECAPEN0_SHIFT))&FTM_COMBINE_DECAPEN0_MASK)
#define FTM_COMBINE_DECAP0_MASK                  0x8u
#define FTM_COMBINE_DECAP0_SHIFT                 3
#define FTM_COMBINE_DECAP0_WIDTH                 1
#define FTM_COMBINE_DECAP0(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_COMBINE_DECAP0_SHIFT))&FTM_COMBINE_DECAP0_MASK)
#define FTM_COMBINE_DTEN0_MASK                   0x10u
#define FTM_COMBINE_DTEN0_SHIFT                  4
#define FTM_COMBINE_DTEN0_WIDTH                  1
#define FTM_COMBINE_DTEN0(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_COMBINE_DTEN0_SHIFT))&FTM_COMBINE_DTEN0_MASK)
#define FTM_COMBINE_SYNCEN0_MASK                 0x20u
#define FTM_COMBINE_SYNCEN0_SHIFT                5
#define FTM_COMBINE_SYNCEN0_WIDTH                1
#define FTM_COMBINE_SYNCEN0(x)                   (((uint32_t)(((uint32_t)(x))<<FTM_COMBINE_SYNCEN0_SHIFT))&FTM_COMBINE_SYNCEN0_MASK)
#define FTM_COMBINE_FAULTEN0_MASK                0x40u
#define FTM_COMBINE_FAULTEN0_SHIFT               6
#define FTM_COMBINE_FAULTEN0_WIDTH               1
#define FTM_COMBINE_FAULTEN0(x)                  (((uint32_t)(((uint32_t)(x))<<FTM_COMBINE_FAULTEN0_SHIFT))&FTM_COMBINE_FAULTEN0_MASK)
#define FTM_COMBINE_COMBINE1_MASK                0x100u
#define FTM_COMBINE_COMBINE1_SHIFT               8
#define FTM_COMBINE_COMBINE1_WIDTH               1
#define FTM_COMBINE_COMBINE1(x)                  (((uint32_t)(((uint32_t)(x))<<FTM_COMBINE_COMBINE1_SHIFT))&FTM_COMBINE_COMBINE1_MASK)
#define FTM_COMBINE_COMP1_MASK                   0x200u
#define FTM_COMBINE_COMP1_SHIFT                  9
#define FTM_COMBINE_COMP1_WIDTH                  1
#define FTM_COMBINE_COMP1(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_COMBINE_COMP1_SHIFT))&FTM_COMBINE_COMP1_MASK)
#define FTM_COMBINE_DECAPEN1_MASK                0x400u
#define FTM_COMBINE_DECAPEN1_SHIFT               10
#define FTM_COMBINE_DECAPEN1_WIDTH               1
#define FTM_COMBINE_DECAPEN1(x)                  (((uint32_t)(((uint32_t)(x))<<FTM_COMBINE_DECAPEN1_SHIFT))&FTM_COMBINE_DECAPEN1_MASK)
#define FTM_COMBINE_DECAP1_MASK                  0x800u
#define FTM_COMBINE_DECAP1_SHIFT                 11
#define FTM_COMBINE_DECAP1_WIDTH                 1
#define FTM_COMBINE_DECAP1(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_COMBINE_DECAP1_SHIFT))&FTM_COMBINE_DECAP1_MASK)
#define FTM_COMBINE_DTEN1_MASK                   0x1000u
#define FTM_COMBINE_DTEN1_SHIFT                  12
#define FTM_COMBINE_DTEN1_WIDTH                  1
#define FTM_COMBINE_DTEN1(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_COMBINE_DTEN1_SHIFT))&FTM_COMBINE_DTEN1_MASK)
#define FTM_COMBINE_SYNCEN1_MASK                 0x2000u
#define FTM_COMBINE_SYNCEN1_SHIFT                13
#define FTM_COMBINE_SYNCEN1_WIDTH                1
#define FTM_COMBINE_SYNCEN1(x)                   (((uint32_t)(((uint32_t)(x))<<FTM_COMBINE_SYNCEN1_SHIFT))&FTM_COMBINE_SYNCEN1_MASK)
#define FTM_COMBINE_FAULTEN1_MASK                0x4000u
#define FTM_COMBINE_FAULTEN1_SHIFT               14
#define FTM_COMBINE_FAULTEN1_WIDTH               1
#define FTM_COMBINE_FAULTEN1(x)                  (((uint32_t)(((uint32_t)(x))<<FTM_COMBINE_FAULTEN1_SHIFT))&FTM_COMBINE_FAULTEN1_MASK)
#define FTM_COMBINE_COMBINE2_MASK                0x10000u
#define FTM_COMBINE_COMBINE2_SHIFT               16
#define FTM_COMBINE_COMBINE2_WIDTH               1
#define FTM_COMBINE_COMBINE2(x)                  (((uint32_t)(((uint32_t)(x))<<FTM_COMBINE_COMBINE2_SHIFT))&FTM_COMBINE_COMBINE2_MASK)
#define FTM_COMBINE_COMP2_MASK                   0x20000u
#define FTM_COMBINE_COMP2_SHIFT                  17
#define FTM_COMBINE_COMP2_WIDTH                  1
#define FTM_COMBINE_COMP2(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_COMBINE_COMP2_SHIFT))&FTM_COMBINE_COMP2_MASK)
#define FTM_COMBINE_DECAPEN2_MASK                0x40000u
#define FTM_COMBINE_DECAPEN2_SHIFT               18
#define FTM_COMBINE_DECAPEN2_WIDTH               1
#define FTM_COMBINE_DECAPEN2(x)                  (((uint32_t)(((uint32_t)(x))<<FTM_COMBINE_DECAPEN2_SHIFT))&FTM_COMBINE_DECAPEN2_MASK)
#define FTM_COMBINE_DECAP2_MASK                  0x80000u
#define FTM_COMBINE_DECAP2_SHIFT                 19
#define FTM_COMBINE_DECAP2_WIDTH                 1
#define FTM_COMBINE_DECAP2(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_COMBINE_DECAP2_SHIFT))&FTM_COMBINE_DECAP2_MASK)
#define FTM_COMBINE_DTEN2_MASK                   0x100000u
#define FTM_COMBINE_DTEN2_SHIFT                  20
#define FTM_COMBINE_DTEN2_WIDTH                  1
#define FTM_COMBINE_DTEN2(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_COMBINE_DTEN2_SHIFT))&FTM_COMBINE_DTEN2_MASK)
#define FTM_COMBINE_SYNCEN2_MASK                 0x200000u
#define FTM_COMBINE_SYNCEN2_SHIFT                21
#define FTM_COMBINE_SYNCEN2_WIDTH                1
#define FTM_COMBINE_SYNCEN2(x)                   (((uint32_t)(((uint32_t)(x))<<FTM_COMBINE_SYNCEN2_SHIFT))&FTM_COMBINE_SYNCEN2_MASK)
#define FTM_COMBINE_FAULTEN2_MASK                0x400000u
#define FTM_COMBINE_FAULTEN2_SHIFT               22
#define FTM_COMBINE_FAULTEN2_WIDTH               1
#define FTM_COMBINE_FAULTEN2(x)                  (((uint32_t)(((uint32_t)(x))<<FTM_COMBINE_FAULTEN2_SHIFT))&FTM_COMBINE_FAULTEN2_MASK)
#define FTM_COMBINE_COMBINE3_MASK                0x1000000u
#define FTM_COMBINE_COMBINE3_SHIFT               24
#define FTM_COMBINE_COMBINE3_WIDTH               1
#define FTM_COMBINE_COMBINE3(x)                  (((uint32_t)(((uint32_t)(x))<<FTM_COMBINE_COMBINE3_SHIFT))&FTM_COMBINE_COMBINE3_MASK)
#define FTM_COMBINE_COMP3_MASK                   0x2000000u
#define FTM_COMBINE_COMP3_SHIFT                  25
#define FTM_COMBINE_COMP3_WIDTH                  1
#define FTM_COMBINE_COMP3(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_COMBINE_COMP3_SHIFT))&FTM_COMBINE_COMP3_MASK)
#define FTM_COMBINE_DECAPEN3_MASK                0x4000000u
#define FTM_COMBINE_DECAPEN3_SHIFT               26
#define FTM_COMBINE_DECAPEN3_WIDTH               1
#define FTM_COMBINE_DECAPEN3(x)                  (((uint32_t)(((uint32_t)(x))<<FTM_COMBINE_DECAPEN3_SHIFT))&FTM_COMBINE_DECAPEN3_MASK)
#define FTM_COMBINE_DECAP3_MASK                  0x8000000u
#define FTM_COMBINE_DECAP3_SHIFT                 27
#define FTM_COMBINE_DECAP3_WIDTH                 1
#define FTM_COMBINE_DECAP3(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_COMBINE_DECAP3_SHIFT))&FTM_COMBINE_DECAP3_MASK)
#define FTM_COMBINE_DTEN3_MASK                   0x10000000u
#define FTM_COMBINE_DTEN3_SHIFT                  28
#define FTM_COMBINE_DTEN3_WIDTH                  1
#define FTM_COMBINE_DTEN3(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_COMBINE_DTEN3_SHIFT))&FTM_COMBINE_DTEN3_MASK)
#define FTM_COMBINE_SYNCEN3_MASK                 0x20000000u
#define FTM_COMBINE_SYNCEN3_SHIFT                29
#define FTM_COMBINE_SYNCEN3_WIDTH                1
#define FTM_COMBINE_SYNCEN3(x)                   (((uint32_t)(((uint32_t)(x))<<FTM_COMBINE_SYNCEN3_SHIFT))&FTM_COMBINE_SYNCEN3_MASK)
#define FTM_COMBINE_FAULTEN3_MASK                0x40000000u
#define FTM_COMBINE_FAULTEN3_SHIFT               30
#define FTM_COMBINE_FAULTEN3_WIDTH               1
#define FTM_COMBINE_FAULTEN3(x)                  (((uint32_t)(((uint32_t)(x))<<FTM_COMBINE_FAULTEN3_SHIFT))&FTM_COMBINE_FAULTEN3_MASK)
/* DEADTIME Bit Fields */
#define FTM_DEADTIME_DTVAL_MASK                  0x3Fu
#define FTM_DEADTIME_DTVAL_SHIFT                 0
#define FTM_DEADTIME_DTVAL_WIDTH                 6
#define FTM_DEADTIME_DTVAL(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_DEADTIME_DTVAL_SHIFT))&FTM_DEADTIME_DTVAL_MASK)
#define FTM_DEADTIME_DTPS_MASK                   0xC0u
#define FTM_DEADTIME_DTPS_SHIFT                  6
#define FTM_DEADTIME_DTPS_WIDTH                  2
#define FTM_DEADTIME_DTPS(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_DEADTIME_DTPS_SHIFT))&FTM_DEADTIME_DTPS_MASK)
/* EXTTRIG Bit Fields */
#define FTM_EXTTRIG_CH2TRIG_MASK                 0x1u
#define FTM_EXTTRIG_CH2TRIG_SHIFT                0
#define FTM_EXTTRIG_CH2TRIG_WIDTH                1
#define FTM_EXTTRIG_CH2TRIG(x)                   (((uint32_t)(((uint32_t)(x))<<FTM_EXTTRIG_CH2TRIG_SHIFT))&FTM_EXTTRIG_CH2TRIG_MASK)
#define FTM_EXTTRIG_CH3TRIG_MASK                 0x2u
#define FTM_EXTTRIG_CH3TRIG_SHIFT                1
#define FTM_EXTTRIG_CH3TRIG_WIDTH                1
#define FTM_EXTTRIG_CH3TRIG(x)                   (((uint32_t)(((uint32_t)(x))<<FTM_EXTTRIG_CH3TRIG_SHIFT))&FTM_EXTTRIG_CH3TRIG_MASK)
#define FTM_EXTTRIG_CH4TRIG_MASK                 0x4u
#define FTM_EXTTRIG_CH4TRIG_SHIFT                2
#define FTM_EXTTRIG_CH4TRIG_WIDTH                1
#define FTM_EXTTRIG_CH4TRIG(x)                   (((uint32_t)(((uint32_t)(x))<<FTM_EXTTRIG_CH4TRIG_SHIFT))&FTM_EXTTRIG_CH4TRIG_MASK)
#define FTM_EXTTRIG_CH5TRIG_MASK                 0x8u
#define FTM_EXTTRIG_CH5TRIG_SHIFT                3
#define FTM_EXTTRIG_CH5TRIG_WIDTH                1
#define FTM_EXTTRIG_CH5TRIG(x)                   (((uint32_t)(((uint32_t)(x))<<FTM_EXTTRIG_CH5TRIG_SHIFT))&FTM_EXTTRIG_CH5TRIG_MASK)
#define FTM_EXTTRIG_CH0TRIG_MASK                 0x10u
#define FTM_EXTTRIG_CH0TRIG_SHIFT                4
#define FTM_EXTTRIG_CH0TRIG_WIDTH                1
#define FTM_EXTTRIG_CH0TRIG(x)                   (((uint32_t)(((uint32_t)(x))<<FTM_EXTTRIG_CH0TRIG_SHIFT))&FTM_EXTTRIG_CH0TRIG_MASK)
#define FTM_EXTTRIG_CH1TRIG_MASK                 0x20u
#define FTM_EXTTRIG_CH1TRIG_SHIFT                5
#define FTM_EXTTRIG_CH1TRIG_WIDTH                1
#define FTM_EXTTRIG_CH1TRIG(x)                   (((uint32_t)(((uint32_t)(x))<<FTM_EXTTRIG_CH1TRIG_SHIFT))&FTM_EXTTRIG_CH1TRIG_MASK)
#define FTM_EXTTRIG_INITTRIGEN_MASK              0x40u
#define FTM_EXTTRIG_INITTRIGEN_SHIFT             6
#define FTM_EXTTRIG_INITTRIGEN_WIDTH             1
#define FTM_EXTTRIG_INITTRIGEN(x)                (((uint32_t)(((uint32_t)(x))<<FTM_EXTTRIG_INITTRIGEN_SHIFT))&FTM_EXTTRIG_INITTRIGEN_MASK)
#define FTM_EXTTRIG_TRIGF_MASK                   0x80u
#define FTM_EXTTRIG_TRIGF_SHIFT                  7
#define FTM_EXTTRIG_TRIGF_WIDTH                  1
#define FTM_EXTTRIG_TRIGF(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_EXTTRIG_TRIGF_SHIFT))&FTM_EXTTRIG_TRIGF_MASK)
/* POL Bit Fields */
#define FTM_POL_POL0_MASK                        0x1u
#define FTM_POL_POL0_SHIFT                       0
#define FTM_POL_POL0_WIDTH                       1
#define FTM_POL_POL0(x)                          (((uint32_t)(((uint32_t)(x))<<FTM_POL_POL0_SHIFT))&FTM_POL_POL0_MASK)
#define FTM_POL_POL1_MASK                        0x2u
#define FTM_POL_POL1_SHIFT                       1
#define FTM_POL_POL1_WIDTH                       1
#define FTM_POL_POL1(x)                          (((uint32_t)(((uint32_t)(x))<<FTM_POL_POL1_SHIFT))&FTM_POL_POL1_MASK)
#define FTM_POL_POL2_MASK                        0x4u
#define FTM_POL_POL2_SHIFT                       2
#define FTM_POL_POL2_WIDTH                       1
#define FTM_POL_POL2(x)                          (((uint32_t)(((uint32_t)(x))<<FTM_POL_POL2_SHIFT))&FTM_POL_POL2_MASK)
#define FTM_POL_POL3_MASK                        0x8u
#define FTM_POL_POL3_SHIFT                       3
#define FTM_POL_POL3_WIDTH                       1
#define FTM_POL_POL3(x)                          (((uint32_t)(((uint32_t)(x))<<FTM_POL_POL3_SHIFT))&FTM_POL_POL3_MASK)
#define FTM_POL_POL4_MASK                        0x10u
#define FTM_POL_POL4_SHIFT                       4
#define FTM_POL_POL4_WIDTH                       1
#define FTM_POL_POL4(x)                          (((uint32_t)(((uint32_t)(x))<<FTM_POL_POL4_SHIFT))&FTM_POL_POL4_MASK)
#define FTM_POL_POL5_MASK                        0x20u
#define FTM_POL_POL5_SHIFT                       5
#define FTM_POL_POL5_WIDTH                       1
#define FTM_POL_POL5(x)                          (((uint32_t)(((uint32_t)(x))<<FTM_POL_POL5_SHIFT))&FTM_POL_POL5_MASK)
#define FTM_POL_POL6_MASK                        0x40u
#define FTM_POL_POL6_SHIFT                       6
#define FTM_POL_POL6_WIDTH                       1
#define FTM_POL_POL6(x)                          (((uint32_t)(((uint32_t)(x))<<FTM_POL_POL6_SHIFT))&FTM_POL_POL6_MASK)
#define FTM_POL_POL7_MASK                        0x80u
#define FTM_POL_POL7_SHIFT                       7
#define FTM_POL_POL7_WIDTH                       1
#define FTM_POL_POL7(x)                          (((uint32_t)(((uint32_t)(x))<<FTM_POL_POL7_SHIFT))&FTM_POL_POL7_MASK)
/* FMS Bit Fields */
#define FTM_FMS_FAULTF0_MASK                     0x1u
#define FTM_FMS_FAULTF0_SHIFT                    0
#define FTM_FMS_FAULTF0_WIDTH                    1
#define FTM_FMS_FAULTF0(x)                       (((uint32_t)(((uint32_t)(x))<<FTM_FMS_FAULTF0_SHIFT))&FTM_FMS_FAULTF0_MASK)
#define FTM_FMS_FAULTF1_MASK                     0x2u
#define FTM_FMS_FAULTF1_SHIFT                    1
#define FTM_FMS_FAULTF1_WIDTH                    1
#define FTM_FMS_FAULTF1(x)                       (((uint32_t)(((uint32_t)(x))<<FTM_FMS_FAULTF1_SHIFT))&FTM_FMS_FAULTF1_MASK)
#define FTM_FMS_FAULTF2_MASK                     0x4u
#define FTM_FMS_FAULTF2_SHIFT                    2
#define FTM_FMS_FAULTF2_WIDTH                    1
#define FTM_FMS_FAULTF2(x)                       (((uint32_t)(((uint32_t)(x))<<FTM_FMS_FAULTF2_SHIFT))&FTM_FMS_FAULTF2_MASK)
#define FTM_FMS_FAULTF3_MASK                     0x8u
#define FTM_FMS_FAULTF3_SHIFT                    3
#define FTM_FMS_FAULTF3_WIDTH                    1
#define FTM_FMS_FAULTF3(x)                       (((uint32_t)(((uint32_t)(x))<<FTM_FMS_FAULTF3_SHIFT))&FTM_FMS_FAULTF3_MASK)
#define FTM_FMS_FAULTIN_MASK                     0x20u
#define FTM_FMS_FAULTIN_SHIFT                    5
#define FTM_FMS_FAULTIN_WIDTH                    1
#define FTM_FMS_FAULTIN(x)                       (((uint32_t)(((uint32_t)(x))<<FTM_FMS_FAULTIN_SHIFT))&FTM_FMS_FAULTIN_MASK)
#define FTM_FMS_WPEN_MASK                        0x40u
#define FTM_FMS_WPEN_SHIFT                       6
#define FTM_FMS_WPEN_WIDTH                       1
#define FTM_FMS_WPEN(x)                          (((uint32_t)(((uint32_t)(x))<<FTM_FMS_WPEN_SHIFT))&FTM_FMS_WPEN_MASK)
#define FTM_FMS_FAULTF_MASK                      0x80u
#define FTM_FMS_FAULTF_SHIFT                     7
#define FTM_FMS_FAULTF_WIDTH                     1
#define FTM_FMS_FAULTF(x)                        (((uint32_t)(((uint32_t)(x))<<FTM_FMS_FAULTF_SHIFT))&FTM_FMS_FAULTF_MASK)
/* FILTER Bit Fields */
#define FTM_FILTER_CH0FVAL_MASK                  0xFu
#define FTM_FILTER_CH0FVAL_SHIFT                 0
#define FTM_FILTER_CH0FVAL_WIDTH                 4
#define FTM_FILTER_CH0FVAL(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_FILTER_CH0FVAL_SHIFT))&FTM_FILTER_CH0FVAL_MASK)
#define FTM_FILTER_CH1FVAL_MASK                  0xF0u
#define FTM_FILTER_CH1FVAL_SHIFT                 4
#define FTM_FILTER_CH1FVAL_WIDTH                 4
#define FTM_FILTER_CH1FVAL(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_FILTER_CH1FVAL_SHIFT))&FTM_FILTER_CH1FVAL_MASK)
#define FTM_FILTER_CH2FVAL_MASK                  0xF00u
#define FTM_FILTER_CH2FVAL_SHIFT                 8
#define FTM_FILTER_CH2FVAL_WIDTH                 4
#define FTM_FILTER_CH2FVAL(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_FILTER_CH2FVAL_SHIFT))&FTM_FILTER_CH2FVAL_MASK)
#define FTM_FILTER_CH3FVAL_MASK                  0xF000u
#define FTM_FILTER_CH3FVAL_SHIFT                 12
#define FTM_FILTER_CH3FVAL_WIDTH                 4
#define FTM_FILTER_CH3FVAL(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_FILTER_CH3FVAL_SHIFT))&FTM_FILTER_CH3FVAL_MASK)
/* FLTCTRL Bit Fields */
#define FTM_FLTCTRL_FAULT0EN_MASK                0x1u
#define FTM_FLTCTRL_FAULT0EN_SHIFT               0
#define FTM_FLTCTRL_FAULT0EN_WIDTH               1
#define FTM_FLTCTRL_FAULT0EN(x)                  (((uint32_t)(((uint32_t)(x))<<FTM_FLTCTRL_FAULT0EN_SHIFT))&FTM_FLTCTRL_FAULT0EN_MASK)
#define FTM_FLTCTRL_FAULT1EN_MASK                0x2u
#define FTM_FLTCTRL_FAULT1EN_SHIFT               1
#define FTM_FLTCTRL_FAULT1EN_WIDTH               1
#define FTM_FLTCTRL_FAULT1EN(x)                  (((uint32_t)(((uint32_t)(x))<<FTM_FLTCTRL_FAULT1EN_SHIFT))&FTM_FLTCTRL_FAULT1EN_MASK)
#define FTM_FLTCTRL_FAULT2EN_MASK                0x4u
#define FTM_FLTCTRL_FAULT2EN_SHIFT               2
#define FTM_FLTCTRL_FAULT2EN_WIDTH               1
#define FTM_FLTCTRL_FAULT2EN(x)                  (((uint32_t)(((uint32_t)(x))<<FTM_FLTCTRL_FAULT2EN_SHIFT))&FTM_FLTCTRL_FAULT2EN_MASK)
#define FTM_FLTCTRL_FAULT3EN_MASK                0x8u
#define FTM_FLTCTRL_FAULT3EN_SHIFT               3
#define FTM_FLTCTRL_FAULT3EN_WIDTH               1
#define FTM_FLTCTRL_FAULT3EN(x)                  (((uint32_t)(((uint32_t)(x))<<FTM_FLTCTRL_FAULT3EN_SHIFT))&FTM_FLTCTRL_FAULT3EN_MASK)
#define FTM_FLTCTRL_FFLTR0EN_MASK                0x10u
#define FTM_FLTCTRL_FFLTR0EN_SHIFT               4
#define FTM_FLTCTRL_FFLTR0EN_WIDTH               1
#define FTM_FLTCTRL_FFLTR0EN(x)                  (((uint32_t)(((uint32_t)(x))<<FTM_FLTCTRL_FFLTR0EN_SHIFT))&FTM_FLTCTRL_FFLTR0EN_MASK)
#define FTM_FLTCTRL_FFLTR1EN_MASK                0x20u
#define FTM_FLTCTRL_FFLTR1EN_SHIFT               5
#define FTM_FLTCTRL_FFLTR1EN_WIDTH               1
#define FTM_FLTCTRL_FFLTR1EN(x)                  (((uint32_t)(((uint32_t)(x))<<FTM_FLTCTRL_FFLTR1EN_SHIFT))&FTM_FLTCTRL_FFLTR1EN_MASK)
#define FTM_FLTCTRL_FFLTR2EN_MASK                0x40u
#define FTM_FLTCTRL_FFLTR2EN_SHIFT               6
#define FTM_FLTCTRL_FFLTR2EN_WIDTH               1
#define FTM_FLTCTRL_FFLTR2EN(x)                  (((uint32_t)(((uint32_t)(x))<<FTM_FLTCTRL_FFLTR2EN_SHIFT))&FTM_FLTCTRL_FFLTR2EN_MASK)
#define FTM_FLTCTRL_FFLTR3EN_MASK                0x80u
#define FTM_FLTCTRL_FFLTR3EN_SHIFT               7
#define FTM_FLTCTRL_FFLTR3EN_WIDTH               1
#define FTM_FLTCTRL_FFLTR3EN(x)                  (((uint32_t)(((uint32_t)(x))<<FTM_FLTCTRL_FFLTR3EN_SHIFT))&FTM_FLTCTRL_FFLTR3EN_MASK)
#define FTM_FLTCTRL_FFVAL_MASK                   0xF00u
#define FTM_FLTCTRL_FFVAL_SHIFT                  8
#define FTM_FLTCTRL_FFVAL_WIDTH                  4
#define FTM_FLTCTRL_FFVAL(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_FLTCTRL_FFVAL_SHIFT))&FTM_FLTCTRL_FFVAL_MASK)
/* CONF Bit Fields */
#define FTM_CONF_NUMTOF_MASK                     0x1Fu
#define FTM_CONF_NUMTOF_SHIFT                    0
#define FTM_CONF_NUMTOF_WIDTH                    5
#define FTM_CONF_NUMTOF(x)                       (((uint32_t)(((uint32_t)(x))<<FTM_CONF_NUMTOF_SHIFT))&FTM_CONF_NUMTOF_MASK)
#define FTM_CONF_BDMMODE_MASK                    0xC0u
#define FTM_CONF_BDMMODE_SHIFT                   6
#define FTM_CONF_BDMMODE_WIDTH                   2
#define FTM_CONF_BDMMODE(x)                      (((uint32_t)(((uint32_t)(x))<<FTM_CONF_BDMMODE_SHIFT))&FTM_CONF_BDMMODE_MASK)
#define FTM_CONF_GTBEEN_MASK                     0x200u
#define FTM_CONF_GTBEEN_SHIFT                    9
#define FTM_CONF_GTBEEN_WIDTH                    1
#define FTM_CONF_GTBEEN(x)                       (((uint32_t)(((uint32_t)(x))<<FTM_CONF_GTBEEN_SHIFT))&FTM_CONF_GTBEEN_MASK)
#define FTM_CONF_GTBEOUT_MASK                    0x400u
#define FTM_CONF_GTBEOUT_SHIFT                   10
#define FTM_CONF_GTBEOUT_WIDTH                   1
#define FTM_CONF_GTBEOUT(x)                      (((uint32_t)(((uint32_t)(x))<<FTM_CONF_GTBEOUT_SHIFT))&FTM_CONF_GTBEOUT_MASK)
/* FLTPOL Bit Fields */
#define FTM_FLTPOL_FLT0POL_MASK                  0x1u
#define FTM_FLTPOL_FLT0POL_SHIFT                 0
#define FTM_FLTPOL_FLT0POL_WIDTH                 1
#define FTM_FLTPOL_FLT0POL(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_FLTPOL_FLT0POL_SHIFT))&FTM_FLTPOL_FLT0POL_MASK)
#define FTM_FLTPOL_FLT1POL_MASK                  0x2u
#define FTM_FLTPOL_FLT1POL_SHIFT                 1
#define FTM_FLTPOL_FLT1POL_WIDTH                 1
#define FTM_FLTPOL_FLT1POL(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_FLTPOL_FLT1POL_SHIFT))&FTM_FLTPOL_FLT1POL_MASK)
#define FTM_FLTPOL_FLT2POL_MASK                  0x4u
#define FTM_FLTPOL_FLT2POL_SHIFT                 2
#define FTM_FLTPOL_FLT2POL_WIDTH                 1
#define FTM_FLTPOL_FLT2POL(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_FLTPOL_FLT2POL_SHIFT))&FTM_FLTPOL_FLT2POL_MASK)
#define FTM_FLTPOL_FLT3POL_MASK                  0x8u
#define FTM_FLTPOL_FLT3POL_SHIFT                 3
#define FTM_FLTPOL_FLT3POL_WIDTH                 1
#define FTM_FLTPOL_FLT3POL(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_FLTPOL_FLT3POL_SHIFT))&FTM_FLTPOL_FLT3POL_MASK)
/* SYNCONF Bit Fields */
#define FTM_SYNCONF_HWTRIGMODE_MASK              0x1u
#define FTM_SYNCONF_HWTRIGMODE_SHIFT             0
#define FTM_SYNCONF_HWTRIGMODE_WIDTH             1
#define FTM_SYNCONF_HWTRIGMODE(x)                (((uint32_t)(((uint32_t)(x))<<FTM_SYNCONF_HWTRIGMODE_SHIFT))&FTM_SYNCONF_HWTRIGMODE_MASK)
#define FTM_SYNCONF_CNTINC_MASK                  0x4u
#define FTM_SYNCONF_CNTINC_SHIFT                 2
#define FTM_SYNCONF_CNTINC_WIDTH                 1
#define FTM_SYNCONF_CNTINC(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_SYNCONF_CNTINC_SHIFT))&FTM_SYNCONF_CNTINC_MASK)
#define FTM_SYNCONF_INVC_MASK                    0x10u
#define FTM_SYNCONF_INVC_SHIFT                   4
#define FTM_SYNCONF_INVC_WIDTH                   1
#define FTM_SYNCONF_INVC(x)                      (((uint32_t)(((uint32_t)(x))<<FTM_SYNCONF_INVC_SHIFT))&FTM_SYNCONF_INVC_MASK)
#define FTM_SYNCONF_SWOC_MASK                    0x20u
#define FTM_SYNCONF_SWOC_SHIFT                   5
#define FTM_SYNCONF_SWOC_WIDTH                   1
#define FTM_SYNCONF_SWOC(x)                      (((uint32_t)(((uint32_t)(x))<<FTM_SYNCONF_SWOC_SHIFT))&FTM_SYNCONF_SWOC_MASK)
#define FTM_SYNCONF_SYNCMODE_MASK                0x80u
#define FTM_SYNCONF_SYNCMODE_SHIFT               7
#define FTM_SYNCONF_SYNCMODE_WIDTH               1
#define FTM_SYNCONF_SYNCMODE(x)                  (((uint32_t)(((uint32_t)(x))<<FTM_SYNCONF_SYNCMODE_SHIFT))&FTM_SYNCONF_SYNCMODE_MASK)
#define FTM_SYNCONF_SWRSTCNT_MASK                0x100u
#define FTM_SYNCONF_SWRSTCNT_SHIFT               8
#define FTM_SYNCONF_SWRSTCNT_WIDTH               1
#define FTM_SYNCONF_SWRSTCNT(x)                  (((uint32_t)(((uint32_t)(x))<<FTM_SYNCONF_SWRSTCNT_SHIFT))&FTM_SYNCONF_SWRSTCNT_MASK)
#define FTM_SYNCONF_SWWRBUF_MASK                 0x200u
#define FTM_SYNCONF_SWWRBUF_SHIFT                9
#define FTM_SYNCONF_SWWRBUF_WIDTH                1
#define FTM_SYNCONF_SWWRBUF(x)                   (((uint32_t)(((uint32_t)(x))<<FTM_SYNCONF_SWWRBUF_SHIFT))&FTM_SYNCONF_SWWRBUF_MASK)
#define FTM_SYNCONF_SWOM_MASK                    0x400u
#define FTM_SYNCONF_SWOM_SHIFT                   10
#define FTM_SYNCONF_SWOM_WIDTH                   1
#define FTM_SYNCONF_SWOM(x)                      (((uint32_t)(((uint32_t)(x))<<FTM_SYNCONF_SWOM_SHIFT))&FTM_SYNCONF_SWOM_MASK)
#define FTM_SYNCONF_SWINVC_MASK                  0x800u
#define FTM_SYNCONF_SWINVC_SHIFT                 11
#define FTM_SYNCONF_SWINVC_WIDTH                 1
#define FTM_SYNCONF_SWINVC(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_SYNCONF_SWINVC_SHIFT))&FTM_SYNCONF_SWINVC_MASK)
#define FTM_SYNCONF_SWSOC_MASK                   0x1000u
#define FTM_SYNCONF_SWSOC_SHIFT                  12
#define FTM_SYNCONF_SWSOC_WIDTH                  1
#define FTM_SYNCONF_SWSOC(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_SYNCONF_SWSOC_SHIFT))&FTM_SYNCONF_SWSOC_MASK)
#define FTM_SYNCONF_HWRSTCNT_MASK                0x10000u
#define FTM_SYNCONF_HWRSTCNT_SHIFT               16
#define FTM_SYNCONF_HWRSTCNT_WIDTH               1
#define FTM_SYNCONF_HWRSTCNT(x)                  (((uint32_t)(((uint32_t)(x))<<FTM_SYNCONF_HWRSTCNT_SHIFT))&FTM_SYNCONF_HWRSTCNT_MASK)
#define FTM_SYNCONF_HWWRBUF_MASK                 0x20000u
#define FTM_SYNCONF_HWWRBUF_SHIFT                17
#define FTM_SYNCONF_HWWRBUF_WIDTH                1
#define FTM_SYNCONF_HWWRBUF(x)                   (((uint32_t)(((uint32_t)(x))<<FTM_SYNCONF_HWWRBUF_SHIFT))&FTM_SYNCONF_HWWRBUF_MASK)
#define FTM_SYNCONF_HWOM_MASK                    0x40000u
#define FTM_SYNCONF_HWOM_SHIFT                   18
#define FTM_SYNCONF_HWOM_WIDTH                   1
#define FTM_SYNCONF_HWOM(x)                      (((uint32_t)(((uint32_t)(x))<<FTM_SYNCONF_HWOM_SHIFT))&FTM_SYNCONF_HWOM_MASK)
#define FTM_SYNCONF_HWINVC_MASK                  0x80000u
#define FTM_SYNCONF_HWINVC_SHIFT                 19
#define FTM_SYNCONF_HWINVC_WIDTH                 1
#define FTM_SYNCONF_HWINVC(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_SYNCONF_HWINVC_SHIFT))&FTM_SYNCONF_HWINVC_MASK)
#define FTM_SYNCONF_HWSOC_MASK                   0x100000u
#define FTM_SYNCONF_HWSOC_SHIFT                  20
#define FTM_SYNCONF_HWSOC_WIDTH                  1
#define FTM_SYNCONF_HWSOC(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_SYNCONF_HWSOC_SHIFT))&FTM_SYNCONF_HWSOC_MASK)
/* INVCTRL Bit Fields */
#define FTM_INVCTRL_INV0EN_MASK                  0x1u
#define FTM_INVCTRL_INV0EN_SHIFT                 0
#define FTM_INVCTRL_INV0EN_WIDTH                 1
#define FTM_INVCTRL_INV0EN(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_INVCTRL_INV0EN_SHIFT))&FTM_INVCTRL_INV0EN_MASK)
#define FTM_INVCTRL_INV1EN_MASK                  0x2u
#define FTM_INVCTRL_INV1EN_SHIFT                 1
#define FTM_INVCTRL_INV1EN_WIDTH                 1
#define FTM_INVCTRL_INV1EN(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_INVCTRL_INV1EN_SHIFT))&FTM_INVCTRL_INV1EN_MASK)
#define FTM_INVCTRL_INV2EN_MASK                  0x4u
#define FTM_INVCTRL_INV2EN_SHIFT                 2
#define FTM_INVCTRL_INV2EN_WIDTH                 1
#define FTM_INVCTRL_INV2EN(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_INVCTRL_INV2EN_SHIFT))&FTM_INVCTRL_INV2EN_MASK)
#define FTM_INVCTRL_INV3EN_MASK                  0x8u
#define FTM_INVCTRL_INV3EN_SHIFT                 3
#define FTM_INVCTRL_INV3EN_WIDTH                 1
#define FTM_INVCTRL_INV3EN(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_INVCTRL_INV3EN_SHIFT))&FTM_INVCTRL_INV3EN_MASK)
/* SWOCTRL Bit Fields */
#define FTM_SWOCTRL_CH0OC_MASK                   0x1u
#define FTM_SWOCTRL_CH0OC_SHIFT                  0
#define FTM_SWOCTRL_CH0OC_WIDTH                  1
#define FTM_SWOCTRL_CH0OC(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_SWOCTRL_CH0OC_SHIFT))&FTM_SWOCTRL_CH0OC_MASK)
#define FTM_SWOCTRL_CH1OC_MASK                   0x2u
#define FTM_SWOCTRL_CH1OC_SHIFT                  1
#define FTM_SWOCTRL_CH1OC_WIDTH                  1
#define FTM_SWOCTRL_CH1OC(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_SWOCTRL_CH1OC_SHIFT))&FTM_SWOCTRL_CH1OC_MASK)
#define FTM_SWOCTRL_CH2OC_MASK                   0x4u
#define FTM_SWOCTRL_CH2OC_SHIFT                  2
#define FTM_SWOCTRL_CH2OC_WIDTH                  1
#define FTM_SWOCTRL_CH2OC(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_SWOCTRL_CH2OC_SHIFT))&FTM_SWOCTRL_CH2OC_MASK)
#define FTM_SWOCTRL_CH3OC_MASK                   0x8u
#define FTM_SWOCTRL_CH3OC_SHIFT                  3
#define FTM_SWOCTRL_CH3OC_WIDTH                  1
#define FTM_SWOCTRL_CH3OC(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_SWOCTRL_CH3OC_SHIFT))&FTM_SWOCTRL_CH3OC_MASK)
#define FTM_SWOCTRL_CH4OC_MASK                   0x10u
#define FTM_SWOCTRL_CH4OC_SHIFT                  4
#define FTM_SWOCTRL_CH4OC_WIDTH                  1
#define FTM_SWOCTRL_CH4OC(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_SWOCTRL_CH4OC_SHIFT))&FTM_SWOCTRL_CH4OC_MASK)
#define FTM_SWOCTRL_CH5OC_MASK                   0x20u
#define FTM_SWOCTRL_CH5OC_SHIFT                  5
#define FTM_SWOCTRL_CH5OC_WIDTH                  1
#define FTM_SWOCTRL_CH5OC(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_SWOCTRL_CH5OC_SHIFT))&FTM_SWOCTRL_CH5OC_MASK)
#define FTM_SWOCTRL_CH6OC_MASK                   0x40u
#define FTM_SWOCTRL_CH6OC_SHIFT                  6
#define FTM_SWOCTRL_CH6OC_WIDTH                  1
#define FTM_SWOCTRL_CH6OC(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_SWOCTRL_CH6OC_SHIFT))&FTM_SWOCTRL_CH6OC_MASK)
#define FTM_SWOCTRL_CH7OC_MASK                   0x80u
#define FTM_SWOCTRL_CH7OC_SHIFT                  7
#define FTM_SWOCTRL_CH7OC_WIDTH                  1
#define FTM_SWOCTRL_CH7OC(x)                     (((uint32_t)(((uint32_t)(x))<<FTM_SWOCTRL_CH7OC_SHIFT))&FTM_SWOCTRL_CH7OC_MASK)
#define FTM_SWOCTRL_CH0OCV_MASK                  0x100u
#define FTM_SWOCTRL_CH0OCV_SHIFT                 8
#define FTM_SWOCTRL_CH0OCV_WIDTH                 1
#define FTM_SWOCTRL_CH0OCV(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_SWOCTRL_CH0OCV_SHIFT))&FTM_SWOCTRL_CH0OCV_MASK)
#define FTM_SWOCTRL_CH1OCV_MASK                  0x200u
#define FTM_SWOCTRL_CH1OCV_SHIFT                 9
#define FTM_SWOCTRL_CH1OCV_WIDTH                 1
#define FTM_SWOCTRL_CH1OCV(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_SWOCTRL_CH1OCV_SHIFT))&FTM_SWOCTRL_CH1OCV_MASK)
#define FTM_SWOCTRL_CH2OCV_MASK                  0x400u
#define FTM_SWOCTRL_CH2OCV_SHIFT                 10
#define FTM_SWOCTRL_CH2OCV_WIDTH                 1
#define FTM_SWOCTRL_CH2OCV(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_SWOCTRL_CH2OCV_SHIFT))&FTM_SWOCTRL_CH2OCV_MASK)
#define FTM_SWOCTRL_CH3OCV_MASK                  0x800u
#define FTM_SWOCTRL_CH3OCV_SHIFT                 11
#define FTM_SWOCTRL_CH3OCV_WIDTH                 1
#define FTM_SWOCTRL_CH3OCV(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_SWOCTRL_CH3OCV_SHIFT))&FTM_SWOCTRL_CH3OCV_MASK)
#define FTM_SWOCTRL_CH4OCV_MASK                  0x1000u
#define FTM_SWOCTRL_CH4OCV_SHIFT                 12
#define FTM_SWOCTRL_CH4OCV_WIDTH                 1
#define FTM_SWOCTRL_CH4OCV(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_SWOCTRL_CH4OCV_SHIFT))&FTM_SWOCTRL_CH4OCV_MASK)
#define FTM_SWOCTRL_CH5OCV_MASK                  0x2000u
#define FTM_SWOCTRL_CH5OCV_SHIFT                 13
#define FTM_SWOCTRL_CH5OCV_WIDTH                 1
#define FTM_SWOCTRL_CH5OCV(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_SWOCTRL_CH5OCV_SHIFT))&FTM_SWOCTRL_CH5OCV_MASK)
#define FTM_SWOCTRL_CH6OCV_MASK                  0x4000u
#define FTM_SWOCTRL_CH6OCV_SHIFT                 14
#define FTM_SWOCTRL_CH6OCV_WIDTH                 1
#define FTM_SWOCTRL_CH6OCV(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_SWOCTRL_CH6OCV_SHIFT))&FTM_SWOCTRL_CH6OCV_MASK)
#define FTM_SWOCTRL_CH7OCV_MASK                  0x8000u
#define FTM_SWOCTRL_CH7OCV_SHIFT                 15
#define FTM_SWOCTRL_CH7OCV_WIDTH                 1
#define FTM_SWOCTRL_CH7OCV(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_SWOCTRL_CH7OCV_SHIFT))&FTM_SWOCTRL_CH7OCV_MASK)
/* PWMLOAD Bit Fields */
#define FTM_PWMLOAD_CH0SEL_MASK                  0x1u
#define FTM_PWMLOAD_CH0SEL_SHIFT                 0
#define FTM_PWMLOAD_CH0SEL_WIDTH                 1
#define FTM_PWMLOAD_CH0SEL(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_PWMLOAD_CH0SEL_SHIFT))&FTM_PWMLOAD_CH0SEL_MASK)
#define FTM_PWMLOAD_CH1SEL_MASK                  0x2u
#define FTM_PWMLOAD_CH1SEL_SHIFT                 1
#define FTM_PWMLOAD_CH1SEL_WIDTH                 1
#define FTM_PWMLOAD_CH1SEL(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_PWMLOAD_CH1SEL_SHIFT))&FTM_PWMLOAD_CH1SEL_MASK)
#define FTM_PWMLOAD_CH2SEL_MASK                  0x4u
#define FTM_PWMLOAD_CH2SEL_SHIFT                 2
#define FTM_PWMLOAD_CH2SEL_WIDTH                 1
#define FTM_PWMLOAD_CH2SEL(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_PWMLOAD_CH2SEL_SHIFT))&FTM_PWMLOAD_CH2SEL_MASK)
#define FTM_PWMLOAD_CH3SEL_MASK                  0x8u
#define FTM_PWMLOAD_CH3SEL_SHIFT                 3
#define FTM_PWMLOAD_CH3SEL_WIDTH                 1
#define FTM_PWMLOAD_CH3SEL(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_PWMLOAD_CH3SEL_SHIFT))&FTM_PWMLOAD_CH3SEL_MASK)
#define FTM_PWMLOAD_CH4SEL_MASK                  0x10u
#define FTM_PWMLOAD_CH4SEL_SHIFT                 4
#define FTM_PWMLOAD_CH4SEL_WIDTH                 1
#define FTM_PWMLOAD_CH4SEL(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_PWMLOAD_CH4SEL_SHIFT))&FTM_PWMLOAD_CH4SEL_MASK)
#define FTM_PWMLOAD_CH5SEL_MASK                  0x20u
#define FTM_PWMLOAD_CH5SEL_SHIFT                 5
#define FTM_PWMLOAD_CH5SEL_WIDTH                 1
#define FTM_PWMLOAD_CH5SEL(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_PWMLOAD_CH5SEL_SHIFT))&FTM_PWMLOAD_CH5SEL_MASK)
#define FTM_PWMLOAD_CH6SEL_MASK                  0x40u
#define FTM_PWMLOAD_CH6SEL_SHIFT                 6
#define FTM_PWMLOAD_CH6SEL_WIDTH                 1
#define FTM_PWMLOAD_CH6SEL(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_PWMLOAD_CH6SEL_SHIFT))&FTM_PWMLOAD_CH6SEL_MASK)
#define FTM_PWMLOAD_CH7SEL_MASK                  0x80u
#define FTM_PWMLOAD_CH7SEL_SHIFT                 7
#define FTM_PWMLOAD_CH7SEL_WIDTH                 1
#define FTM_PWMLOAD_CH7SEL(x)                    (((uint32_t)(((uint32_t)(x))<<FTM_PWMLOAD_CH7SEL_SHIFT))&FTM_PWMLOAD_CH7SEL_MASK)
#define FTM_PWMLOAD_LDOK_MASK                    0x200u
#define FTM_PWMLOAD_LDOK_SHIFT                   9
#define FTM_PWMLOAD_LDOK_WIDTH                   1
#define FTM_PWMLOAD_LDOK(x)                      (((uint32_t)(((uint32_t)(x))<<FTM_PWMLOAD_LDOK_SHIFT))&FTM_PWMLOAD_LDOK_MASK)

/*!
 * @}
 */ /* end of group FTM_Register_Masks */


/* FTM - Peripheral instance base addresses */
/** Peripheral FTM0 base pointer */
#define FTM0_BASE_PTR                            ((FTM_MemMapPtr)0x40038000u)
/** Peripheral FTM1 base pointer */
#define FTM1_BASE_PTR                            ((FTM_MemMapPtr)0x40039000u)
/** Peripheral FTM2 base pointer */
#define FTM2_BASE_PTR                            ((FTM_MemMapPtr)0x4003A000u)
/** Array initializer of FTM peripheral base pointers */
#define FTM_BASE_PTRS                            { FTM0_BASE_PTR, FTM1_BASE_PTR, FTM2_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- FTM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTM_Register_Accessor_Macros FTM - Register accessor macros
 * @{
 */


/* FTM - Register instance definitions */
/* FTM0 */
#define FTM0_SC                                  FTM_SC_REG(FTM0_BASE_PTR)
#define FTM0_CNT                                 FTM_CNT_REG(FTM0_BASE_PTR)
#define FTM0_MOD                                 FTM_MOD_REG(FTM0_BASE_PTR)
#define FTM0_C0SC                                FTM_CnSC_REG(FTM0_BASE_PTR,0)
#define FTM0_C0V                                 FTM_CnV_REG(FTM0_BASE_PTR,0)
#define FTM0_C1SC                                FTM_CnSC_REG(FTM0_BASE_PTR,1)
#define FTM0_C1V                                 FTM_CnV_REG(FTM0_BASE_PTR,1)
/* FTM1 */
#define FTM1_SC                                  FTM_SC_REG(FTM1_BASE_PTR)
#define FTM1_CNT                                 FTM_CNT_REG(FTM1_BASE_PTR)
#define FTM1_MOD                                 FTM_MOD_REG(FTM1_BASE_PTR)
#define FTM1_C0SC                                FTM_CnSC_REG(FTM1_BASE_PTR,0)
#define FTM1_C0V                                 FTM_CnV_REG(FTM1_BASE_PTR,0)
#define FTM1_C1SC                                FTM_CnSC_REG(FTM1_BASE_PTR,1)
#define FTM1_C1V                                 FTM_CnV_REG(FTM1_BASE_PTR,1)
/* FTM2 */
#define FTM2_SC                                  FTM_SC_REG(FTM2_BASE_PTR)
#define FTM2_CNT                                 FTM_CNT_REG(FTM2_BASE_PTR)
#define FTM2_MOD                                 FTM_MOD_REG(FTM2_BASE_PTR)
#define FTM2_C0SC                                FTM_CnSC_REG(FTM2_BASE_PTR,0)
#define FTM2_C0V                                 FTM_CnV_REG(FTM2_BASE_PTR,0)
#define FTM2_C1SC                                FTM_CnSC_REG(FTM2_BASE_PTR,1)
#define FTM2_C1V                                 FTM_CnV_REG(FTM2_BASE_PTR,1)
#define FTM2_C2SC                                FTM_CnSC_REG(FTM2_BASE_PTR,2)
#define FTM2_C2V                                 FTM_CnV_REG(FTM2_BASE_PTR,2)
#define FTM2_C3SC                                FTM_CnSC_REG(FTM2_BASE_PTR,3)
#define FTM2_C3V                                 FTM_CnV_REG(FTM2_BASE_PTR,3)
#define FTM2_C4SC                                FTM_CnSC_REG(FTM2_BASE_PTR,4)
#define FTM2_C4V                                 FTM_CnV_REG(FTM2_BASE_PTR,4)
#define FTM2_C5SC                                FTM_CnSC_REG(FTM2_BASE_PTR,5)
#define FTM2_C5V                                 FTM_CnV_REG(FTM2_BASE_PTR,5)
#define FTM2_CNTIN                               FTM_CNTIN_REG(FTM2_BASE_PTR)
#define FTM2_STATUS                              FTM_STATUS_REG(FTM2_BASE_PTR)
#define FTM2_MODE                                FTM_MODE_REG(FTM2_BASE_PTR)
#define FTM2_SYNC                                FTM_SYNC_REG(FTM2_BASE_PTR)
#define FTM2_OUTINIT                             FTM_OUTINIT_REG(FTM2_BASE_PTR)
#define FTM2_OUTMASK                             FTM_OUTMASK_REG(FTM2_BASE_PTR)
#define FTM2_COMBINE                             FTM_COMBINE_REG(FTM2_BASE_PTR)
#define FTM2_DEADTIME                            FTM_DEADTIME_REG(FTM2_BASE_PTR)
#define FTM2_EXTTRIG                             FTM_EXTTRIG_REG(FTM2_BASE_PTR)
#define FTM2_POL                                 FTM_POL_REG(FTM2_BASE_PTR)
#define FTM2_FMS                                 FTM_FMS_REG(FTM2_BASE_PTR)
#define FTM2_FILTER                              FTM_FILTER_REG(FTM2_BASE_PTR)
#define FTM2_FLTCTRL                             FTM_FLTCTRL_REG(FTM2_BASE_PTR)
#define FTM2_CONF                                FTM_CONF_REG(FTM2_BASE_PTR)
#define FTM2_FLTPOL                              FTM_FLTPOL_REG(FTM2_BASE_PTR)
#define FTM2_SYNCONF                             FTM_SYNCONF_REG(FTM2_BASE_PTR)
#define FTM2_INVCTRL                             FTM_INVCTRL_REG(FTM2_BASE_PTR)
#define FTM2_SWOCTRL                             FTM_SWOCTRL_REG(FTM2_BASE_PTR)
#define FTM2_PWMLOAD                             FTM_PWMLOAD_REG(FTM2_BASE_PTR)

/* FTM - Register array accessors */
#define FTM0_CnSC(index)                         FTM_CnSC_REG(FTM0_BASE_PTR,index)
#define FTM1_CnSC(index)                         FTM_CnSC_REG(FTM1_BASE_PTR,index)
#define FTM2_CnSC(index)                         FTM_CnSC_REG(FTM2_BASE_PTR,index)
#define FTM0_CnV(index)                          FTM_CnV_REG(FTM0_BASE_PTR,index)
#define FTM1_CnV(index)                          FTM_CnV_REG(FTM1_BASE_PTR,index)
#define FTM2_CnV(index)                          FTM_CnV_REG(FTM2_BASE_PTR,index)

/*!
 * @}
 */ /* end of group FTM_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group FTM_Peripheral */


/* ----------------------------------------------------------------------------
   -- FTMRH
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTMRH_Peripheral FTMRH
 * @{
 */

/** FTMRH - Peripheral register structure */
typedef struct FTMRH_MemMap {
  uint8_t FCLKDIV;                                 /**< Flash Clock Divider Register, offset: 0x0 */
  uint8_t FSEC;                                    /**< Flash Security Register, offset: 0x1 */
  uint8_t FCCOBIX;                                 /**< Flash CCOB Index Register, offset: 0x2 */
  uint8_t RESERVED_0[1];
  uint8_t FCNFG;                                   /**< Flash Configuration Register, offset: 0x4 */
  uint8_t FERCNFG;                                 /**< Flash Error Configuration Register, offset: 0x5 */
  uint8_t FSTAT;                                   /**< Flash Status Register, offset: 0x6 */
  uint8_t FERSTAT;                                 /**< Flash Error Status Register, offset: 0x7 */
  uint8_t FPROT;                                   /**< Flash Protection Register, offset: 0x8 */
  uint8_t EEPROT;                                  /**< EEPROM Protection Register, offset: 0x9 */
  uint8_t FCCOBHI;                                 /**< Flash Common Command Object Register:High, offset: 0xA */
  uint8_t FCCOBLO;                                 /**< Flash Common Command Object Register: Low, offset: 0xB */
  uint8_t FOPT;                                    /**< Flash Option Register, offset: 0xC */
} volatile *FTMRH_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- FTMRH - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTMRH_Register_Accessor_Macros FTMRH - Register accessor macros
 * @{
 */


/* FTMRH - Register accessors */
#define FTMRH_FCLKDIV_REG(base)                  ((base)->FCLKDIV)
#define FTMRH_FSEC_REG(base)                     ((base)->FSEC)
#define FTMRH_FCCOBIX_REG(base)                  ((base)->FCCOBIX)
#define FTMRH_FCNFG_REG(base)                    ((base)->FCNFG)
#define FTMRH_FERCNFG_REG(base)                  ((base)->FERCNFG)
#define FTMRH_FSTAT_REG(base)                    ((base)->FSTAT)
#define FTMRH_FERSTAT_REG(base)                  ((base)->FERSTAT)
#define FTMRH_FPROT_REG(base)                    ((base)->FPROT)
#define FTMRH_EEPROT_REG(base)                   ((base)->EEPROT)
#define FTMRH_FCCOBHI_REG(base)                  ((base)->FCCOBHI)
#define FTMRH_FCCOBLO_REG(base)                  ((base)->FCCOBLO)
#define FTMRH_FOPT_REG(base)                     ((base)->FOPT)

/*!
 * @}
 */ /* end of group FTMRH_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- FTMRH Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTMRH_Register_Masks FTMRH Register Masks
 * @{
 */

/* FCLKDIV Bit Fields */
#define FTMRH_FCLKDIV_FDIV_MASK                  0x3Fu
#define FTMRH_FCLKDIV_FDIV_SHIFT                 0
#define FTMRH_FCLKDIV_FDIV_WIDTH                 6
#define FTMRH_FCLKDIV_FDIV(x)                    (((uint8_t)(((uint8_t)(x))<<FTMRH_FCLKDIV_FDIV_SHIFT))&FTMRH_FCLKDIV_FDIV_MASK)
#define FTMRH_FCLKDIV_FDIVLCK_MASK               0x40u
#define FTMRH_FCLKDIV_FDIVLCK_SHIFT              6
#define FTMRH_FCLKDIV_FDIVLCK_WIDTH              1
#define FTMRH_FCLKDIV_FDIVLCK(x)                 (((uint8_t)(((uint8_t)(x))<<FTMRH_FCLKDIV_FDIVLCK_SHIFT))&FTMRH_FCLKDIV_FDIVLCK_MASK)
#define FTMRH_FCLKDIV_FDIVLD_MASK                0x80u
#define FTMRH_FCLKDIV_FDIVLD_SHIFT               7
#define FTMRH_FCLKDIV_FDIVLD_WIDTH               1
#define FTMRH_FCLKDIV_FDIVLD(x)                  (((uint8_t)(((uint8_t)(x))<<FTMRH_FCLKDIV_FDIVLD_SHIFT))&FTMRH_FCLKDIV_FDIVLD_MASK)
/* FSEC Bit Fields */
#define FTMRH_FSEC_SEC_MASK                      0x3u
#define FTMRH_FSEC_SEC_SHIFT                     0
#define FTMRH_FSEC_SEC_WIDTH                     2
#define FTMRH_FSEC_SEC(x)                        (((uint8_t)(((uint8_t)(x))<<FTMRH_FSEC_SEC_SHIFT))&FTMRH_FSEC_SEC_MASK)
#define FTMRH_FSEC_KEYEN_MASK                    0xC0u
#define FTMRH_FSEC_KEYEN_SHIFT                   6
#define FTMRH_FSEC_KEYEN_WIDTH                   2
#define FTMRH_FSEC_KEYEN(x)                      (((uint8_t)(((uint8_t)(x))<<FTMRH_FSEC_KEYEN_SHIFT))&FTMRH_FSEC_KEYEN_MASK)
/* FCCOBIX Bit Fields */
#define FTMRH_FCCOBIX_CCOBIX_MASK                0x7u
#define FTMRH_FCCOBIX_CCOBIX_SHIFT               0
#define FTMRH_FCCOBIX_CCOBIX_WIDTH               3
#define FTMRH_FCCOBIX_CCOBIX(x)                  (((uint8_t)(((uint8_t)(x))<<FTMRH_FCCOBIX_CCOBIX_SHIFT))&FTMRH_FCCOBIX_CCOBIX_MASK)
/* FCNFG Bit Fields */
#define FTMRH_FCNFG_FSFD_MASK                    0x1u
#define FTMRH_FCNFG_FSFD_SHIFT                   0
#define FTMRH_FCNFG_FSFD_WIDTH                   1
#define FTMRH_FCNFG_FSFD(x)                      (((uint8_t)(((uint8_t)(x))<<FTMRH_FCNFG_FSFD_SHIFT))&FTMRH_FCNFG_FSFD_MASK)
#define FTMRH_FCNFG_FDFD_MASK                    0x2u
#define FTMRH_FCNFG_FDFD_SHIFT                   1
#define FTMRH_FCNFG_FDFD_WIDTH                   1
#define FTMRH_FCNFG_FDFD(x)                      (((uint8_t)(((uint8_t)(x))<<FTMRH_FCNFG_FDFD_SHIFT))&FTMRH_FCNFG_FDFD_MASK)
#define FTMRH_FCNFG_IGNSF_MASK                   0x10u
#define FTMRH_FCNFG_IGNSF_SHIFT                  4
#define FTMRH_FCNFG_IGNSF_WIDTH                  1
#define FTMRH_FCNFG_IGNSF(x)                     (((uint8_t)(((uint8_t)(x))<<FTMRH_FCNFG_IGNSF_SHIFT))&FTMRH_FCNFG_IGNSF_MASK)
#define FTMRH_FCNFG_CCIE_MASK                    0x80u
#define FTMRH_FCNFG_CCIE_SHIFT                   7
#define FTMRH_FCNFG_CCIE_WIDTH                   1
#define FTMRH_FCNFG_CCIE(x)                      (((uint8_t)(((uint8_t)(x))<<FTMRH_FCNFG_CCIE_SHIFT))&FTMRH_FCNFG_CCIE_MASK)
/* FERCNFG Bit Fields */
#define FTMRH_FERCNFG_SFDIE_MASK                 0x1u
#define FTMRH_FERCNFG_SFDIE_SHIFT                0
#define FTMRH_FERCNFG_SFDIE_WIDTH                1
#define FTMRH_FERCNFG_SFDIE(x)                   (((uint8_t)(((uint8_t)(x))<<FTMRH_FERCNFG_SFDIE_SHIFT))&FTMRH_FERCNFG_SFDIE_MASK)
#define FTMRH_FERCNFG_DFDIE_MASK                 0x2u
#define FTMRH_FERCNFG_DFDIE_SHIFT                1
#define FTMRH_FERCNFG_DFDIE_WIDTH                1
#define FTMRH_FERCNFG_DFDIE(x)                   (((uint8_t)(((uint8_t)(x))<<FTMRH_FERCNFG_DFDIE_SHIFT))&FTMRH_FERCNFG_DFDIE_MASK)
/* FSTAT Bit Fields */
#define FTMRH_FSTAT_MGSTAT_MASK                  0x3u
#define FTMRH_FSTAT_MGSTAT_SHIFT                 0
#define FTMRH_FSTAT_MGSTAT_WIDTH                 2
#define FTMRH_FSTAT_MGSTAT(x)                    (((uint8_t)(((uint8_t)(x))<<FTMRH_FSTAT_MGSTAT_SHIFT))&FTMRH_FSTAT_MGSTAT_MASK)
#define FTMRH_FSTAT_MGBUSY_MASK                  0x8u
#define FTMRH_FSTAT_MGBUSY_SHIFT                 3
#define FTMRH_FSTAT_MGBUSY_WIDTH                 1
#define FTMRH_FSTAT_MGBUSY(x)                    (((uint8_t)(((uint8_t)(x))<<FTMRH_FSTAT_MGBUSY_SHIFT))&FTMRH_FSTAT_MGBUSY_MASK)
#define FTMRH_FSTAT_FPVIOL_MASK                  0x10u
#define FTMRH_FSTAT_FPVIOL_SHIFT                 4
#define FTMRH_FSTAT_FPVIOL_WIDTH                 1
#define FTMRH_FSTAT_FPVIOL(x)                    (((uint8_t)(((uint8_t)(x))<<FTMRH_FSTAT_FPVIOL_SHIFT))&FTMRH_FSTAT_FPVIOL_MASK)
#define FTMRH_FSTAT_ACCERR_MASK                  0x20u
#define FTMRH_FSTAT_ACCERR_SHIFT                 5
#define FTMRH_FSTAT_ACCERR_WIDTH                 1
#define FTMRH_FSTAT_ACCERR(x)                    (((uint8_t)(((uint8_t)(x))<<FTMRH_FSTAT_ACCERR_SHIFT))&FTMRH_FSTAT_ACCERR_MASK)
#define FTMRH_FSTAT_CCIF_MASK                    0x80u
#define FTMRH_FSTAT_CCIF_SHIFT                   7
#define FTMRH_FSTAT_CCIF_WIDTH                   1
#define FTMRH_FSTAT_CCIF(x)                      (((uint8_t)(((uint8_t)(x))<<FTMRH_FSTAT_CCIF_SHIFT))&FTMRH_FSTAT_CCIF_MASK)
/* FERSTAT Bit Fields */
#define FTMRH_FERSTAT_SFDIF_MASK                 0x1u
#define FTMRH_FERSTAT_SFDIF_SHIFT                0
#define FTMRH_FERSTAT_SFDIF_WIDTH                1
#define FTMRH_FERSTAT_SFDIF(x)                   (((uint8_t)(((uint8_t)(x))<<FTMRH_FERSTAT_SFDIF_SHIFT))&FTMRH_FERSTAT_SFDIF_MASK)
#define FTMRH_FERSTAT_DFDIF_MASK                 0x2u
#define FTMRH_FERSTAT_DFDIF_SHIFT                1
#define FTMRH_FERSTAT_DFDIF_WIDTH                1
#define FTMRH_FERSTAT_DFDIF(x)                   (((uint8_t)(((uint8_t)(x))<<FTMRH_FERSTAT_DFDIF_SHIFT))&FTMRH_FERSTAT_DFDIF_MASK)
/* FPROT Bit Fields */
#define FTMRH_FPROT_FPLS_MASK                    0x3u
#define FTMRH_FPROT_FPLS_SHIFT                   0
#define FTMRH_FPROT_FPLS_WIDTH                   2
#define FTMRH_FPROT_FPLS(x)                      (((uint8_t)(((uint8_t)(x))<<FTMRH_FPROT_FPLS_SHIFT))&FTMRH_FPROT_FPLS_MASK)
#define FTMRH_FPROT_FPLDIS_MASK                  0x4u
#define FTMRH_FPROT_FPLDIS_SHIFT                 2
#define FTMRH_FPROT_FPLDIS_WIDTH                 1
#define FTMRH_FPROT_FPLDIS(x)                    (((uint8_t)(((uint8_t)(x))<<FTMRH_FPROT_FPLDIS_SHIFT))&FTMRH_FPROT_FPLDIS_MASK)
#define FTMRH_FPROT_FPHS_MASK                    0x18u
#define FTMRH_FPROT_FPHS_SHIFT                   3
#define FTMRH_FPROT_FPHS_WIDTH                   2
#define FTMRH_FPROT_FPHS(x)                      (((uint8_t)(((uint8_t)(x))<<FTMRH_FPROT_FPHS_SHIFT))&FTMRH_FPROT_FPHS_MASK)
#define FTMRH_FPROT_FPHDIS_MASK                  0x20u
#define FTMRH_FPROT_FPHDIS_SHIFT                 5
#define FTMRH_FPROT_FPHDIS_WIDTH                 1
#define FTMRH_FPROT_FPHDIS(x)                    (((uint8_t)(((uint8_t)(x))<<FTMRH_FPROT_FPHDIS_SHIFT))&FTMRH_FPROT_FPHDIS_MASK)
#define FTMRH_FPROT_RNV6_MASK                    0x40u
#define FTMRH_FPROT_RNV6_SHIFT                   6
#define FTMRH_FPROT_RNV6_WIDTH                   1
#define FTMRH_FPROT_RNV6(x)                      (((uint8_t)(((uint8_t)(x))<<FTMRH_FPROT_RNV6_SHIFT))&FTMRH_FPROT_RNV6_MASK)
#define FTMRH_FPROT_FPOPEN_MASK                  0x80u
#define FTMRH_FPROT_FPOPEN_SHIFT                 7
#define FTMRH_FPROT_FPOPEN_WIDTH                 1
#define FTMRH_FPROT_FPOPEN(x)                    (((uint8_t)(((uint8_t)(x))<<FTMRH_FPROT_FPOPEN_SHIFT))&FTMRH_FPROT_FPOPEN_MASK)
/* EEPROT Bit Fields */
#define FTMRH_EEPROT_DPS_MASK                    0x7u
#define FTMRH_EEPROT_DPS_SHIFT                   0
#define FTMRH_EEPROT_DPS_WIDTH                   3
#define FTMRH_EEPROT_DPS(x)                      (((uint8_t)(((uint8_t)(x))<<FTMRH_EEPROT_DPS_SHIFT))&FTMRH_EEPROT_DPS_MASK)
#define FTMRH_EEPROT_DPOPEN_MASK                 0x80u
#define FTMRH_EEPROT_DPOPEN_SHIFT                7
#define FTMRH_EEPROT_DPOPEN_WIDTH                1
#define FTMRH_EEPROT_DPOPEN(x)                   (((uint8_t)(((uint8_t)(x))<<FTMRH_EEPROT_DPOPEN_SHIFT))&FTMRH_EEPROT_DPOPEN_MASK)
/* FCCOBHI Bit Fields */
#define FTMRH_FCCOBHI_CCOB_MASK                  0xFFu
#define FTMRH_FCCOBHI_CCOB_SHIFT                 0
#define FTMRH_FCCOBHI_CCOB_WIDTH                 8
#define FTMRH_FCCOBHI_CCOB(x)                    (((uint8_t)(((uint8_t)(x))<<FTMRH_FCCOBHI_CCOB_SHIFT))&FTMRH_FCCOBHI_CCOB_MASK)
/* FCCOBLO Bit Fields */
#define FTMRH_FCCOBLO_CCOB_MASK                  0xFFu
#define FTMRH_FCCOBLO_CCOB_SHIFT                 0
#define FTMRH_FCCOBLO_CCOB_WIDTH                 8
#define FTMRH_FCCOBLO_CCOB(x)                    (((uint8_t)(((uint8_t)(x))<<FTMRH_FCCOBLO_CCOB_SHIFT))&FTMRH_FCCOBLO_CCOB_MASK)
/* FOPT Bit Fields */
#define FTMRH_FOPT_NV_MASK                       0xFFu
#define FTMRH_FOPT_NV_SHIFT                      0
#define FTMRH_FOPT_NV_WIDTH                      8
#define FTMRH_FOPT_NV(x)                         (((uint8_t)(((uint8_t)(x))<<FTMRH_FOPT_NV_SHIFT))&FTMRH_FOPT_NV_MASK)

/*!
 * @}
 */ /* end of group FTMRH_Register_Masks */


/* FTMRH - Peripheral instance base addresses */
/** Peripheral FTMRH base pointer */
#define FTMRH_BASE_PTR                           ((FTMRH_MemMapPtr)0x40020000u)
/** Array initializer of FTMRH peripheral base pointers */
#define FTMRH_BASE_PTRS                          { FTMRH_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- FTMRH - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTMRH_Register_Accessor_Macros FTMRH - Register accessor macros
 * @{
 */


/* FTMRH - Register instance definitions */
/* FTMRH */
#define FTMRH_FCLKDIV                            FTMRH_FCLKDIV_REG(FTMRH_BASE_PTR)
#define FTMRH_FSEC                               FTMRH_FSEC_REG(FTMRH_BASE_PTR)
#define FTMRH_FCCOBIX                            FTMRH_FCCOBIX_REG(FTMRH_BASE_PTR)
#define FTMRH_FCNFG                              FTMRH_FCNFG_REG(FTMRH_BASE_PTR)
#define FTMRH_FERCNFG                            FTMRH_FERCNFG_REG(FTMRH_BASE_PTR)
#define FTMRH_FSTAT                              FTMRH_FSTAT_REG(FTMRH_BASE_PTR)
#define FTMRH_FERSTAT                            FTMRH_FERSTAT_REG(FTMRH_BASE_PTR)
#define FTMRH_FPROT                              FTMRH_FPROT_REG(FTMRH_BASE_PTR)
#define FTMRH_EEPROT                             FTMRH_EEPROT_REG(FTMRH_BASE_PTR)
#define FTMRH_FCCOBHI                            FTMRH_FCCOBHI_REG(FTMRH_BASE_PTR)
#define FTMRH_FCCOBLO                            FTMRH_FCCOBLO_REG(FTMRH_BASE_PTR)
#define FTMRH_FOPT                               FTMRH_FOPT_REG(FTMRH_BASE_PTR)

/*!
 * @}
 */ /* end of group FTMRH_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group FTMRH_Peripheral */


/* ----------------------------------------------------------------------------
   -- GPIO
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPIO_Peripheral GPIO
 * @{
 */

/** GPIO - Peripheral register structure */
typedef struct GPIO_MemMap {
  uint32_t PDOR;                                   /**< Port Data Output Register, offset: 0x0 */
  uint32_t PSOR;                                   /**< Port Set Output Register, offset: 0x4 */
  uint32_t PCOR;                                   /**< Port Clear Output Register, offset: 0x8 */
  uint32_t PTOR;                                   /**< Port Toggle Output Register, offset: 0xC */
  uint32_t PDIR;                                   /**< Port Data Input Register, offset: 0x10 */
  uint32_t PDDR;                                   /**< Port Data Direction Register, offset: 0x14 */
  uint32_t PIDR;                                   /**< Port Input Disable Register, offset: 0x18 */
} volatile *GPIO_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- GPIO - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPIO_Register_Accessor_Macros GPIO - Register accessor macros
 * @{
 */


/* GPIO - Register accessors */
#define GPIO_PDOR_REG(base)                      ((base)->PDOR)
#define GPIO_PSOR_REG(base)                      ((base)->PSOR)
#define GPIO_PCOR_REG(base)                      ((base)->PCOR)
#define GPIO_PTOR_REG(base)                      ((base)->PTOR)
#define GPIO_PDIR_REG(base)                      ((base)->PDIR)
#define GPIO_PDDR_REG(base)                      ((base)->PDDR)
#define GPIO_PIDR_REG(base)                      ((base)->PIDR)

/*!
 * @}
 */ /* end of group GPIO_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- GPIO Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPIO_Register_Masks GPIO Register Masks
 * @{
 */

/* PDOR Bit Fields */
#define GPIO_PDOR_PDO_MASK                       0xFFFFFFFFu
#define GPIO_PDOR_PDO_SHIFT                      0
#define GPIO_PDOR_PDO_WIDTH                      32
#define GPIO_PDOR_PDO(x)                         (((uint32_t)(((uint32_t)(x))<<GPIO_PDOR_PDO_SHIFT))&GPIO_PDOR_PDO_MASK)
/* PSOR Bit Fields */
#define GPIO_PSOR_PTSO_MASK                      0xFFFFFFFFu
#define GPIO_PSOR_PTSO_SHIFT                     0
#define GPIO_PSOR_PTSO_WIDTH                     32
#define GPIO_PSOR_PTSO(x)                        (((uint32_t)(((uint32_t)(x))<<GPIO_PSOR_PTSO_SHIFT))&GPIO_PSOR_PTSO_MASK)
/* PCOR Bit Fields */
#define GPIO_PCOR_PTCO_MASK                      0xFFFFFFFFu
#define GPIO_PCOR_PTCO_SHIFT                     0
#define GPIO_PCOR_PTCO_WIDTH                     32
#define GPIO_PCOR_PTCO(x)                        (((uint32_t)(((uint32_t)(x))<<GPIO_PCOR_PTCO_SHIFT))&GPIO_PCOR_PTCO_MASK)
/* PTOR Bit Fields */
#define GPIO_PTOR_PTTO_MASK                      0xFFFFFFFFu
#define GPIO_PTOR_PTTO_SHIFT                     0
#define GPIO_PTOR_PTTO_WIDTH                     32
#define GPIO_PTOR_PTTO(x)                        (((uint32_t)(((uint32_t)(x))<<GPIO_PTOR_PTTO_SHIFT))&GPIO_PTOR_PTTO_MASK)
/* PDIR Bit Fields */
#define GPIO_PDIR_PDI_MASK                       0xFFFFFFFFu
#define GPIO_PDIR_PDI_SHIFT                      0
#define GPIO_PDIR_PDI_WIDTH                      32
#define GPIO_PDIR_PDI(x)                         (((uint32_t)(((uint32_t)(x))<<GPIO_PDIR_PDI_SHIFT))&GPIO_PDIR_PDI_MASK)
/* PDDR Bit Fields */
#define GPIO_PDDR_PDD_MASK                       0xFFFFFFFFu
#define GPIO_PDDR_PDD_SHIFT                      0
#define GPIO_PDDR_PDD_WIDTH                      32
#define GPIO_PDDR_PDD(x)                         (((uint32_t)(((uint32_t)(x))<<GPIO_PDDR_PDD_SHIFT))&GPIO_PDDR_PDD_MASK)
/* PIDR Bit Fields */
#define GPIO_PIDR_PID_MASK                       0xFFFFFFFFu
#define GPIO_PIDR_PID_SHIFT                      0
#define GPIO_PIDR_PID_WIDTH                      32
#define GPIO_PIDR_PID(x)                         (((uint32_t)(((uint32_t)(x))<<GPIO_PIDR_PID_SHIFT))&GPIO_PIDR_PID_MASK)

/*!
 * @}
 */ /* end of group GPIO_Register_Masks */


/* GPIO - Peripheral instance base addresses */
/** Peripheral GPIOA base pointer */
#define GPIOA_BASE_PTR                           ((GPIO_MemMapPtr)0x400FF000u)
/** Peripheral GPIOB base pointer */
#define GPIOB_BASE_PTR                           ((GPIO_MemMapPtr)0x400FF040u)
/** Array initializer of GPIO peripheral base pointers */
#define GPIO_BASE_PTRS                           { GPIOA_BASE_PTR, GPIOB_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- GPIO - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPIO_Register_Accessor_Macros GPIO - Register accessor macros
 * @{
 */


/* GPIO - Register instance definitions */
/* GPIOA */
#define GPIOA_PDOR                               GPIO_PDOR_REG(GPIOA_BASE_PTR)
#define GPIOA_PSOR                               GPIO_PSOR_REG(GPIOA_BASE_PTR)
#define GPIOA_PCOR                               GPIO_PCOR_REG(GPIOA_BASE_PTR)
#define GPIOA_PTOR                               GPIO_PTOR_REG(GPIOA_BASE_PTR)
#define GPIOA_PDIR                               GPIO_PDIR_REG(GPIOA_BASE_PTR)
#define GPIOA_PDDR                               GPIO_PDDR_REG(GPIOA_BASE_PTR)
#define GPIOA_PIDR                               GPIO_PIDR_REG(GPIOA_BASE_PTR)
/* GPIOB */
#define GPIOB_PDOR                               GPIO_PDOR_REG(GPIOB_BASE_PTR)
#define GPIOB_PSOR                               GPIO_PSOR_REG(GPIOB_BASE_PTR)
#define GPIOB_PCOR                               GPIO_PCOR_REG(GPIOB_BASE_PTR)
#define GPIOB_PTOR                               GPIO_PTOR_REG(GPIOB_BASE_PTR)
#define GPIOB_PDIR                               GPIO_PDIR_REG(GPIOB_BASE_PTR)
#define GPIOB_PDDR                               GPIO_PDDR_REG(GPIOB_BASE_PTR)
#define GPIOB_PIDR                               GPIO_PIDR_REG(GPIOB_BASE_PTR)

/*!
 * @}
 */ /* end of group GPIO_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group GPIO_Peripheral */


/* ----------------------------------------------------------------------------
   -- I2C
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2C_Peripheral I2C
 * @{
 */

/** I2C - Peripheral register structure */
typedef struct I2C_MemMap {
  uint8_t A1;                                      /**< I2C Address Register 1, offset: 0x0 */
  uint8_t F;                                       /**< I2C Frequency Divider register, offset: 0x1 */
  uint8_t C1;                                      /**< I2C Control Register 1, offset: 0x2 */
  uint8_t S;                                       /**< I2C Status register, offset: 0x3 */
  uint8_t D;                                       /**< I2C Data I/O register, offset: 0x4 */
  uint8_t C2;                                      /**< I2C Control Register 2, offset: 0x5 */
  uint8_t FLT;                                     /**< I2C Programmable Input Glitch Filter register, offset: 0x6 */
  uint8_t RA;                                      /**< I2C Range Address register, offset: 0x7 */
  uint8_t SMB;                                     /**< I2C SMBus Control and Status register, offset: 0x8 */
  uint8_t A2;                                      /**< I2C Address Register 2, offset: 0x9 */
  uint8_t SLTH;                                    /**< I2C SCL Low Timeout Register High, offset: 0xA */
  uint8_t SLTL;                                    /**< I2C SCL Low Timeout Register Low, offset: 0xB */
} volatile *I2C_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- I2C - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2C_Register_Accessor_Macros I2C - Register accessor macros
 * @{
 */


/* I2C - Register accessors */
#define I2C_A1_REG(base)                         ((base)->A1)
#define I2C_F_REG(base)                          ((base)->F)
#define I2C_C1_REG(base)                         ((base)->C1)
#define I2C_S_REG(base)                          ((base)->S)
#define I2C_D_REG(base)                          ((base)->D)
#define I2C_C2_REG(base)                         ((base)->C2)
#define I2C_FLT_REG(base)                        ((base)->FLT)
#define I2C_RA_REG(base)                         ((base)->RA)
#define I2C_SMB_REG(base)                        ((base)->SMB)
#define I2C_A2_REG(base)                         ((base)->A2)
#define I2C_SLTH_REG(base)                       ((base)->SLTH)
#define I2C_SLTL_REG(base)                       ((base)->SLTL)

/*!
 * @}
 */ /* end of group I2C_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- I2C Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2C_Register_Masks I2C Register Masks
 * @{
 */

/* A1 Bit Fields */
#define I2C_A1_AD_MASK                           0xFEu
#define I2C_A1_AD_SHIFT                          1
#define I2C_A1_AD_WIDTH                          7
#define I2C_A1_AD(x)                             (((uint8_t)(((uint8_t)(x))<<I2C_A1_AD_SHIFT))&I2C_A1_AD_MASK)
/* F Bit Fields */
#define I2C_F_ICR_MASK                           0x3Fu
#define I2C_F_ICR_SHIFT                          0
#define I2C_F_ICR_WIDTH                          6
#define I2C_F_ICR(x)                             (((uint8_t)(((uint8_t)(x))<<I2C_F_ICR_SHIFT))&I2C_F_ICR_MASK)
#define I2C_F_MULT_MASK                          0xC0u
#define I2C_F_MULT_SHIFT                         6
#define I2C_F_MULT_WIDTH                         2
#define I2C_F_MULT(x)                            (((uint8_t)(((uint8_t)(x))<<I2C_F_MULT_SHIFT))&I2C_F_MULT_MASK)
/* C1 Bit Fields */
#define I2C_C1_WUEN_MASK                         0x2u
#define I2C_C1_WUEN_SHIFT                        1
#define I2C_C1_WUEN_WIDTH                        1
#define I2C_C1_WUEN(x)                           (((uint8_t)(((uint8_t)(x))<<I2C_C1_WUEN_SHIFT))&I2C_C1_WUEN_MASK)
#define I2C_C1_RSTA_MASK                         0x4u
#define I2C_C1_RSTA_SHIFT                        2
#define I2C_C1_RSTA_WIDTH                        1
#define I2C_C1_RSTA(x)                           (((uint8_t)(((uint8_t)(x))<<I2C_C1_RSTA_SHIFT))&I2C_C1_RSTA_MASK)
#define I2C_C1_TXAK_MASK                         0x8u
#define I2C_C1_TXAK_SHIFT                        3
#define I2C_C1_TXAK_WIDTH                        1
#define I2C_C1_TXAK(x)                           (((uint8_t)(((uint8_t)(x))<<I2C_C1_TXAK_SHIFT))&I2C_C1_TXAK_MASK)
#define I2C_C1_TX_MASK                           0x10u
#define I2C_C1_TX_SHIFT                          4
#define I2C_C1_TX_WIDTH                          1
#define I2C_C1_TX(x)                             (((uint8_t)(((uint8_t)(x))<<I2C_C1_TX_SHIFT))&I2C_C1_TX_MASK)
#define I2C_C1_MST_MASK                          0x20u
#define I2C_C1_MST_SHIFT                         5
#define I2C_C1_MST_WIDTH                         1
#define I2C_C1_MST(x)                            (((uint8_t)(((uint8_t)(x))<<I2C_C1_MST_SHIFT))&I2C_C1_MST_MASK)
#define I2C_C1_IICIE_MASK                        0x40u
#define I2C_C1_IICIE_SHIFT                       6
#define I2C_C1_IICIE_WIDTH                       1
#define I2C_C1_IICIE(x)                          (((uint8_t)(((uint8_t)(x))<<I2C_C1_IICIE_SHIFT))&I2C_C1_IICIE_MASK)
#define I2C_C1_IICEN_MASK                        0x80u
#define I2C_C1_IICEN_SHIFT                       7
#define I2C_C1_IICEN_WIDTH                       1
#define I2C_C1_IICEN(x)                          (((uint8_t)(((uint8_t)(x))<<I2C_C1_IICEN_SHIFT))&I2C_C1_IICEN_MASK)
/* S Bit Fields */
#define I2C_S_RXAK_MASK                          0x1u
#define I2C_S_RXAK_SHIFT                         0
#define I2C_S_RXAK_WIDTH                         1
#define I2C_S_RXAK(x)                            (((uint8_t)(((uint8_t)(x))<<I2C_S_RXAK_SHIFT))&I2C_S_RXAK_MASK)
#define I2C_S_IICIF_MASK                         0x2u
#define I2C_S_IICIF_SHIFT                        1
#define I2C_S_IICIF_WIDTH                        1
#define I2C_S_IICIF(x)                           (((uint8_t)(((uint8_t)(x))<<I2C_S_IICIF_SHIFT))&I2C_S_IICIF_MASK)
#define I2C_S_SRW_MASK                           0x4u
#define I2C_S_SRW_SHIFT                          2
#define I2C_S_SRW_WIDTH                          1
#define I2C_S_SRW(x)                             (((uint8_t)(((uint8_t)(x))<<I2C_S_SRW_SHIFT))&I2C_S_SRW_MASK)
#define I2C_S_RAM_MASK                           0x8u
#define I2C_S_RAM_SHIFT                          3
#define I2C_S_RAM_WIDTH                          1
#define I2C_S_RAM(x)                             (((uint8_t)(((uint8_t)(x))<<I2C_S_RAM_SHIFT))&I2C_S_RAM_MASK)
#define I2C_S_ARBL_MASK                          0x10u
#define I2C_S_ARBL_SHIFT                         4
#define I2C_S_ARBL_WIDTH                         1
#define I2C_S_ARBL(x)                            (((uint8_t)(((uint8_t)(x))<<I2C_S_ARBL_SHIFT))&I2C_S_ARBL_MASK)
#define I2C_S_BUSY_MASK                          0x20u
#define I2C_S_BUSY_SHIFT                         5
#define I2C_S_BUSY_WIDTH                         1
#define I2C_S_BUSY(x)                            (((uint8_t)(((uint8_t)(x))<<I2C_S_BUSY_SHIFT))&I2C_S_BUSY_MASK)
#define I2C_S_IAAS_MASK                          0x40u
#define I2C_S_IAAS_SHIFT                         6
#define I2C_S_IAAS_WIDTH                         1
#define I2C_S_IAAS(x)                            (((uint8_t)(((uint8_t)(x))<<I2C_S_IAAS_SHIFT))&I2C_S_IAAS_MASK)
#define I2C_S_TCF_MASK                           0x80u
#define I2C_S_TCF_SHIFT                          7
#define I2C_S_TCF_WIDTH                          1
#define I2C_S_TCF(x)                             (((uint8_t)(((uint8_t)(x))<<I2C_S_TCF_SHIFT))&I2C_S_TCF_MASK)
/* D Bit Fields */
#define I2C_D_DATA_MASK                          0xFFu
#define I2C_D_DATA_SHIFT                         0
#define I2C_D_DATA_WIDTH                         8
#define I2C_D_DATA(x)                            (((uint8_t)(((uint8_t)(x))<<I2C_D_DATA_SHIFT))&I2C_D_DATA_MASK)
/* C2 Bit Fields */
#define I2C_C2_AD_MASK                           0x7u
#define I2C_C2_AD_SHIFT                          0
#define I2C_C2_AD_WIDTH                          3
#define I2C_C2_AD(x)                             (((uint8_t)(((uint8_t)(x))<<I2C_C2_AD_SHIFT))&I2C_C2_AD_MASK)
#define I2C_C2_RMEN_MASK                         0x8u
#define I2C_C2_RMEN_SHIFT                        3
#define I2C_C2_RMEN_WIDTH                        1
#define I2C_C2_RMEN(x)                           (((uint8_t)(((uint8_t)(x))<<I2C_C2_RMEN_SHIFT))&I2C_C2_RMEN_MASK)
#define I2C_C2_SBRC_MASK                         0x10u
#define I2C_C2_SBRC_SHIFT                        4
#define I2C_C2_SBRC_WIDTH                        1
#define I2C_C2_SBRC(x)                           (((uint8_t)(((uint8_t)(x))<<I2C_C2_SBRC_SHIFT))&I2C_C2_SBRC_MASK)
#define I2C_C2_ADEXT_MASK                        0x40u
#define I2C_C2_ADEXT_SHIFT                       6
#define I2C_C2_ADEXT_WIDTH                       1
#define I2C_C2_ADEXT(x)                          (((uint8_t)(((uint8_t)(x))<<I2C_C2_ADEXT_SHIFT))&I2C_C2_ADEXT_MASK)
#define I2C_C2_GCAEN_MASK                        0x80u
#define I2C_C2_GCAEN_SHIFT                       7
#define I2C_C2_GCAEN_WIDTH                       1
#define I2C_C2_GCAEN(x)                          (((uint8_t)(((uint8_t)(x))<<I2C_C2_GCAEN_SHIFT))&I2C_C2_GCAEN_MASK)
/* FLT Bit Fields */
#define I2C_FLT_FLT_MASK                         0xFu
#define I2C_FLT_FLT_SHIFT                        0
#define I2C_FLT_FLT_WIDTH                        4
#define I2C_FLT_FLT(x)                           (((uint8_t)(((uint8_t)(x))<<I2C_FLT_FLT_SHIFT))&I2C_FLT_FLT_MASK)
#define I2C_FLT_STARTF_MASK                      0x10u
#define I2C_FLT_STARTF_SHIFT                     4
#define I2C_FLT_STARTF_WIDTH                     1
#define I2C_FLT_STARTF(x)                        (((uint8_t)(((uint8_t)(x))<<I2C_FLT_STARTF_SHIFT))&I2C_FLT_STARTF_MASK)
#define I2C_FLT_SSIE_MASK                        0x20u
#define I2C_FLT_SSIE_SHIFT                       5
#define I2C_FLT_SSIE_WIDTH                       1
#define I2C_FLT_SSIE(x)                          (((uint8_t)(((uint8_t)(x))<<I2C_FLT_SSIE_SHIFT))&I2C_FLT_SSIE_MASK)
#define I2C_FLT_STOPF_MASK                       0x40u
#define I2C_FLT_STOPF_SHIFT                      6
#define I2C_FLT_STOPF_WIDTH                      1
#define I2C_FLT_STOPF(x)                         (((uint8_t)(((uint8_t)(x))<<I2C_FLT_STOPF_SHIFT))&I2C_FLT_STOPF_MASK)
#define I2C_FLT_SHEN_MASK                        0x80u
#define I2C_FLT_SHEN_SHIFT                       7
#define I2C_FLT_SHEN_WIDTH                       1
#define I2C_FLT_SHEN(x)                          (((uint8_t)(((uint8_t)(x))<<I2C_FLT_SHEN_SHIFT))&I2C_FLT_SHEN_MASK)
/* RA Bit Fields */
#define I2C_RA_RAD_MASK                          0xFEu
#define I2C_RA_RAD_SHIFT                         1
#define I2C_RA_RAD_WIDTH                         7
#define I2C_RA_RAD(x)                            (((uint8_t)(((uint8_t)(x))<<I2C_RA_RAD_SHIFT))&I2C_RA_RAD_MASK)
/* SMB Bit Fields */
#define I2C_SMB_SHTF2IE_MASK                     0x1u
#define I2C_SMB_SHTF2IE_SHIFT                    0
#define I2C_SMB_SHTF2IE_WIDTH                    1
#define I2C_SMB_SHTF2IE(x)                       (((uint8_t)(((uint8_t)(x))<<I2C_SMB_SHTF2IE_SHIFT))&I2C_SMB_SHTF2IE_MASK)
#define I2C_SMB_SHTF2_MASK                       0x2u
#define I2C_SMB_SHTF2_SHIFT                      1
#define I2C_SMB_SHTF2_WIDTH                      1
#define I2C_SMB_SHTF2(x)                         (((uint8_t)(((uint8_t)(x))<<I2C_SMB_SHTF2_SHIFT))&I2C_SMB_SHTF2_MASK)
#define I2C_SMB_SHTF1_MASK                       0x4u
#define I2C_SMB_SHTF1_SHIFT                      2
#define I2C_SMB_SHTF1_WIDTH                      1
#define I2C_SMB_SHTF1(x)                         (((uint8_t)(((uint8_t)(x))<<I2C_SMB_SHTF1_SHIFT))&I2C_SMB_SHTF1_MASK)
#define I2C_SMB_SLTF_MASK                        0x8u
#define I2C_SMB_SLTF_SHIFT                       3
#define I2C_SMB_SLTF_WIDTH                       1
#define I2C_SMB_SLTF(x)                          (((uint8_t)(((uint8_t)(x))<<I2C_SMB_SLTF_SHIFT))&I2C_SMB_SLTF_MASK)
#define I2C_SMB_TCKSEL_MASK                      0x10u
#define I2C_SMB_TCKSEL_SHIFT                     4
#define I2C_SMB_TCKSEL_WIDTH                     1
#define I2C_SMB_TCKSEL(x)                        (((uint8_t)(((uint8_t)(x))<<I2C_SMB_TCKSEL_SHIFT))&I2C_SMB_TCKSEL_MASK)
#define I2C_SMB_SIICAEN_MASK                     0x20u
#define I2C_SMB_SIICAEN_SHIFT                    5
#define I2C_SMB_SIICAEN_WIDTH                    1
#define I2C_SMB_SIICAEN(x)                       (((uint8_t)(((uint8_t)(x))<<I2C_SMB_SIICAEN_SHIFT))&I2C_SMB_SIICAEN_MASK)
#define I2C_SMB_ALERTEN_MASK                     0x40u
#define I2C_SMB_ALERTEN_SHIFT                    6
#define I2C_SMB_ALERTEN_WIDTH                    1
#define I2C_SMB_ALERTEN(x)                       (((uint8_t)(((uint8_t)(x))<<I2C_SMB_ALERTEN_SHIFT))&I2C_SMB_ALERTEN_MASK)
#define I2C_SMB_FACK_MASK                        0x80u
#define I2C_SMB_FACK_SHIFT                       7
#define I2C_SMB_FACK_WIDTH                       1
#define I2C_SMB_FACK(x)                          (((uint8_t)(((uint8_t)(x))<<I2C_SMB_FACK_SHIFT))&I2C_SMB_FACK_MASK)
/* A2 Bit Fields */
#define I2C_A2_SAD_MASK                          0xFEu
#define I2C_A2_SAD_SHIFT                         1
#define I2C_A2_SAD_WIDTH                         7
#define I2C_A2_SAD(x)                            (((uint8_t)(((uint8_t)(x))<<I2C_A2_SAD_SHIFT))&I2C_A2_SAD_MASK)
/* SLTH Bit Fields */
#define I2C_SLTH_SSLT_MASK                       0xFFu
#define I2C_SLTH_SSLT_SHIFT                      0
#define I2C_SLTH_SSLT_WIDTH                      8
#define I2C_SLTH_SSLT(x)                         (((uint8_t)(((uint8_t)(x))<<I2C_SLTH_SSLT_SHIFT))&I2C_SLTH_SSLT_MASK)
/* SLTL Bit Fields */
#define I2C_SLTL_SSLT_MASK                       0xFFu
#define I2C_SLTL_SSLT_SHIFT                      0
#define I2C_SLTL_SSLT_WIDTH                      8
#define I2C_SLTL_SSLT(x)                         (((uint8_t)(((uint8_t)(x))<<I2C_SLTL_SSLT_SHIFT))&I2C_SLTL_SSLT_MASK)

/*!
 * @}
 */ /* end of group I2C_Register_Masks */


/* I2C - Peripheral instance base addresses */
/** Peripheral I2C0 base pointer */
#define I2C0_BASE_PTR                            ((I2C_MemMapPtr)0x40066000u)
/** Array initializer of I2C peripheral base pointers */
#define I2C_BASE_PTRS                            { I2C0_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- I2C - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2C_Register_Accessor_Macros I2C - Register accessor macros
 * @{
 */


/* I2C - Register instance definitions */
/* I2C0 */
#define I2C0_A1                                  I2C_A1_REG(I2C0_BASE_PTR)
#define I2C0_F                                   I2C_F_REG(I2C0_BASE_PTR)
#define I2C0_C1                                  I2C_C1_REG(I2C0_BASE_PTR)
#define I2C0_S                                   I2C_S_REG(I2C0_BASE_PTR)
#define I2C0_D                                   I2C_D_REG(I2C0_BASE_PTR)
#define I2C0_C2                                  I2C_C2_REG(I2C0_BASE_PTR)
#define I2C0_FLT                                 I2C_FLT_REG(I2C0_BASE_PTR)
#define I2C0_RA                                  I2C_RA_REG(I2C0_BASE_PTR)
#define I2C0_SMB                                 I2C_SMB_REG(I2C0_BASE_PTR)
#define I2C0_A2                                  I2C_A2_REG(I2C0_BASE_PTR)
#define I2C0_SLTH                                I2C_SLTH_REG(I2C0_BASE_PTR)
#define I2C0_SLTL                                I2C_SLTL_REG(I2C0_BASE_PTR)

/*!
 * @}
 */ /* end of group I2C_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group I2C_Peripheral */


/* ----------------------------------------------------------------------------
   -- ICS
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ICS_Peripheral ICS
 * @{
 */

/** ICS - Peripheral register structure */
typedef struct ICS_MemMap {
  uint8_t C1;                                      /**< ICS Control Register 1, offset: 0x0 */
  uint8_t C2;                                      /**< ICS Control Register 2, offset: 0x1 */
  uint8_t C3;                                      /**< ICS Control Register 3, offset: 0x2 */
  uint8_t C4;                                      /**< ICS Control Register 4, offset: 0x3 */
  uint8_t S;                                       /**< ICS Status Register, offset: 0x4 */
} volatile *ICS_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- ICS - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ICS_Register_Accessor_Macros ICS - Register accessor macros
 * @{
 */


/* ICS - Register accessors */
#define ICS_C1_REG(base)                         ((base)->C1)
#define ICS_C2_REG(base)                         ((base)->C2)
#define ICS_C3_REG(base)                         ((base)->C3)
#define ICS_C4_REG(base)                         ((base)->C4)
#define ICS_S_REG(base)                          ((base)->S)

/*!
 * @}
 */ /* end of group ICS_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- ICS Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ICS_Register_Masks ICS Register Masks
 * @{
 */

/* C1 Bit Fields */
#define ICS_C1_IREFSTEN_MASK                     0x1u
#define ICS_C1_IREFSTEN_SHIFT                    0
#define ICS_C1_IREFSTEN_WIDTH                    1
#define ICS_C1_IREFSTEN(x)                       (((uint8_t)(((uint8_t)(x))<<ICS_C1_IREFSTEN_SHIFT))&ICS_C1_IREFSTEN_MASK)
#define ICS_C1_IRCLKEN_MASK                      0x2u
#define ICS_C1_IRCLKEN_SHIFT                     1
#define ICS_C1_IRCLKEN_WIDTH                     1
#define ICS_C1_IRCLKEN(x)                        (((uint8_t)(((uint8_t)(x))<<ICS_C1_IRCLKEN_SHIFT))&ICS_C1_IRCLKEN_MASK)
#define ICS_C1_IREFS_MASK                        0x4u
#define ICS_C1_IREFS_SHIFT                       2
#define ICS_C1_IREFS_WIDTH                       1
#define ICS_C1_IREFS(x)                          (((uint8_t)(((uint8_t)(x))<<ICS_C1_IREFS_SHIFT))&ICS_C1_IREFS_MASK)
#define ICS_C1_RDIV_MASK                         0x38u
#define ICS_C1_RDIV_SHIFT                        3
#define ICS_C1_RDIV_WIDTH                        3
#define ICS_C1_RDIV(x)                           (((uint8_t)(((uint8_t)(x))<<ICS_C1_RDIV_SHIFT))&ICS_C1_RDIV_MASK)
#define ICS_C1_CLKS_MASK                         0xC0u
#define ICS_C1_CLKS_SHIFT                        6
#define ICS_C1_CLKS_WIDTH                        2
#define ICS_C1_CLKS(x)                           (((uint8_t)(((uint8_t)(x))<<ICS_C1_CLKS_SHIFT))&ICS_C1_CLKS_MASK)
/* C2 Bit Fields */
#define ICS_C2_LP_MASK                           0x10u
#define ICS_C2_LP_SHIFT                          4
#define ICS_C2_LP_WIDTH                          1
#define ICS_C2_LP(x)                             (((uint8_t)(((uint8_t)(x))<<ICS_C2_LP_SHIFT))&ICS_C2_LP_MASK)
#define ICS_C2_BDIV_MASK                         0xE0u
#define ICS_C2_BDIV_SHIFT                        5
#define ICS_C2_BDIV_WIDTH                        3
#define ICS_C2_BDIV(x)                           (((uint8_t)(((uint8_t)(x))<<ICS_C2_BDIV_SHIFT))&ICS_C2_BDIV_MASK)
/* C3 Bit Fields */
#define ICS_C3_SCTRIM_MASK                       0xFFu
#define ICS_C3_SCTRIM_SHIFT                      0
#define ICS_C3_SCTRIM_WIDTH                      8
#define ICS_C3_SCTRIM(x)                         (((uint8_t)(((uint8_t)(x))<<ICS_C3_SCTRIM_SHIFT))&ICS_C3_SCTRIM_MASK)
/* C4 Bit Fields */
#define ICS_C4_SCFTRIM_MASK                      0x1u
#define ICS_C4_SCFTRIM_SHIFT                     0
#define ICS_C4_SCFTRIM_WIDTH                     1
#define ICS_C4_SCFTRIM(x)                        (((uint8_t)(((uint8_t)(x))<<ICS_C4_SCFTRIM_SHIFT))&ICS_C4_SCFTRIM_MASK)
#define ICS_C4_CME_MASK                          0x20u
#define ICS_C4_CME_SHIFT                         5
#define ICS_C4_CME_WIDTH                         1
#define ICS_C4_CME(x)                            (((uint8_t)(((uint8_t)(x))<<ICS_C4_CME_SHIFT))&ICS_C4_CME_MASK)
#define ICS_C4_LOLIE_MASK                        0x80u
#define ICS_C4_LOLIE_SHIFT                       7
#define ICS_C4_LOLIE_WIDTH                       1
#define ICS_C4_LOLIE(x)                          (((uint8_t)(((uint8_t)(x))<<ICS_C4_LOLIE_SHIFT))&ICS_C4_LOLIE_MASK)
/* S Bit Fields */
#define ICS_S_CLKST_MASK                         0xCu
#define ICS_S_CLKST_SHIFT                        2
#define ICS_S_CLKST_WIDTH                        2
#define ICS_S_CLKST(x)                           (((uint8_t)(((uint8_t)(x))<<ICS_S_CLKST_SHIFT))&ICS_S_CLKST_MASK)
#define ICS_S_IREFST_MASK                        0x10u
#define ICS_S_IREFST_SHIFT                       4
#define ICS_S_IREFST_WIDTH                       1
#define ICS_S_IREFST(x)                          (((uint8_t)(((uint8_t)(x))<<ICS_S_IREFST_SHIFT))&ICS_S_IREFST_MASK)
#define ICS_S_LOCK_MASK                          0x40u
#define ICS_S_LOCK_SHIFT                         6
#define ICS_S_LOCK_WIDTH                         1
#define ICS_S_LOCK(x)                            (((uint8_t)(((uint8_t)(x))<<ICS_S_LOCK_SHIFT))&ICS_S_LOCK_MASK)
#define ICS_S_LOLS_MASK                          0x80u
#define ICS_S_LOLS_SHIFT                         7
#define ICS_S_LOLS_WIDTH                         1
#define ICS_S_LOLS(x)                            (((uint8_t)(((uint8_t)(x))<<ICS_S_LOLS_SHIFT))&ICS_S_LOLS_MASK)

/*!
 * @}
 */ /* end of group ICS_Register_Masks */


/* ICS - Peripheral instance base addresses */
/** Peripheral ICS base pointer */
#define ICS_BASE_PTR                             ((ICS_MemMapPtr)0x40064000u)
/** Array initializer of ICS peripheral base pointers */
#define ICS_BASE_PTRS                            { ICS_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- ICS - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ICS_Register_Accessor_Macros ICS - Register accessor macros
 * @{
 */


/* ICS - Register instance definitions */
/* ICS */
#define ICS_C1                                   ICS_C1_REG(ICS_BASE_PTR)
#define ICS_C2                                   ICS_C2_REG(ICS_BASE_PTR)
#define ICS_C3                                   ICS_C3_REG(ICS_BASE_PTR)
#define ICS_C4                                   ICS_C4_REG(ICS_BASE_PTR)
#define ICS_S                                    ICS_S_REG(ICS_BASE_PTR)

/*!
 * @}
 */ /* end of group ICS_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group ICS_Peripheral */


/* ----------------------------------------------------------------------------
   -- IRQ
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IRQ_Peripheral IRQ
 * @{
 */

/** IRQ - Peripheral register structure */
typedef struct IRQ_MemMap {
  uint8_t SC;                                      /**< Interrupt Pin Request Status and Control Register, offset: 0x0 */
} volatile *IRQ_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- IRQ - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IRQ_Register_Accessor_Macros IRQ - Register accessor macros
 * @{
 */


/* IRQ - Register accessors */
#define IRQ_SC_REG(base)                         ((base)->SC)

/*!
 * @}
 */ /* end of group IRQ_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- IRQ Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IRQ_Register_Masks IRQ Register Masks
 * @{
 */

/* SC Bit Fields */
#define IRQ_SC_IRQMOD_MASK                       0x1u
#define IRQ_SC_IRQMOD_SHIFT                      0
#define IRQ_SC_IRQMOD_WIDTH                      1
#define IRQ_SC_IRQMOD(x)                         (((uint8_t)(((uint8_t)(x))<<IRQ_SC_IRQMOD_SHIFT))&IRQ_SC_IRQMOD_MASK)
#define IRQ_SC_IRQIE_MASK                        0x2u
#define IRQ_SC_IRQIE_SHIFT                       1
#define IRQ_SC_IRQIE_WIDTH                       1
#define IRQ_SC_IRQIE(x)                          (((uint8_t)(((uint8_t)(x))<<IRQ_SC_IRQIE_SHIFT))&IRQ_SC_IRQIE_MASK)
#define IRQ_SC_IRQACK_MASK                       0x4u
#define IRQ_SC_IRQACK_SHIFT                      2
#define IRQ_SC_IRQACK_WIDTH                      1
#define IRQ_SC_IRQACK(x)                         (((uint8_t)(((uint8_t)(x))<<IRQ_SC_IRQACK_SHIFT))&IRQ_SC_IRQACK_MASK)
#define IRQ_SC_IRQF_MASK                         0x8u
#define IRQ_SC_IRQF_SHIFT                        3
#define IRQ_SC_IRQF_WIDTH                        1
#define IRQ_SC_IRQF(x)                           (((uint8_t)(((uint8_t)(x))<<IRQ_SC_IRQF_SHIFT))&IRQ_SC_IRQF_MASK)
#define IRQ_SC_IRQPE_MASK                        0x10u
#define IRQ_SC_IRQPE_SHIFT                       4
#define IRQ_SC_IRQPE_WIDTH                       1
#define IRQ_SC_IRQPE(x)                          (((uint8_t)(((uint8_t)(x))<<IRQ_SC_IRQPE_SHIFT))&IRQ_SC_IRQPE_MASK)
#define IRQ_SC_IRQEDG_MASK                       0x20u
#define IRQ_SC_IRQEDG_SHIFT                      5
#define IRQ_SC_IRQEDG_WIDTH                      1
#define IRQ_SC_IRQEDG(x)                         (((uint8_t)(((uint8_t)(x))<<IRQ_SC_IRQEDG_SHIFT))&IRQ_SC_IRQEDG_MASK)
#define IRQ_SC_IRQPDD_MASK                       0x40u
#define IRQ_SC_IRQPDD_SHIFT                      6
#define IRQ_SC_IRQPDD_WIDTH                      1
#define IRQ_SC_IRQPDD(x)                         (((uint8_t)(((uint8_t)(x))<<IRQ_SC_IRQPDD_SHIFT))&IRQ_SC_IRQPDD_MASK)

/*!
 * @}
 */ /* end of group IRQ_Register_Masks */


/* IRQ - Peripheral instance base addresses */
/** Peripheral IRQ base pointer */
#define IRQ_BASE_PTR                             ((IRQ_MemMapPtr)0x40031000u)
/** Array initializer of IRQ peripheral base pointers */
#define IRQ_BASE_PTRS                            { IRQ_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- IRQ - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IRQ_Register_Accessor_Macros IRQ - Register accessor macros
 * @{
 */


/* IRQ - Register instance definitions */
/* IRQ */
#define IRQ_SC                                   IRQ_SC_REG(IRQ_BASE_PTR)

/*!
 * @}
 */ /* end of group IRQ_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group IRQ_Peripheral */


/* ----------------------------------------------------------------------------
   -- KBI
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup KBI_Peripheral KBI
 * @{
 */

/** KBI - Peripheral register structure */
typedef struct KBI_MemMap {
  uint8_t SC;                                      /**< KBI Status and Control Register, offset: 0x0 */
  uint8_t PE;                                      /**< KBIx Pin Enable Register, offset: 0x1 */
  uint8_t ES;                                      /**< KBIx Edge Select Register, offset: 0x2 */
} volatile *KBI_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- KBI - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup KBI_Register_Accessor_Macros KBI - Register accessor macros
 * @{
 */


/* KBI - Register accessors */
#define KBI_SC_REG(base)                         ((base)->SC)
#define KBI_PE_REG(base)                         ((base)->PE)
#define KBI_ES_REG(base)                         ((base)->ES)

/*!
 * @}
 */ /* end of group KBI_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- KBI Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup KBI_Register_Masks KBI Register Masks
 * @{
 */

/* SC Bit Fields */
#define KBI_SC_KBMOD_MASK                        0x1u
#define KBI_SC_KBMOD_SHIFT                       0
#define KBI_SC_KBMOD_WIDTH                       1
#define KBI_SC_KBMOD(x)                          (((uint8_t)(((uint8_t)(x))<<KBI_SC_KBMOD_SHIFT))&KBI_SC_KBMOD_MASK)
#define KBI_SC_KBIE_MASK                         0x2u
#define KBI_SC_KBIE_SHIFT                        1
#define KBI_SC_KBIE_WIDTH                        1
#define KBI_SC_KBIE(x)                           (((uint8_t)(((uint8_t)(x))<<KBI_SC_KBIE_SHIFT))&KBI_SC_KBIE_MASK)
#define KBI_SC_KBACK_MASK                        0x4u
#define KBI_SC_KBACK_SHIFT                       2
#define KBI_SC_KBACK_WIDTH                       1
#define KBI_SC_KBACK(x)                          (((uint8_t)(((uint8_t)(x))<<KBI_SC_KBACK_SHIFT))&KBI_SC_KBACK_MASK)
#define KBI_SC_KBF_MASK                          0x8u
#define KBI_SC_KBF_SHIFT                         3
#define KBI_SC_KBF_WIDTH                         1
#define KBI_SC_KBF(x)                            (((uint8_t)(((uint8_t)(x))<<KBI_SC_KBF_SHIFT))&KBI_SC_KBF_MASK)
/* PE Bit Fields */
#define KBI_PE_KBIPE_MASK                        0xFFu
#define KBI_PE_KBIPE_SHIFT                       0
#define KBI_PE_KBIPE_WIDTH                       8
#define KBI_PE_KBIPE(x)                          (((uint8_t)(((uint8_t)(x))<<KBI_PE_KBIPE_SHIFT))&KBI_PE_KBIPE_MASK)
/* ES Bit Fields */
#define KBI_ES_KBEDG_MASK                        0xFFu
#define KBI_ES_KBEDG_SHIFT                       0
#define KBI_ES_KBEDG_WIDTH                       8
#define KBI_ES_KBEDG(x)                          (((uint8_t)(((uint8_t)(x))<<KBI_ES_KBEDG_SHIFT))&KBI_ES_KBEDG_MASK)

/*!
 * @}
 */ /* end of group KBI_Register_Masks */


/* KBI - Peripheral instance base addresses */
/** Peripheral KBI0 base pointer */
#define KBI0_BASE_PTR                            ((KBI_MemMapPtr)0x40079000u)
/** Peripheral KBI1 base pointer */
#define KBI1_BASE_PTR                            ((KBI_MemMapPtr)0x4007A000u)
/** Array initializer of KBI peripheral base pointers */
#define KBI_BASE_PTRS                            { KBI0_BASE_PTR, KBI1_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- KBI - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup KBI_Register_Accessor_Macros KBI - Register accessor macros
 * @{
 */


/* KBI - Register instance definitions */
/* KBI0 */
#define KBI0_SC                                  KBI_SC_REG(KBI0_BASE_PTR)
#define KBI0_PE                                  KBI_PE_REG(KBI0_BASE_PTR)
#define KBI0_ES                                  KBI_ES_REG(KBI0_BASE_PTR)
/* KBI1 */
#define KBI1_SC                                  KBI_SC_REG(KBI1_BASE_PTR)
#define KBI1_PE                                  KBI_PE_REG(KBI1_BASE_PTR)
#define KBI1_ES                                  KBI_ES_REG(KBI1_BASE_PTR)

/*!
 * @}
 */ /* end of group KBI_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group KBI_Peripheral */


/* ----------------------------------------------------------------------------
   -- MCM
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCM_Peripheral MCM
 * @{
 */

/** MCM - Peripheral register structure */
typedef struct MCM_MemMap {
  uint8_t RESERVED_0[8];
  uint16_t PLASC;                                  /**< Crossbar Switch (AXBS) Slave Configuration, offset: 0x8 */
  uint16_t PLAMC;                                  /**< Crossbar Switch (AXBS) Master Configuration, offset: 0xA */
  uint32_t PLACR;                                  /**< Platform Control Register, offset: 0xC */
} volatile *MCM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- MCM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCM_Register_Accessor_Macros MCM - Register accessor macros
 * @{
 */


/* MCM - Register accessors */
#define MCM_PLASC_REG(base)                      ((base)->PLASC)
#define MCM_PLAMC_REG(base)                      ((base)->PLAMC)
#define MCM_PLACR_REG(base)                      ((base)->PLACR)

/*!
 * @}
 */ /* end of group MCM_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- MCM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCM_Register_Masks MCM Register Masks
 * @{
 */

/* PLASC Bit Fields */
#define MCM_PLASC_ASC_MASK                       0xFFu
#define MCM_PLASC_ASC_SHIFT                      0
#define MCM_PLASC_ASC_WIDTH                      8
#define MCM_PLASC_ASC(x)                         (((uint16_t)(((uint16_t)(x))<<MCM_PLASC_ASC_SHIFT))&MCM_PLASC_ASC_MASK)
/* PLAMC Bit Fields */
#define MCM_PLAMC_AMC_MASK                       0xFFu
#define MCM_PLAMC_AMC_SHIFT                      0
#define MCM_PLAMC_AMC_WIDTH                      8
#define MCM_PLAMC_AMC(x)                         (((uint16_t)(((uint16_t)(x))<<MCM_PLAMC_AMC_SHIFT))&MCM_PLAMC_AMC_MASK)
/* PLACR Bit Fields */
#define MCM_PLACR_CFCC_MASK                      0x400u
#define MCM_PLACR_CFCC_SHIFT                     10
#define MCM_PLACR_CFCC_WIDTH                     1
#define MCM_PLACR_CFCC(x)                        (((uint32_t)(((uint32_t)(x))<<MCM_PLACR_CFCC_SHIFT))&MCM_PLACR_CFCC_MASK)
#define MCM_PLACR_DFCDA_MASK                     0x800u
#define MCM_PLACR_DFCDA_SHIFT                    11
#define MCM_PLACR_DFCDA_WIDTH                    1
#define MCM_PLACR_DFCDA(x)                       (((uint32_t)(((uint32_t)(x))<<MCM_PLACR_DFCDA_SHIFT))&MCM_PLACR_DFCDA_MASK)
#define MCM_PLACR_DFCIC_MASK                     0x1000u
#define MCM_PLACR_DFCIC_SHIFT                    12
#define MCM_PLACR_DFCIC_WIDTH                    1
#define MCM_PLACR_DFCIC(x)                       (((uint32_t)(((uint32_t)(x))<<MCM_PLACR_DFCIC_SHIFT))&MCM_PLACR_DFCIC_MASK)
#define MCM_PLACR_DFCC_MASK                      0x2000u
#define MCM_PLACR_DFCC_SHIFT                     13
#define MCM_PLACR_DFCC_WIDTH                     1
#define MCM_PLACR_DFCC(x)                        (((uint32_t)(((uint32_t)(x))<<MCM_PLACR_DFCC_SHIFT))&MCM_PLACR_DFCC_MASK)
#define MCM_PLACR_EFDS_MASK                      0x4000u
#define MCM_PLACR_EFDS_SHIFT                     14
#define MCM_PLACR_EFDS_WIDTH                     1
#define MCM_PLACR_EFDS(x)                        (((uint32_t)(((uint32_t)(x))<<MCM_PLACR_EFDS_SHIFT))&MCM_PLACR_EFDS_MASK)
#define MCM_PLACR_DFCS_MASK                      0x8000u
#define MCM_PLACR_DFCS_SHIFT                     15
#define MCM_PLACR_DFCS_WIDTH                     1
#define MCM_PLACR_DFCS(x)                        (((uint32_t)(((uint32_t)(x))<<MCM_PLACR_DFCS_SHIFT))&MCM_PLACR_DFCS_MASK)
#define MCM_PLACR_ESFC_MASK                      0x10000u
#define MCM_PLACR_ESFC_SHIFT                     16
#define MCM_PLACR_ESFC_WIDTH                     1
#define MCM_PLACR_ESFC(x)                        (((uint32_t)(((uint32_t)(x))<<MCM_PLACR_ESFC_SHIFT))&MCM_PLACR_ESFC_MASK)

/*!
 * @}
 */ /* end of group MCM_Register_Masks */


/* MCM - Peripheral instance base addresses */
/** Peripheral MCM base pointer */
#define MCM_BASE_PTR                             ((MCM_MemMapPtr)0xF0003000u)
/** Array initializer of MCM peripheral base pointers */
#define MCM_BASE_PTRS                            { MCM_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- MCM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCM_Register_Accessor_Macros MCM - Register accessor macros
 * @{
 */


/* MCM - Register instance definitions */
/* MCM */
#define MCM_PLASC                                MCM_PLASC_REG(MCM_BASE_PTR)
#define MCM_PLAMC                                MCM_PLAMC_REG(MCM_BASE_PTR)
#define MCM_PLACR                                MCM_PLACR_REG(MCM_BASE_PTR)

/*!
 * @}
 */ /* end of group MCM_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group MCM_Peripheral */


/* ----------------------------------------------------------------------------
   -- NV
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NV_Peripheral NV
 * @{
 */

/** NV - Peripheral register structure */
typedef struct NV_MemMap {
  uint8_t BACKKEY0;                                /**< Backdoor Comparison Key 0, offset: 0x0 */
  uint8_t BACKKEY1;                                /**< Backdoor Comparison Key 1, offset: 0x1 */
  uint8_t BACKKEY2;                                /**< Backdoor Comparison Key 2, offset: 0x2 */
  uint8_t BACKKEY3;                                /**< Backdoor Comparison Key 3, offset: 0x3 */
  uint8_t BACKKEY4;                                /**< Backdoor Comparison Key 4, offset: 0x4 */
  uint8_t BACKKEY5;                                /**< Backdoor Comparison Key 5, offset: 0x5 */
  uint8_t BACKKEY6;                                /**< Backdoor Comparison Key 6, offset: 0x6 */
  uint8_t BACKKEY7;                                /**< Backdoor Comparison Key 7, offset: 0x7 */
  uint8_t RESERVED_0[4];
  uint8_t EEPROT;                                  /**< Non-volatile E-Flash Protection Register, offset: 0xC */
  uint8_t FPROT;                                   /**< Non-volatile P-Flash Protection Register, offset: 0xD */
  uint8_t FSEC;                                    /**< Non-volatile Flash Security Register, offset: 0xE */
  uint8_t FOPT;                                    /**< Non-volatile Flash Option Register, offset: 0xF */
} volatile *NV_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- NV - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NV_Register_Accessor_Macros NV - Register accessor macros
 * @{
 */


/* NV - Register accessors */
#define NV_BACKKEY0_REG(base)                    ((base)->BACKKEY0)
#define NV_BACKKEY1_REG(base)                    ((base)->BACKKEY1)
#define NV_BACKKEY2_REG(base)                    ((base)->BACKKEY2)
#define NV_BACKKEY3_REG(base)                    ((base)->BACKKEY3)
#define NV_BACKKEY4_REG(base)                    ((base)->BACKKEY4)
#define NV_BACKKEY5_REG(base)                    ((base)->BACKKEY5)
#define NV_BACKKEY6_REG(base)                    ((base)->BACKKEY6)
#define NV_BACKKEY7_REG(base)                    ((base)->BACKKEY7)
#define NV_EEPROT_REG(base)                      ((base)->EEPROT)
#define NV_FPROT_REG(base)                       ((base)->FPROT)
#define NV_FSEC_REG(base)                        ((base)->FSEC)
#define NV_FOPT_REG(base)                        ((base)->FOPT)

/*!
 * @}
 */ /* end of group NV_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- NV Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NV_Register_Masks NV Register Masks
 * @{
 */

/* BACKKEY0 Bit Fields */
#define NV_BACKKEY0_KEY_MASK                     0xFFu
#define NV_BACKKEY0_KEY_SHIFT                    0
#define NV_BACKKEY0_KEY_WIDTH                    8
#define NV_BACKKEY0_KEY(x)                       (((uint8_t)(((uint8_t)(x))<<NV_BACKKEY0_KEY_SHIFT))&NV_BACKKEY0_KEY_MASK)
/* BACKKEY1 Bit Fields */
#define NV_BACKKEY1_KEY_MASK                     0xFFu
#define NV_BACKKEY1_KEY_SHIFT                    0
#define NV_BACKKEY1_KEY_WIDTH                    8
#define NV_BACKKEY1_KEY(x)                       (((uint8_t)(((uint8_t)(x))<<NV_BACKKEY1_KEY_SHIFT))&NV_BACKKEY1_KEY_MASK)
/* BACKKEY2 Bit Fields */
#define NV_BACKKEY2_KEY_MASK                     0xFFu
#define NV_BACKKEY2_KEY_SHIFT                    0
#define NV_BACKKEY2_KEY_WIDTH                    8
#define NV_BACKKEY2_KEY(x)                       (((uint8_t)(((uint8_t)(x))<<NV_BACKKEY2_KEY_SHIFT))&NV_BACKKEY2_KEY_MASK)
/* BACKKEY3 Bit Fields */
#define NV_BACKKEY3_KEY_MASK                     0xFFu
#define NV_BACKKEY3_KEY_SHIFT                    0
#define NV_BACKKEY3_KEY_WIDTH                    8
#define NV_BACKKEY3_KEY(x)                       (((uint8_t)(((uint8_t)(x))<<NV_BACKKEY3_KEY_SHIFT))&NV_BACKKEY3_KEY_MASK)
/* BACKKEY4 Bit Fields */
#define NV_BACKKEY4_KEY_MASK                     0xFFu
#define NV_BACKKEY4_KEY_SHIFT                    0
#define NV_BACKKEY4_KEY_WIDTH                    8
#define NV_BACKKEY4_KEY(x)                       (((uint8_t)(((uint8_t)(x))<<NV_BACKKEY4_KEY_SHIFT))&NV_BACKKEY4_KEY_MASK)
/* BACKKEY5 Bit Fields */
#define NV_BACKKEY5_KEY_MASK                     0xFFu
#define NV_BACKKEY5_KEY_SHIFT                    0
#define NV_BACKKEY5_KEY_WIDTH                    8
#define NV_BACKKEY5_KEY(x)                       (((uint8_t)(((uint8_t)(x))<<NV_BACKKEY5_KEY_SHIFT))&NV_BACKKEY5_KEY_MASK)
/* BACKKEY6 Bit Fields */
#define NV_BACKKEY6_KEY_MASK                     0xFFu
#define NV_BACKKEY6_KEY_SHIFT                    0
#define NV_BACKKEY6_KEY_WIDTH                    8
#define NV_BACKKEY6_KEY(x)                       (((uint8_t)(((uint8_t)(x))<<NV_BACKKEY6_KEY_SHIFT))&NV_BACKKEY6_KEY_MASK)
/* BACKKEY7 Bit Fields */
#define NV_BACKKEY7_KEY_MASK                     0xFFu
#define NV_BACKKEY7_KEY_SHIFT                    0
#define NV_BACKKEY7_KEY_WIDTH                    8
#define NV_BACKKEY7_KEY(x)                       (((uint8_t)(((uint8_t)(x))<<NV_BACKKEY7_KEY_SHIFT))&NV_BACKKEY7_KEY_MASK)
/* EEPROT Bit Fields */
#define NV_EEPROT_DPS_MASK                       0x7u
#define NV_EEPROT_DPS_SHIFT                      0
#define NV_EEPROT_DPS_WIDTH                      3
#define NV_EEPROT_DPS(x)                         (((uint8_t)(((uint8_t)(x))<<NV_EEPROT_DPS_SHIFT))&NV_EEPROT_DPS_MASK)
#define NV_EEPROT_DPOPEN_MASK                    0x80u
#define NV_EEPROT_DPOPEN_SHIFT                   7
#define NV_EEPROT_DPOPEN_WIDTH                   1
#define NV_EEPROT_DPOPEN(x)                      (((uint8_t)(((uint8_t)(x))<<NV_EEPROT_DPOPEN_SHIFT))&NV_EEPROT_DPOPEN_MASK)
/* FPROT Bit Fields */
#define NV_FPROT_FPLS_MASK                       0x3u
#define NV_FPROT_FPLS_SHIFT                      0
#define NV_FPROT_FPLS_WIDTH                      2
#define NV_FPROT_FPLS(x)                         (((uint8_t)(((uint8_t)(x))<<NV_FPROT_FPLS_SHIFT))&NV_FPROT_FPLS_MASK)
#define NV_FPROT_FPLDIS_MASK                     0x4u
#define NV_FPROT_FPLDIS_SHIFT                    2
#define NV_FPROT_FPLDIS_WIDTH                    1
#define NV_FPROT_FPLDIS(x)                       (((uint8_t)(((uint8_t)(x))<<NV_FPROT_FPLDIS_SHIFT))&NV_FPROT_FPLDIS_MASK)
#define NV_FPROT_FPHS_MASK                       0x18u
#define NV_FPROT_FPHS_SHIFT                      3
#define NV_FPROT_FPHS_WIDTH                      2
#define NV_FPROT_FPHS(x)                         (((uint8_t)(((uint8_t)(x))<<NV_FPROT_FPHS_SHIFT))&NV_FPROT_FPHS_MASK)
#define NV_FPROT_FPHDIS_MASK                     0x20u
#define NV_FPROT_FPHDIS_SHIFT                    5
#define NV_FPROT_FPHDIS_WIDTH                    1
#define NV_FPROT_FPHDIS(x)                       (((uint8_t)(((uint8_t)(x))<<NV_FPROT_FPHDIS_SHIFT))&NV_FPROT_FPHDIS_MASK)
#define NV_FPROT_FPOPEN_MASK                     0x80u
#define NV_FPROT_FPOPEN_SHIFT                    7
#define NV_FPROT_FPOPEN_WIDTH                    1
#define NV_FPROT_FPOPEN(x)                       (((uint8_t)(((uint8_t)(x))<<NV_FPROT_FPOPEN_SHIFT))&NV_FPROT_FPOPEN_MASK)
/* FSEC Bit Fields */
#define NV_FSEC_SEC_MASK                         0x3u
#define NV_FSEC_SEC_SHIFT                        0
#define NV_FSEC_SEC_WIDTH                        2
#define NV_FSEC_SEC(x)                           (((uint8_t)(((uint8_t)(x))<<NV_FSEC_SEC_SHIFT))&NV_FSEC_SEC_MASK)
#define NV_FSEC_KEYEN_MASK                       0xC0u
#define NV_FSEC_KEYEN_SHIFT                      6
#define NV_FSEC_KEYEN_WIDTH                      2
#define NV_FSEC_KEYEN(x)                         (((uint8_t)(((uint8_t)(x))<<NV_FSEC_KEYEN_SHIFT))&NV_FSEC_KEYEN_MASK)

/*!
 * @}
 */ /* end of group NV_Register_Masks */


/* NV - Peripheral instance base addresses */
/** Peripheral FTMRH_FlashConfig base pointer */
#define FTMRH_FlashConfig_BASE_PTR               ((NV_MemMapPtr)0x400u)
/** Array initializer of NV peripheral base pointers */
#define NV_BASE_PTRS                             { FTMRH_FlashConfig_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- NV - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NV_Register_Accessor_Macros NV - Register accessor macros
 * @{
 */


/* NV - Register instance definitions */
/* FTMRH_FlashConfig */
#define NV_BACKKEY0                              NV_BACKKEY0_REG(FTMRH_FlashConfig_BASE_PTR)
#define NV_BACKKEY1                              NV_BACKKEY1_REG(FTMRH_FlashConfig_BASE_PTR)
#define NV_BACKKEY2                              NV_BACKKEY2_REG(FTMRH_FlashConfig_BASE_PTR)
#define NV_BACKKEY3                              NV_BACKKEY3_REG(FTMRH_FlashConfig_BASE_PTR)
#define NV_BACKKEY4                              NV_BACKKEY4_REG(FTMRH_FlashConfig_BASE_PTR)
#define NV_BACKKEY5                              NV_BACKKEY5_REG(FTMRH_FlashConfig_BASE_PTR)
#define NV_BACKKEY6                              NV_BACKKEY6_REG(FTMRH_FlashConfig_BASE_PTR)
#define NV_BACKKEY7                              NV_BACKKEY7_REG(FTMRH_FlashConfig_BASE_PTR)
#define NV_EEPROT                                NV_EEPROT_REG(FTMRH_FlashConfig_BASE_PTR)
#define NV_FPROT                                 NV_FPROT_REG(FTMRH_FlashConfig_BASE_PTR)
#define NV_FSEC                                  NV_FSEC_REG(FTMRH_FlashConfig_BASE_PTR)
#define NV_FOPT                                  NV_FOPT_REG(FTMRH_FlashConfig_BASE_PTR)

/*!
 * @}
 */ /* end of group NV_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group NV_Peripheral */


/* ----------------------------------------------------------------------------
   -- NVIC
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NVIC_Peripheral NVIC
 * @{
 */

/** NVIC - Peripheral register structure */
typedef struct NVIC_MemMap {
  uint32_t ISER;                                   /**< Interrupt Set Enable Register, offset: 0x0 */
  uint8_t RESERVED_0[124];
  uint32_t ICER;                                   /**< Interrupt Clear Enable Register, offset: 0x80 */
  uint8_t RESERVED_1[124];
  uint32_t ISPR;                                   /**< Interrupt Set Pending Register, offset: 0x100 */
  uint8_t RESERVED_2[124];
  uint32_t ICPR;                                   /**< Interrupt Clear Pending Register, offset: 0x180 */
  uint8_t RESERVED_3[380];
  uint32_t IP[8];                                  /**< Interrupt Priority Register 0..Interrupt Priority Register 7, array offset: 0x300, array step: 0x4 */
} volatile *NVIC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- NVIC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NVIC_Register_Accessor_Macros NVIC - Register accessor macros
 * @{
 */


/* NVIC - Register accessors */
#define NVIC_ISER_REG(base)                      ((base)->ISER)
#define NVIC_ICER_REG(base)                      ((base)->ICER)
#define NVIC_ISPR_REG(base)                      ((base)->ISPR)
#define NVIC_ICPR_REG(base)                      ((base)->ICPR)
#define NVIC_IP_REG(base,index)                  ((base)->IP[index])
#define NVIC_IP_COUNT                            8

/*!
 * @}
 */ /* end of group NVIC_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- NVIC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NVIC_Register_Masks NVIC Register Masks
 * @{
 */

/* ISER Bit Fields */
#define NVIC_ISER_SETENA0_MASK                   0x1u
#define NVIC_ISER_SETENA0_SHIFT                  0
#define NVIC_ISER_SETENA0_WIDTH                  1
#define NVIC_ISER_SETENA0(x)                     (((uint32_t)(((uint32_t)(x))<<NVIC_ISER_SETENA0_SHIFT))&NVIC_ISER_SETENA0_MASK)
#define NVIC_ISER_SETENA1_MASK                   0x2u
#define NVIC_ISER_SETENA1_SHIFT                  1
#define NVIC_ISER_SETENA1_WIDTH                  1
#define NVIC_ISER_SETENA1(x)                     (((uint32_t)(((uint32_t)(x))<<NVIC_ISER_SETENA1_SHIFT))&NVIC_ISER_SETENA1_MASK)
#define NVIC_ISER_SETENA2_MASK                   0x4u
#define NVIC_ISER_SETENA2_SHIFT                  2
#define NVIC_ISER_SETENA2_WIDTH                  1
#define NVIC_ISER_SETENA2(x)                     (((uint32_t)(((uint32_t)(x))<<NVIC_ISER_SETENA2_SHIFT))&NVIC_ISER_SETENA2_MASK)
#define NVIC_ISER_SETENA3_MASK                   0x8u
#define NVIC_ISER_SETENA3_SHIFT                  3
#define NVIC_ISER_SETENA3_WIDTH                  1
#define NVIC_ISER_SETENA3(x)                     (((uint32_t)(((uint32_t)(x))<<NVIC_ISER_SETENA3_SHIFT))&NVIC_ISER_SETENA3_MASK)
#define NVIC_ISER_SETENA4_MASK                   0x10u
#define NVIC_ISER_SETENA4_SHIFT                  4
#define NVIC_ISER_SETENA4_WIDTH                  1
#define NVIC_ISER_SETENA4(x)                     (((uint32_t)(((uint32_t)(x))<<NVIC_ISER_SETENA4_SHIFT))&NVIC_ISER_SETENA4_MASK)
#define NVIC_ISER_SETENA5_MASK                   0x20u
#define NVIC_ISER_SETENA5_SHIFT                  5
#define NVIC_ISER_SETENA5_WIDTH                  1
#define NVIC_ISER_SETENA5(x)                     (((uint32_t)(((uint32_t)(x))<<NVIC_ISER_SETENA5_SHIFT))&NVIC_ISER_SETENA5_MASK)
#define NVIC_ISER_SETENA6_MASK                   0x40u
#define NVIC_ISER_SETENA6_SHIFT                  6
#define NVIC_ISER_SETENA6_WIDTH                  1
#define NVIC_ISER_SETENA6(x)                     (((uint32_t)(((uint32_t)(x))<<NVIC_ISER_SETENA6_SHIFT))&NVIC_ISER_SETENA6_MASK)
#define NVIC_ISER_SETENA7_MASK                   0x80u
#define NVIC_ISER_SETENA7_SHIFT                  7
#define NVIC_ISER_SETENA7_WIDTH                  1
#define NVIC_ISER_SETENA7(x)                     (((uint32_t)(((uint32_t)(x))<<NVIC_ISER_SETENA7_SHIFT))&NVIC_ISER_SETENA7_MASK)
#define NVIC_ISER_SETENA8_MASK                   0x100u
#define NVIC_ISER_SETENA8_SHIFT                  8
#define NVIC_ISER_SETENA8_WIDTH                  1
#define NVIC_ISER_SETENA8(x)                     (((uint32_t)(((uint32_t)(x))<<NVIC_ISER_SETENA8_SHIFT))&NVIC_ISER_SETENA8_MASK)
#define NVIC_ISER_SETENA9_MASK                   0x200u
#define NVIC_ISER_SETENA9_SHIFT                  9
#define NVIC_ISER_SETENA9_WIDTH                  1
#define NVIC_ISER_SETENA9(x)                     (((uint32_t)(((uint32_t)(x))<<NVIC_ISER_SETENA9_SHIFT))&NVIC_ISER_SETENA9_MASK)
#define NVIC_ISER_SETENA10_MASK                  0x400u
#define NVIC_ISER_SETENA10_SHIFT                 10
#define NVIC_ISER_SETENA10_WIDTH                 1
#define NVIC_ISER_SETENA10(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ISER_SETENA10_SHIFT))&NVIC_ISER_SETENA10_MASK)
#define NVIC_ISER_SETENA11_MASK                  0x800u
#define NVIC_ISER_SETENA11_SHIFT                 11
#define NVIC_ISER_SETENA11_WIDTH                 1
#define NVIC_ISER_SETENA11(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ISER_SETENA11_SHIFT))&NVIC_ISER_SETENA11_MASK)
#define NVIC_ISER_SETENA12_MASK                  0x1000u
#define NVIC_ISER_SETENA12_SHIFT                 12
#define NVIC_ISER_SETENA12_WIDTH                 1
#define NVIC_ISER_SETENA12(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ISER_SETENA12_SHIFT))&NVIC_ISER_SETENA12_MASK)
#define NVIC_ISER_SETENA13_MASK                  0x2000u
#define NVIC_ISER_SETENA13_SHIFT                 13
#define NVIC_ISER_SETENA13_WIDTH                 1
#define NVIC_ISER_SETENA13(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ISER_SETENA13_SHIFT))&NVIC_ISER_SETENA13_MASK)
#define NVIC_ISER_SETENA14_MASK                  0x4000u
#define NVIC_ISER_SETENA14_SHIFT                 14
#define NVIC_ISER_SETENA14_WIDTH                 1
#define NVIC_ISER_SETENA14(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ISER_SETENA14_SHIFT))&NVIC_ISER_SETENA14_MASK)
#define NVIC_ISER_SETENA15_MASK                  0x8000u
#define NVIC_ISER_SETENA15_SHIFT                 15
#define NVIC_ISER_SETENA15_WIDTH                 1
#define NVIC_ISER_SETENA15(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ISER_SETENA15_SHIFT))&NVIC_ISER_SETENA15_MASK)
#define NVIC_ISER_SETENA16_MASK                  0x10000u
#define NVIC_ISER_SETENA16_SHIFT                 16
#define NVIC_ISER_SETENA16_WIDTH                 1
#define NVIC_ISER_SETENA16(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ISER_SETENA16_SHIFT))&NVIC_ISER_SETENA16_MASK)
#define NVIC_ISER_SETENA17_MASK                  0x20000u
#define NVIC_ISER_SETENA17_SHIFT                 17
#define NVIC_ISER_SETENA17_WIDTH                 1
#define NVIC_ISER_SETENA17(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ISER_SETENA17_SHIFT))&NVIC_ISER_SETENA17_MASK)
#define NVIC_ISER_SETENA18_MASK                  0x40000u
#define NVIC_ISER_SETENA18_SHIFT                 18
#define NVIC_ISER_SETENA18_WIDTH                 1
#define NVIC_ISER_SETENA18(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ISER_SETENA18_SHIFT))&NVIC_ISER_SETENA18_MASK)
#define NVIC_ISER_SETENA19_MASK                  0x80000u
#define NVIC_ISER_SETENA19_SHIFT                 19
#define NVIC_ISER_SETENA19_WIDTH                 1
#define NVIC_ISER_SETENA19(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ISER_SETENA19_SHIFT))&NVIC_ISER_SETENA19_MASK)
#define NVIC_ISER_SETENA20_MASK                  0x100000u
#define NVIC_ISER_SETENA20_SHIFT                 20
#define NVIC_ISER_SETENA20_WIDTH                 1
#define NVIC_ISER_SETENA20(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ISER_SETENA20_SHIFT))&NVIC_ISER_SETENA20_MASK)
#define NVIC_ISER_SETENA21_MASK                  0x200000u
#define NVIC_ISER_SETENA21_SHIFT                 21
#define NVIC_ISER_SETENA21_WIDTH                 1
#define NVIC_ISER_SETENA21(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ISER_SETENA21_SHIFT))&NVIC_ISER_SETENA21_MASK)
#define NVIC_ISER_SETENA22_MASK                  0x400000u
#define NVIC_ISER_SETENA22_SHIFT                 22
#define NVIC_ISER_SETENA22_WIDTH                 1
#define NVIC_ISER_SETENA22(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ISER_SETENA22_SHIFT))&NVIC_ISER_SETENA22_MASK)
#define NVIC_ISER_SETENA23_MASK                  0x800000u
#define NVIC_ISER_SETENA23_SHIFT                 23
#define NVIC_ISER_SETENA23_WIDTH                 1
#define NVIC_ISER_SETENA23(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ISER_SETENA23_SHIFT))&NVIC_ISER_SETENA23_MASK)
#define NVIC_ISER_SETENA24_MASK                  0x1000000u
#define NVIC_ISER_SETENA24_SHIFT                 24
#define NVIC_ISER_SETENA24_WIDTH                 1
#define NVIC_ISER_SETENA24(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ISER_SETENA24_SHIFT))&NVIC_ISER_SETENA24_MASK)
#define NVIC_ISER_SETENA25_MASK                  0x2000000u
#define NVIC_ISER_SETENA25_SHIFT                 25
#define NVIC_ISER_SETENA25_WIDTH                 1
#define NVIC_ISER_SETENA25(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ISER_SETENA25_SHIFT))&NVIC_ISER_SETENA25_MASK)
#define NVIC_ISER_SETENA26_MASK                  0x4000000u
#define NVIC_ISER_SETENA26_SHIFT                 26
#define NVIC_ISER_SETENA26_WIDTH                 1
#define NVIC_ISER_SETENA26(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ISER_SETENA26_SHIFT))&NVIC_ISER_SETENA26_MASK)
#define NVIC_ISER_SETENA27_MASK                  0x8000000u
#define NVIC_ISER_SETENA27_SHIFT                 27
#define NVIC_ISER_SETENA27_WIDTH                 1
#define NVIC_ISER_SETENA27(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ISER_SETENA27_SHIFT))&NVIC_ISER_SETENA27_MASK)
#define NVIC_ISER_SETENA28_MASK                  0x10000000u
#define NVIC_ISER_SETENA28_SHIFT                 28
#define NVIC_ISER_SETENA28_WIDTH                 1
#define NVIC_ISER_SETENA28(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ISER_SETENA28_SHIFT))&NVIC_ISER_SETENA28_MASK)
#define NVIC_ISER_SETENA29_MASK                  0x20000000u
#define NVIC_ISER_SETENA29_SHIFT                 29
#define NVIC_ISER_SETENA29_WIDTH                 1
#define NVIC_ISER_SETENA29(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ISER_SETENA29_SHIFT))&NVIC_ISER_SETENA29_MASK)
#define NVIC_ISER_SETENA30_MASK                  0x40000000u
#define NVIC_ISER_SETENA30_SHIFT                 30
#define NVIC_ISER_SETENA30_WIDTH                 1
#define NVIC_ISER_SETENA30(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ISER_SETENA30_SHIFT))&NVIC_ISER_SETENA30_MASK)
#define NVIC_ISER_SETENA31_MASK                  0x80000000u
#define NVIC_ISER_SETENA31_SHIFT                 31
#define NVIC_ISER_SETENA31_WIDTH                 1
#define NVIC_ISER_SETENA31(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ISER_SETENA31_SHIFT))&NVIC_ISER_SETENA31_MASK)
/* ICER Bit Fields */
#define NVIC_ICER_CLRENA0_MASK                   0x1u
#define NVIC_ICER_CLRENA0_SHIFT                  0
#define NVIC_ICER_CLRENA0_WIDTH                  1
#define NVIC_ICER_CLRENA0(x)                     (((uint32_t)(((uint32_t)(x))<<NVIC_ICER_CLRENA0_SHIFT))&NVIC_ICER_CLRENA0_MASK)
#define NVIC_ICER_CLRENA1_MASK                   0x2u
#define NVIC_ICER_CLRENA1_SHIFT                  1
#define NVIC_ICER_CLRENA1_WIDTH                  1
#define NVIC_ICER_CLRENA1(x)                     (((uint32_t)(((uint32_t)(x))<<NVIC_ICER_CLRENA1_SHIFT))&NVIC_ICER_CLRENA1_MASK)
#define NVIC_ICER_CLRENA2_MASK                   0x4u
#define NVIC_ICER_CLRENA2_SHIFT                  2
#define NVIC_ICER_CLRENA2_WIDTH                  1
#define NVIC_ICER_CLRENA2(x)                     (((uint32_t)(((uint32_t)(x))<<NVIC_ICER_CLRENA2_SHIFT))&NVIC_ICER_CLRENA2_MASK)
#define NVIC_ICER_CLRENA3_MASK                   0x8u
#define NVIC_ICER_CLRENA3_SHIFT                  3
#define NVIC_ICER_CLRENA3_WIDTH                  1
#define NVIC_ICER_CLRENA3(x)                     (((uint32_t)(((uint32_t)(x))<<NVIC_ICER_CLRENA3_SHIFT))&NVIC_ICER_CLRENA3_MASK)
#define NVIC_ICER_CLRENA4_MASK                   0x10u
#define NVIC_ICER_CLRENA4_SHIFT                  4
#define NVIC_ICER_CLRENA4_WIDTH                  1
#define NVIC_ICER_CLRENA4(x)                     (((uint32_t)(((uint32_t)(x))<<NVIC_ICER_CLRENA4_SHIFT))&NVIC_ICER_CLRENA4_MASK)
#define NVIC_ICER_CLRENA5_MASK                   0x20u
#define NVIC_ICER_CLRENA5_SHIFT                  5
#define NVIC_ICER_CLRENA5_WIDTH                  1
#define NVIC_ICER_CLRENA5(x)                     (((uint32_t)(((uint32_t)(x))<<NVIC_ICER_CLRENA5_SHIFT))&NVIC_ICER_CLRENA5_MASK)
#define NVIC_ICER_CLRENA6_MASK                   0x40u
#define NVIC_ICER_CLRENA6_SHIFT                  6
#define NVIC_ICER_CLRENA6_WIDTH                  1
#define NVIC_ICER_CLRENA6(x)                     (((uint32_t)(((uint32_t)(x))<<NVIC_ICER_CLRENA6_SHIFT))&NVIC_ICER_CLRENA6_MASK)
#define NVIC_ICER_CLRENA7_MASK                   0x80u
#define NVIC_ICER_CLRENA7_SHIFT                  7
#define NVIC_ICER_CLRENA7_WIDTH                  1
#define NVIC_ICER_CLRENA7(x)                     (((uint32_t)(((uint32_t)(x))<<NVIC_ICER_CLRENA7_SHIFT))&NVIC_ICER_CLRENA7_MASK)
#define NVIC_ICER_CLRENA8_MASK                   0x100u
#define NVIC_ICER_CLRENA8_SHIFT                  8
#define NVIC_ICER_CLRENA8_WIDTH                  1
#define NVIC_ICER_CLRENA8(x)                     (((uint32_t)(((uint32_t)(x))<<NVIC_ICER_CLRENA8_SHIFT))&NVIC_ICER_CLRENA8_MASK)
#define NVIC_ICER_CLRENA9_MASK                   0x200u
#define NVIC_ICER_CLRENA9_SHIFT                  9
#define NVIC_ICER_CLRENA9_WIDTH                  1
#define NVIC_ICER_CLRENA9(x)                     (((uint32_t)(((uint32_t)(x))<<NVIC_ICER_CLRENA9_SHIFT))&NVIC_ICER_CLRENA9_MASK)
#define NVIC_ICER_CLRENA10_MASK                  0x400u
#define NVIC_ICER_CLRENA10_SHIFT                 10
#define NVIC_ICER_CLRENA10_WIDTH                 1
#define NVIC_ICER_CLRENA10(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ICER_CLRENA10_SHIFT))&NVIC_ICER_CLRENA10_MASK)
#define NVIC_ICER_CLRENA11_MASK                  0x800u
#define NVIC_ICER_CLRENA11_SHIFT                 11
#define NVIC_ICER_CLRENA11_WIDTH                 1
#define NVIC_ICER_CLRENA11(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ICER_CLRENA11_SHIFT))&NVIC_ICER_CLRENA11_MASK)
#define NVIC_ICER_CLRENA12_MASK                  0x1000u
#define NVIC_ICER_CLRENA12_SHIFT                 12
#define NVIC_ICER_CLRENA12_WIDTH                 1
#define NVIC_ICER_CLRENA12(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ICER_CLRENA12_SHIFT))&NVIC_ICER_CLRENA12_MASK)
#define NVIC_ICER_CLRENA13_MASK                  0x2000u
#define NVIC_ICER_CLRENA13_SHIFT                 13
#define NVIC_ICER_CLRENA13_WIDTH                 1
#define NVIC_ICER_CLRENA13(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ICER_CLRENA13_SHIFT))&NVIC_ICER_CLRENA13_MASK)
#define NVIC_ICER_CLRENA14_MASK                  0x4000u
#define NVIC_ICER_CLRENA14_SHIFT                 14
#define NVIC_ICER_CLRENA14_WIDTH                 1
#define NVIC_ICER_CLRENA14(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ICER_CLRENA14_SHIFT))&NVIC_ICER_CLRENA14_MASK)
#define NVIC_ICER_CLRENA15_MASK                  0x8000u
#define NVIC_ICER_CLRENA15_SHIFT                 15
#define NVIC_ICER_CLRENA15_WIDTH                 1
#define NVIC_ICER_CLRENA15(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ICER_CLRENA15_SHIFT))&NVIC_ICER_CLRENA15_MASK)
#define NVIC_ICER_CLRENA16_MASK                  0x10000u
#define NVIC_ICER_CLRENA16_SHIFT                 16
#define NVIC_ICER_CLRENA16_WIDTH                 1
#define NVIC_ICER_CLRENA16(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ICER_CLRENA16_SHIFT))&NVIC_ICER_CLRENA16_MASK)
#define NVIC_ICER_CLRENA17_MASK                  0x20000u
#define NVIC_ICER_CLRENA17_SHIFT                 17
#define NVIC_ICER_CLRENA17_WIDTH                 1
#define NVIC_ICER_CLRENA17(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ICER_CLRENA17_SHIFT))&NVIC_ICER_CLRENA17_MASK)
#define NVIC_ICER_CLRENA18_MASK                  0x40000u
#define NVIC_ICER_CLRENA18_SHIFT                 18
#define NVIC_ICER_CLRENA18_WIDTH                 1
#define NVIC_ICER_CLRENA18(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ICER_CLRENA18_SHIFT))&NVIC_ICER_CLRENA18_MASK)
#define NVIC_ICER_CLRENA19_MASK                  0x80000u
#define NVIC_ICER_CLRENA19_SHIFT                 19
#define NVIC_ICER_CLRENA19_WIDTH                 1
#define NVIC_ICER_CLRENA19(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ICER_CLRENA19_SHIFT))&NVIC_ICER_CLRENA19_MASK)
#define NVIC_ICER_CLRENA20_MASK                  0x100000u
#define NVIC_ICER_CLRENA20_SHIFT                 20
#define NVIC_ICER_CLRENA20_WIDTH                 1
#define NVIC_ICER_CLRENA20(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ICER_CLRENA20_SHIFT))&NVIC_ICER_CLRENA20_MASK)
#define NVIC_ICER_CLRENA21_MASK                  0x200000u
#define NVIC_ICER_CLRENA21_SHIFT                 21
#define NVIC_ICER_CLRENA21_WIDTH                 1
#define NVIC_ICER_CLRENA21(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ICER_CLRENA21_SHIFT))&NVIC_ICER_CLRENA21_MASK)
#define NVIC_ICER_CLRENA22_MASK                  0x400000u
#define NVIC_ICER_CLRENA22_SHIFT                 22
#define NVIC_ICER_CLRENA22_WIDTH                 1
#define NVIC_ICER_CLRENA22(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ICER_CLRENA22_SHIFT))&NVIC_ICER_CLRENA22_MASK)
#define NVIC_ICER_CLRENA23_MASK                  0x800000u
#define NVIC_ICER_CLRENA23_SHIFT                 23
#define NVIC_ICER_CLRENA23_WIDTH                 1
#define NVIC_ICER_CLRENA23(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ICER_CLRENA23_SHIFT))&NVIC_ICER_CLRENA23_MASK)
#define NVIC_ICER_CLRENA24_MASK                  0x1000000u
#define NVIC_ICER_CLRENA24_SHIFT                 24
#define NVIC_ICER_CLRENA24_WIDTH                 1
#define NVIC_ICER_CLRENA24(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ICER_CLRENA24_SHIFT))&NVIC_ICER_CLRENA24_MASK)
#define NVIC_ICER_CLRENA25_MASK                  0x2000000u
#define NVIC_ICER_CLRENA25_SHIFT                 25
#define NVIC_ICER_CLRENA25_WIDTH                 1
#define NVIC_ICER_CLRENA25(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ICER_CLRENA25_SHIFT))&NVIC_ICER_CLRENA25_MASK)
#define NVIC_ICER_CLRENA26_MASK                  0x4000000u
#define NVIC_ICER_CLRENA26_SHIFT                 26
#define NVIC_ICER_CLRENA26_WIDTH                 1
#define NVIC_ICER_CLRENA26(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ICER_CLRENA26_SHIFT))&NVIC_ICER_CLRENA26_MASK)
#define NVIC_ICER_CLRENA27_MASK                  0x8000000u
#define NVIC_ICER_CLRENA27_SHIFT                 27
#define NVIC_ICER_CLRENA27_WIDTH                 1
#define NVIC_ICER_CLRENA27(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ICER_CLRENA27_SHIFT))&NVIC_ICER_CLRENA27_MASK)
#define NVIC_ICER_CLRENA28_MASK                  0x10000000u
#define NVIC_ICER_CLRENA28_SHIFT                 28
#define NVIC_ICER_CLRENA28_WIDTH                 1
#define NVIC_ICER_CLRENA28(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ICER_CLRENA28_SHIFT))&NVIC_ICER_CLRENA28_MASK)
#define NVIC_ICER_CLRENA29_MASK                  0x20000000u
#define NVIC_ICER_CLRENA29_SHIFT                 29
#define NVIC_ICER_CLRENA29_WIDTH                 1
#define NVIC_ICER_CLRENA29(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ICER_CLRENA29_SHIFT))&NVIC_ICER_CLRENA29_MASK)
#define NVIC_ICER_CLRENA30_MASK                  0x40000000u
#define NVIC_ICER_CLRENA30_SHIFT                 30
#define NVIC_ICER_CLRENA30_WIDTH                 1
#define NVIC_ICER_CLRENA30(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ICER_CLRENA30_SHIFT))&NVIC_ICER_CLRENA30_MASK)
#define NVIC_ICER_CLRENA31_MASK                  0x80000000u
#define NVIC_ICER_CLRENA31_SHIFT                 31
#define NVIC_ICER_CLRENA31_WIDTH                 1
#define NVIC_ICER_CLRENA31(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ICER_CLRENA31_SHIFT))&NVIC_ICER_CLRENA31_MASK)
/* ISPR Bit Fields */
#define NVIC_ISPR_SETPEND0_MASK                  0x1u
#define NVIC_ISPR_SETPEND0_SHIFT                 0
#define NVIC_ISPR_SETPEND0_WIDTH                 1
#define NVIC_ISPR_SETPEND0(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ISPR_SETPEND0_SHIFT))&NVIC_ISPR_SETPEND0_MASK)
#define NVIC_ISPR_SETPEND1_MASK                  0x2u
#define NVIC_ISPR_SETPEND1_SHIFT                 1
#define NVIC_ISPR_SETPEND1_WIDTH                 1
#define NVIC_ISPR_SETPEND1(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ISPR_SETPEND1_SHIFT))&NVIC_ISPR_SETPEND1_MASK)
#define NVIC_ISPR_SETPEND2_MASK                  0x4u
#define NVIC_ISPR_SETPEND2_SHIFT                 2
#define NVIC_ISPR_SETPEND2_WIDTH                 1
#define NVIC_ISPR_SETPEND2(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ISPR_SETPEND2_SHIFT))&NVIC_ISPR_SETPEND2_MASK)
#define NVIC_ISPR_SETPEND3_MASK                  0x8u
#define NVIC_ISPR_SETPEND3_SHIFT                 3
#define NVIC_ISPR_SETPEND3_WIDTH                 1
#define NVIC_ISPR_SETPEND3(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ISPR_SETPEND3_SHIFT))&NVIC_ISPR_SETPEND3_MASK)
#define NVIC_ISPR_SETPEND4_MASK                  0x10u
#define NVIC_ISPR_SETPEND4_SHIFT                 4
#define NVIC_ISPR_SETPEND4_WIDTH                 1
#define NVIC_ISPR_SETPEND4(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ISPR_SETPEND4_SHIFT))&NVIC_ISPR_SETPEND4_MASK)
#define NVIC_ISPR_SETPEND5_MASK                  0x20u
#define NVIC_ISPR_SETPEND5_SHIFT                 5
#define NVIC_ISPR_SETPEND5_WIDTH                 1
#define NVIC_ISPR_SETPEND5(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ISPR_SETPEND5_SHIFT))&NVIC_ISPR_SETPEND5_MASK)
#define NVIC_ISPR_SETPEND6_MASK                  0x40u
#define NVIC_ISPR_SETPEND6_SHIFT                 6
#define NVIC_ISPR_SETPEND6_WIDTH                 1
#define NVIC_ISPR_SETPEND6(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ISPR_SETPEND6_SHIFT))&NVIC_ISPR_SETPEND6_MASK)
#define NVIC_ISPR_SETPEND7_MASK                  0x80u
#define NVIC_ISPR_SETPEND7_SHIFT                 7
#define NVIC_ISPR_SETPEND7_WIDTH                 1
#define NVIC_ISPR_SETPEND7(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ISPR_SETPEND7_SHIFT))&NVIC_ISPR_SETPEND7_MASK)
#define NVIC_ISPR_SETPEND8_MASK                  0x100u
#define NVIC_ISPR_SETPEND8_SHIFT                 8
#define NVIC_ISPR_SETPEND8_WIDTH                 1
#define NVIC_ISPR_SETPEND8(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ISPR_SETPEND8_SHIFT))&NVIC_ISPR_SETPEND8_MASK)
#define NVIC_ISPR_SETPEND9_MASK                  0x200u
#define NVIC_ISPR_SETPEND9_SHIFT                 9
#define NVIC_ISPR_SETPEND9_WIDTH                 1
#define NVIC_ISPR_SETPEND9(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ISPR_SETPEND9_SHIFT))&NVIC_ISPR_SETPEND9_MASK)
#define NVIC_ISPR_SETPEND10_MASK                 0x400u
#define NVIC_ISPR_SETPEND10_SHIFT                10
#define NVIC_ISPR_SETPEND10_WIDTH                1
#define NVIC_ISPR_SETPEND10(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ISPR_SETPEND10_SHIFT))&NVIC_ISPR_SETPEND10_MASK)
#define NVIC_ISPR_SETPEND11_MASK                 0x800u
#define NVIC_ISPR_SETPEND11_SHIFT                11
#define NVIC_ISPR_SETPEND11_WIDTH                1
#define NVIC_ISPR_SETPEND11(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ISPR_SETPEND11_SHIFT))&NVIC_ISPR_SETPEND11_MASK)
#define NVIC_ISPR_SETPEND12_MASK                 0x1000u
#define NVIC_ISPR_SETPEND12_SHIFT                12
#define NVIC_ISPR_SETPEND12_WIDTH                1
#define NVIC_ISPR_SETPEND12(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ISPR_SETPEND12_SHIFT))&NVIC_ISPR_SETPEND12_MASK)
#define NVIC_ISPR_SETPEND13_MASK                 0x2000u
#define NVIC_ISPR_SETPEND13_SHIFT                13
#define NVIC_ISPR_SETPEND13_WIDTH                1
#define NVIC_ISPR_SETPEND13(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ISPR_SETPEND13_SHIFT))&NVIC_ISPR_SETPEND13_MASK)
#define NVIC_ISPR_SETPEND14_MASK                 0x4000u
#define NVIC_ISPR_SETPEND14_SHIFT                14
#define NVIC_ISPR_SETPEND14_WIDTH                1
#define NVIC_ISPR_SETPEND14(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ISPR_SETPEND14_SHIFT))&NVIC_ISPR_SETPEND14_MASK)
#define NVIC_ISPR_SETPEND15_MASK                 0x8000u
#define NVIC_ISPR_SETPEND15_SHIFT                15
#define NVIC_ISPR_SETPEND15_WIDTH                1
#define NVIC_ISPR_SETPEND15(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ISPR_SETPEND15_SHIFT))&NVIC_ISPR_SETPEND15_MASK)
#define NVIC_ISPR_SETPEND16_MASK                 0x10000u
#define NVIC_ISPR_SETPEND16_SHIFT                16
#define NVIC_ISPR_SETPEND16_WIDTH                1
#define NVIC_ISPR_SETPEND16(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ISPR_SETPEND16_SHIFT))&NVIC_ISPR_SETPEND16_MASK)
#define NVIC_ISPR_SETPEND17_MASK                 0x20000u
#define NVIC_ISPR_SETPEND17_SHIFT                17
#define NVIC_ISPR_SETPEND17_WIDTH                1
#define NVIC_ISPR_SETPEND17(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ISPR_SETPEND17_SHIFT))&NVIC_ISPR_SETPEND17_MASK)
#define NVIC_ISPR_SETPEND18_MASK                 0x40000u
#define NVIC_ISPR_SETPEND18_SHIFT                18
#define NVIC_ISPR_SETPEND18_WIDTH                1
#define NVIC_ISPR_SETPEND18(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ISPR_SETPEND18_SHIFT))&NVIC_ISPR_SETPEND18_MASK)
#define NVIC_ISPR_SETPEND19_MASK                 0x80000u
#define NVIC_ISPR_SETPEND19_SHIFT                19
#define NVIC_ISPR_SETPEND19_WIDTH                1
#define NVIC_ISPR_SETPEND19(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ISPR_SETPEND19_SHIFT))&NVIC_ISPR_SETPEND19_MASK)
#define NVIC_ISPR_SETPEND20_MASK                 0x100000u
#define NVIC_ISPR_SETPEND20_SHIFT                20
#define NVIC_ISPR_SETPEND20_WIDTH                1
#define NVIC_ISPR_SETPEND20(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ISPR_SETPEND20_SHIFT))&NVIC_ISPR_SETPEND20_MASK)
#define NVIC_ISPR_SETPEND21_MASK                 0x200000u
#define NVIC_ISPR_SETPEND21_SHIFT                21
#define NVIC_ISPR_SETPEND21_WIDTH                1
#define NVIC_ISPR_SETPEND21(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ISPR_SETPEND21_SHIFT))&NVIC_ISPR_SETPEND21_MASK)
#define NVIC_ISPR_SETPEND22_MASK                 0x400000u
#define NVIC_ISPR_SETPEND22_SHIFT                22
#define NVIC_ISPR_SETPEND22_WIDTH                1
#define NVIC_ISPR_SETPEND22(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ISPR_SETPEND22_SHIFT))&NVIC_ISPR_SETPEND22_MASK)
#define NVIC_ISPR_SETPEND23_MASK                 0x800000u
#define NVIC_ISPR_SETPEND23_SHIFT                23
#define NVIC_ISPR_SETPEND23_WIDTH                1
#define NVIC_ISPR_SETPEND23(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ISPR_SETPEND23_SHIFT))&NVIC_ISPR_SETPEND23_MASK)
#define NVIC_ISPR_SETPEND24_MASK                 0x1000000u
#define NVIC_ISPR_SETPEND24_SHIFT                24
#define NVIC_ISPR_SETPEND24_WIDTH                1
#define NVIC_ISPR_SETPEND24(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ISPR_SETPEND24_SHIFT))&NVIC_ISPR_SETPEND24_MASK)
#define NVIC_ISPR_SETPEND25_MASK                 0x2000000u
#define NVIC_ISPR_SETPEND25_SHIFT                25
#define NVIC_ISPR_SETPEND25_WIDTH                1
#define NVIC_ISPR_SETPEND25(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ISPR_SETPEND25_SHIFT))&NVIC_ISPR_SETPEND25_MASK)
#define NVIC_ISPR_SETPEND26_MASK                 0x4000000u
#define NVIC_ISPR_SETPEND26_SHIFT                26
#define NVIC_ISPR_SETPEND26_WIDTH                1
#define NVIC_ISPR_SETPEND26(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ISPR_SETPEND26_SHIFT))&NVIC_ISPR_SETPEND26_MASK)
#define NVIC_ISPR_SETPEND27_MASK                 0x8000000u
#define NVIC_ISPR_SETPEND27_SHIFT                27
#define NVIC_ISPR_SETPEND27_WIDTH                1
#define NVIC_ISPR_SETPEND27(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ISPR_SETPEND27_SHIFT))&NVIC_ISPR_SETPEND27_MASK)
#define NVIC_ISPR_SETPEND28_MASK                 0x10000000u
#define NVIC_ISPR_SETPEND28_SHIFT                28
#define NVIC_ISPR_SETPEND28_WIDTH                1
#define NVIC_ISPR_SETPEND28(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ISPR_SETPEND28_SHIFT))&NVIC_ISPR_SETPEND28_MASK)
#define NVIC_ISPR_SETPEND29_MASK                 0x20000000u
#define NVIC_ISPR_SETPEND29_SHIFT                29
#define NVIC_ISPR_SETPEND29_WIDTH                1
#define NVIC_ISPR_SETPEND29(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ISPR_SETPEND29_SHIFT))&NVIC_ISPR_SETPEND29_MASK)
#define NVIC_ISPR_SETPEND30_MASK                 0x40000000u
#define NVIC_ISPR_SETPEND30_SHIFT                30
#define NVIC_ISPR_SETPEND30_WIDTH                1
#define NVIC_ISPR_SETPEND30(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ISPR_SETPEND30_SHIFT))&NVIC_ISPR_SETPEND30_MASK)
#define NVIC_ISPR_SETPEND31_MASK                 0x80000000u
#define NVIC_ISPR_SETPEND31_SHIFT                31
#define NVIC_ISPR_SETPEND31_WIDTH                1
#define NVIC_ISPR_SETPEND31(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ISPR_SETPEND31_SHIFT))&NVIC_ISPR_SETPEND31_MASK)
/* ICPR Bit Fields */
#define NVIC_ICPR_CLRPEND0_MASK                  0x1u
#define NVIC_ICPR_CLRPEND0_SHIFT                 0
#define NVIC_ICPR_CLRPEND0_WIDTH                 1
#define NVIC_ICPR_CLRPEND0(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ICPR_CLRPEND0_SHIFT))&NVIC_ICPR_CLRPEND0_MASK)
#define NVIC_ICPR_CLRPEND1_MASK                  0x2u
#define NVIC_ICPR_CLRPEND1_SHIFT                 1
#define NVIC_ICPR_CLRPEND1_WIDTH                 1
#define NVIC_ICPR_CLRPEND1(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ICPR_CLRPEND1_SHIFT))&NVIC_ICPR_CLRPEND1_MASK)
#define NVIC_ICPR_CLRPEND2_MASK                  0x4u
#define NVIC_ICPR_CLRPEND2_SHIFT                 2
#define NVIC_ICPR_CLRPEND2_WIDTH                 1
#define NVIC_ICPR_CLRPEND2(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ICPR_CLRPEND2_SHIFT))&NVIC_ICPR_CLRPEND2_MASK)
#define NVIC_ICPR_CLRPEND3_MASK                  0x8u
#define NVIC_ICPR_CLRPEND3_SHIFT                 3
#define NVIC_ICPR_CLRPEND3_WIDTH                 1
#define NVIC_ICPR_CLRPEND3(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ICPR_CLRPEND3_SHIFT))&NVIC_ICPR_CLRPEND3_MASK)
#define NVIC_ICPR_CLRPEND4_MASK                  0x10u
#define NVIC_ICPR_CLRPEND4_SHIFT                 4
#define NVIC_ICPR_CLRPEND4_WIDTH                 1
#define NVIC_ICPR_CLRPEND4(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ICPR_CLRPEND4_SHIFT))&NVIC_ICPR_CLRPEND4_MASK)
#define NVIC_ICPR_CLRPEND5_MASK                  0x20u
#define NVIC_ICPR_CLRPEND5_SHIFT                 5
#define NVIC_ICPR_CLRPEND5_WIDTH                 1
#define NVIC_ICPR_CLRPEND5(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ICPR_CLRPEND5_SHIFT))&NVIC_ICPR_CLRPEND5_MASK)
#define NVIC_ICPR_CLRPEND6_MASK                  0x40u
#define NVIC_ICPR_CLRPEND6_SHIFT                 6
#define NVIC_ICPR_CLRPEND6_WIDTH                 1
#define NVIC_ICPR_CLRPEND6(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ICPR_CLRPEND6_SHIFT))&NVIC_ICPR_CLRPEND6_MASK)
#define NVIC_ICPR_CLRPEND7_MASK                  0x80u
#define NVIC_ICPR_CLRPEND7_SHIFT                 7
#define NVIC_ICPR_CLRPEND7_WIDTH                 1
#define NVIC_ICPR_CLRPEND7(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ICPR_CLRPEND7_SHIFT))&NVIC_ICPR_CLRPEND7_MASK)
#define NVIC_ICPR_CLRPEND8_MASK                  0x100u
#define NVIC_ICPR_CLRPEND8_SHIFT                 8
#define NVIC_ICPR_CLRPEND8_WIDTH                 1
#define NVIC_ICPR_CLRPEND8(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ICPR_CLRPEND8_SHIFT))&NVIC_ICPR_CLRPEND8_MASK)
#define NVIC_ICPR_CLRPEND9_MASK                  0x200u
#define NVIC_ICPR_CLRPEND9_SHIFT                 9
#define NVIC_ICPR_CLRPEND9_WIDTH                 1
#define NVIC_ICPR_CLRPEND9(x)                    (((uint32_t)(((uint32_t)(x))<<NVIC_ICPR_CLRPEND9_SHIFT))&NVIC_ICPR_CLRPEND9_MASK)
#define NVIC_ICPR_CLRPEND10_MASK                 0x400u
#define NVIC_ICPR_CLRPEND10_SHIFT                10
#define NVIC_ICPR_CLRPEND10_WIDTH                1
#define NVIC_ICPR_CLRPEND10(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ICPR_CLRPEND10_SHIFT))&NVIC_ICPR_CLRPEND10_MASK)
#define NVIC_ICPR_CLRPEND11_MASK                 0x800u
#define NVIC_ICPR_CLRPEND11_SHIFT                11
#define NVIC_ICPR_CLRPEND11_WIDTH                1
#define NVIC_ICPR_CLRPEND11(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ICPR_CLRPEND11_SHIFT))&NVIC_ICPR_CLRPEND11_MASK)
#define NVIC_ICPR_CLRPEND12_MASK                 0x1000u
#define NVIC_ICPR_CLRPEND12_SHIFT                12
#define NVIC_ICPR_CLRPEND12_WIDTH                1
#define NVIC_ICPR_CLRPEND12(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ICPR_CLRPEND12_SHIFT))&NVIC_ICPR_CLRPEND12_MASK)
#define NVIC_ICPR_CLRPEND13_MASK                 0x2000u
#define NVIC_ICPR_CLRPEND13_SHIFT                13
#define NVIC_ICPR_CLRPEND13_WIDTH                1
#define NVIC_ICPR_CLRPEND13(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ICPR_CLRPEND13_SHIFT))&NVIC_ICPR_CLRPEND13_MASK)
#define NVIC_ICPR_CLRPEND14_MASK                 0x4000u
#define NVIC_ICPR_CLRPEND14_SHIFT                14
#define NVIC_ICPR_CLRPEND14_WIDTH                1
#define NVIC_ICPR_CLRPEND14(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ICPR_CLRPEND14_SHIFT))&NVIC_ICPR_CLRPEND14_MASK)
#define NVIC_ICPR_CLRPEND15_MASK                 0x8000u
#define NVIC_ICPR_CLRPEND15_SHIFT                15
#define NVIC_ICPR_CLRPEND15_WIDTH                1
#define NVIC_ICPR_CLRPEND15(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ICPR_CLRPEND15_SHIFT))&NVIC_ICPR_CLRPEND15_MASK)
#define NVIC_ICPR_CLRPEND16_MASK                 0x10000u
#define NVIC_ICPR_CLRPEND16_SHIFT                16
#define NVIC_ICPR_CLRPEND16_WIDTH                1
#define NVIC_ICPR_CLRPEND16(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ICPR_CLRPEND16_SHIFT))&NVIC_ICPR_CLRPEND16_MASK)
#define NVIC_ICPR_CLRPEND17_MASK                 0x20000u
#define NVIC_ICPR_CLRPEND17_SHIFT                17
#define NVIC_ICPR_CLRPEND17_WIDTH                1
#define NVIC_ICPR_CLRPEND17(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ICPR_CLRPEND17_SHIFT))&NVIC_ICPR_CLRPEND17_MASK)
#define NVIC_ICPR_CLRPEND18_MASK                 0x40000u
#define NVIC_ICPR_CLRPEND18_SHIFT                18
#define NVIC_ICPR_CLRPEND18_WIDTH                1
#define NVIC_ICPR_CLRPEND18(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ICPR_CLRPEND18_SHIFT))&NVIC_ICPR_CLRPEND18_MASK)
#define NVIC_ICPR_CLRPEND19_MASK                 0x80000u
#define NVIC_ICPR_CLRPEND19_SHIFT                19
#define NVIC_ICPR_CLRPEND19_WIDTH                1
#define NVIC_ICPR_CLRPEND19(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ICPR_CLRPEND19_SHIFT))&NVIC_ICPR_CLRPEND19_MASK)
#define NVIC_ICPR_CLRPEND20_MASK                 0x100000u
#define NVIC_ICPR_CLRPEND20_SHIFT                20
#define NVIC_ICPR_CLRPEND20_WIDTH                1
#define NVIC_ICPR_CLRPEND20(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ICPR_CLRPEND20_SHIFT))&NVIC_ICPR_CLRPEND20_MASK)
#define NVIC_ICPR_CLRPEND21_MASK                 0x200000u
#define NVIC_ICPR_CLRPEND21_SHIFT                21
#define NVIC_ICPR_CLRPEND21_WIDTH                1
#define NVIC_ICPR_CLRPEND21(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ICPR_CLRPEND21_SHIFT))&NVIC_ICPR_CLRPEND21_MASK)
#define NVIC_ICPR_CLRPEND22_MASK                 0x400000u
#define NVIC_ICPR_CLRPEND22_SHIFT                22
#define NVIC_ICPR_CLRPEND22_WIDTH                1
#define NVIC_ICPR_CLRPEND22(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ICPR_CLRPEND22_SHIFT))&NVIC_ICPR_CLRPEND22_MASK)
#define NVIC_ICPR_CLRPEND23_MASK                 0x800000u
#define NVIC_ICPR_CLRPEND23_SHIFT                23
#define NVIC_ICPR_CLRPEND23_WIDTH                1
#define NVIC_ICPR_CLRPEND23(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ICPR_CLRPEND23_SHIFT))&NVIC_ICPR_CLRPEND23_MASK)
#define NVIC_ICPR_CLRPEND24_MASK                 0x1000000u
#define NVIC_ICPR_CLRPEND24_SHIFT                24
#define NVIC_ICPR_CLRPEND24_WIDTH                1
#define NVIC_ICPR_CLRPEND24(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ICPR_CLRPEND24_SHIFT))&NVIC_ICPR_CLRPEND24_MASK)
#define NVIC_ICPR_CLRPEND25_MASK                 0x2000000u
#define NVIC_ICPR_CLRPEND25_SHIFT                25
#define NVIC_ICPR_CLRPEND25_WIDTH                1
#define NVIC_ICPR_CLRPEND25(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ICPR_CLRPEND25_SHIFT))&NVIC_ICPR_CLRPEND25_MASK)
#define NVIC_ICPR_CLRPEND26_MASK                 0x4000000u
#define NVIC_ICPR_CLRPEND26_SHIFT                26
#define NVIC_ICPR_CLRPEND26_WIDTH                1
#define NVIC_ICPR_CLRPEND26(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ICPR_CLRPEND26_SHIFT))&NVIC_ICPR_CLRPEND26_MASK)
#define NVIC_ICPR_CLRPEND27_MASK                 0x8000000u
#define NVIC_ICPR_CLRPEND27_SHIFT                27
#define NVIC_ICPR_CLRPEND27_WIDTH                1
#define NVIC_ICPR_CLRPEND27(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ICPR_CLRPEND27_SHIFT))&NVIC_ICPR_CLRPEND27_MASK)
#define NVIC_ICPR_CLRPEND28_MASK                 0x10000000u
#define NVIC_ICPR_CLRPEND28_SHIFT                28
#define NVIC_ICPR_CLRPEND28_WIDTH                1
#define NVIC_ICPR_CLRPEND28(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ICPR_CLRPEND28_SHIFT))&NVIC_ICPR_CLRPEND28_MASK)
#define NVIC_ICPR_CLRPEND29_MASK                 0x20000000u
#define NVIC_ICPR_CLRPEND29_SHIFT                29
#define NVIC_ICPR_CLRPEND29_WIDTH                1
#define NVIC_ICPR_CLRPEND29(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ICPR_CLRPEND29_SHIFT))&NVIC_ICPR_CLRPEND29_MASK)
#define NVIC_ICPR_CLRPEND30_MASK                 0x40000000u
#define NVIC_ICPR_CLRPEND30_SHIFT                30
#define NVIC_ICPR_CLRPEND30_WIDTH                1
#define NVIC_ICPR_CLRPEND30(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ICPR_CLRPEND30_SHIFT))&NVIC_ICPR_CLRPEND30_MASK)
#define NVIC_ICPR_CLRPEND31_MASK                 0x80000000u
#define NVIC_ICPR_CLRPEND31_SHIFT                31
#define NVIC_ICPR_CLRPEND31_WIDTH                1
#define NVIC_ICPR_CLRPEND31(x)                   (((uint32_t)(((uint32_t)(x))<<NVIC_ICPR_CLRPEND31_SHIFT))&NVIC_ICPR_CLRPEND31_MASK)
/* IP Bit Fields */
#define NVIC_IP_PRI_0_MASK                       0xFFu
#define NVIC_IP_PRI_0_SHIFT                      0
#define NVIC_IP_PRI_0_WIDTH                      8
#define NVIC_IP_PRI_0(x)                         (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_0_SHIFT))&NVIC_IP_PRI_0_MASK)
#define NVIC_IP_PRI_28_MASK                      0xFFu
#define NVIC_IP_PRI_28_SHIFT                     0
#define NVIC_IP_PRI_28_WIDTH                     8
#define NVIC_IP_PRI_28(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_28_SHIFT))&NVIC_IP_PRI_28_MASK)
#define NVIC_IP_PRI_24_MASK                      0xFFu
#define NVIC_IP_PRI_24_SHIFT                     0
#define NVIC_IP_PRI_24_WIDTH                     8
#define NVIC_IP_PRI_24(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_24_SHIFT))&NVIC_IP_PRI_24_MASK)
#define NVIC_IP_PRI_20_MASK                      0xFFu
#define NVIC_IP_PRI_20_SHIFT                     0
#define NVIC_IP_PRI_20_WIDTH                     8
#define NVIC_IP_PRI_20(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_20_SHIFT))&NVIC_IP_PRI_20_MASK)
#define NVIC_IP_PRI_4_MASK                       0xFFu
#define NVIC_IP_PRI_4_SHIFT                      0
#define NVIC_IP_PRI_4_WIDTH                      8
#define NVIC_IP_PRI_4(x)                         (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_4_SHIFT))&NVIC_IP_PRI_4_MASK)
#define NVIC_IP_PRI_16_MASK                      0xFFu
#define NVIC_IP_PRI_16_SHIFT                     0
#define NVIC_IP_PRI_16_WIDTH                     8
#define NVIC_IP_PRI_16(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_16_SHIFT))&NVIC_IP_PRI_16_MASK)
#define NVIC_IP_PRI_12_MASK                      0xFFu
#define NVIC_IP_PRI_12_SHIFT                     0
#define NVIC_IP_PRI_12_WIDTH                     8
#define NVIC_IP_PRI_12(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_12_SHIFT))&NVIC_IP_PRI_12_MASK)
#define NVIC_IP_PRI_8_MASK                       0xFFu
#define NVIC_IP_PRI_8_SHIFT                      0
#define NVIC_IP_PRI_8_WIDTH                      8
#define NVIC_IP_PRI_8(x)                         (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_8_SHIFT))&NVIC_IP_PRI_8_MASK)
#define NVIC_IP_PRI_13_MASK                      0xFF00u
#define NVIC_IP_PRI_13_SHIFT                     8
#define NVIC_IP_PRI_13_WIDTH                     8
#define NVIC_IP_PRI_13(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_13_SHIFT))&NVIC_IP_PRI_13_MASK)
#define NVIC_IP_PRI_21_MASK                      0xFF00u
#define NVIC_IP_PRI_21_SHIFT                     8
#define NVIC_IP_PRI_21_WIDTH                     8
#define NVIC_IP_PRI_21(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_21_SHIFT))&NVIC_IP_PRI_21_MASK)
#define NVIC_IP_PRI_29_MASK                      0xFF00u
#define NVIC_IP_PRI_29_SHIFT                     8
#define NVIC_IP_PRI_29_WIDTH                     8
#define NVIC_IP_PRI_29(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_29_SHIFT))&NVIC_IP_PRI_29_MASK)
#define NVIC_IP_PRI_1_MASK                       0xFF00u
#define NVIC_IP_PRI_1_SHIFT                      8
#define NVIC_IP_PRI_1_WIDTH                      8
#define NVIC_IP_PRI_1(x)                         (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_1_SHIFT))&NVIC_IP_PRI_1_MASK)
#define NVIC_IP_PRI_9_MASK                       0xFF00u
#define NVIC_IP_PRI_9_SHIFT                      8
#define NVIC_IP_PRI_9_WIDTH                      8
#define NVIC_IP_PRI_9(x)                         (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_9_SHIFT))&NVIC_IP_PRI_9_MASK)
#define NVIC_IP_PRI_17_MASK                      0xFF00u
#define NVIC_IP_PRI_17_SHIFT                     8
#define NVIC_IP_PRI_17_WIDTH                     8
#define NVIC_IP_PRI_17(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_17_SHIFT))&NVIC_IP_PRI_17_MASK)
#define NVIC_IP_PRI_25_MASK                      0xFF00u
#define NVIC_IP_PRI_25_SHIFT                     8
#define NVIC_IP_PRI_25_WIDTH                     8
#define NVIC_IP_PRI_25(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_25_SHIFT))&NVIC_IP_PRI_25_MASK)
#define NVIC_IP_PRI_5_MASK                       0xFF00u
#define NVIC_IP_PRI_5_SHIFT                      8
#define NVIC_IP_PRI_5_WIDTH                      8
#define NVIC_IP_PRI_5(x)                         (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_5_SHIFT))&NVIC_IP_PRI_5_MASK)
#define NVIC_IP_PRI_2_MASK                       0xFF0000u
#define NVIC_IP_PRI_2_SHIFT                      16
#define NVIC_IP_PRI_2_WIDTH                      8
#define NVIC_IP_PRI_2(x)                         (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_2_SHIFT))&NVIC_IP_PRI_2_MASK)
#define NVIC_IP_PRI_26_MASK                      0xFF0000u
#define NVIC_IP_PRI_26_SHIFT                     16
#define NVIC_IP_PRI_26_WIDTH                     8
#define NVIC_IP_PRI_26(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_26_SHIFT))&NVIC_IP_PRI_26_MASK)
#define NVIC_IP_PRI_18_MASK                      0xFF0000u
#define NVIC_IP_PRI_18_SHIFT                     16
#define NVIC_IP_PRI_18_WIDTH                     8
#define NVIC_IP_PRI_18(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_18_SHIFT))&NVIC_IP_PRI_18_MASK)
#define NVIC_IP_PRI_14_MASK                      0xFF0000u
#define NVIC_IP_PRI_14_SHIFT                     16
#define NVIC_IP_PRI_14_WIDTH                     8
#define NVIC_IP_PRI_14(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_14_SHIFT))&NVIC_IP_PRI_14_MASK)
#define NVIC_IP_PRI_6_MASK                       0xFF0000u
#define NVIC_IP_PRI_6_SHIFT                      16
#define NVIC_IP_PRI_6_WIDTH                      8
#define NVIC_IP_PRI_6(x)                         (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_6_SHIFT))&NVIC_IP_PRI_6_MASK)
#define NVIC_IP_PRI_30_MASK                      0xFF0000u
#define NVIC_IP_PRI_30_SHIFT                     16
#define NVIC_IP_PRI_30_WIDTH                     8
#define NVIC_IP_PRI_30(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_30_SHIFT))&NVIC_IP_PRI_30_MASK)
#define NVIC_IP_PRI_22_MASK                      0xFF0000u
#define NVIC_IP_PRI_22_SHIFT                     16
#define NVIC_IP_PRI_22_WIDTH                     8
#define NVIC_IP_PRI_22(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_22_SHIFT))&NVIC_IP_PRI_22_MASK)
#define NVIC_IP_PRI_10_MASK                      0xFF0000u
#define NVIC_IP_PRI_10_SHIFT                     16
#define NVIC_IP_PRI_10_WIDTH                     8
#define NVIC_IP_PRI_10(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_10_SHIFT))&NVIC_IP_PRI_10_MASK)
#define NVIC_IP_PRI_31_MASK                      0xFF000000u
#define NVIC_IP_PRI_31_SHIFT                     24
#define NVIC_IP_PRI_31_WIDTH                     8
#define NVIC_IP_PRI_31(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_31_SHIFT))&NVIC_IP_PRI_31_MASK)
#define NVIC_IP_PRI_27_MASK                      0xFF000000u
#define NVIC_IP_PRI_27_SHIFT                     24
#define NVIC_IP_PRI_27_WIDTH                     8
#define NVIC_IP_PRI_27(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_27_SHIFT))&NVIC_IP_PRI_27_MASK)
#define NVIC_IP_PRI_23_MASK                      0xFF000000u
#define NVIC_IP_PRI_23_SHIFT                     24
#define NVIC_IP_PRI_23_WIDTH                     8
#define NVIC_IP_PRI_23(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_23_SHIFT))&NVIC_IP_PRI_23_MASK)
#define NVIC_IP_PRI_3_MASK                       0xFF000000u
#define NVIC_IP_PRI_3_SHIFT                      24
#define NVIC_IP_PRI_3_WIDTH                      8
#define NVIC_IP_PRI_3(x)                         (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_3_SHIFT))&NVIC_IP_PRI_3_MASK)
#define NVIC_IP_PRI_19_MASK                      0xFF000000u
#define NVIC_IP_PRI_19_SHIFT                     24
#define NVIC_IP_PRI_19_WIDTH                     8
#define NVIC_IP_PRI_19(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_19_SHIFT))&NVIC_IP_PRI_19_MASK)
#define NVIC_IP_PRI_15_MASK                      0xFF000000u
#define NVIC_IP_PRI_15_SHIFT                     24
#define NVIC_IP_PRI_15_WIDTH                     8
#define NVIC_IP_PRI_15(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_15_SHIFT))&NVIC_IP_PRI_15_MASK)
#define NVIC_IP_PRI_11_MASK                      0xFF000000u
#define NVIC_IP_PRI_11_SHIFT                     24
#define NVIC_IP_PRI_11_WIDTH                     8
#define NVIC_IP_PRI_11(x)                        (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_11_SHIFT))&NVIC_IP_PRI_11_MASK)
#define NVIC_IP_PRI_7_MASK                       0xFF000000u
#define NVIC_IP_PRI_7_SHIFT                      24
#define NVIC_IP_PRI_7_WIDTH                      8
#define NVIC_IP_PRI_7(x)                         (((uint32_t)(((uint32_t)(x))<<NVIC_IP_PRI_7_SHIFT))&NVIC_IP_PRI_7_MASK)

/*!
 * @}
 */ /* end of group NVIC_Register_Masks */


/* NVIC - Peripheral instance base addresses */
/** Peripheral NVIC base pointer */
#define NVIC_BASE_PTR                            ((NVIC_MemMapPtr)0xE000E100u)
/** Array initializer of NVIC peripheral base pointers */
#define NVIC_BASE_PTRS                           { NVIC_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- NVIC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NVIC_Register_Accessor_Macros NVIC - Register accessor macros
 * @{
 */


/* NVIC - Register instance definitions */
/* NVIC */
#define NVIC_ISER                                NVIC_ISER_REG(NVIC_BASE_PTR)
#define NVIC_ICER                                NVIC_ICER_REG(NVIC_BASE_PTR)
#define NVIC_ISPR                                NVIC_ISPR_REG(NVIC_BASE_PTR)
#define NVIC_ICPR                                NVIC_ICPR_REG(NVIC_BASE_PTR)
#define NVIC_IPR0                                NVIC_IP_REG(NVIC_BASE_PTR,0)
#define NVIC_IPR1                                NVIC_IP_REG(NVIC_BASE_PTR,1)
#define NVIC_IPR2                                NVIC_IP_REG(NVIC_BASE_PTR,2)
#define NVIC_IPR3                                NVIC_IP_REG(NVIC_BASE_PTR,3)
#define NVIC_IPR4                                NVIC_IP_REG(NVIC_BASE_PTR,4)
#define NVIC_IPR5                                NVIC_IP_REG(NVIC_BASE_PTR,5)
#define NVIC_IPR6                                NVIC_IP_REG(NVIC_BASE_PTR,6)
#define NVIC_IPR7                                NVIC_IP_REG(NVIC_BASE_PTR,7)

/* NVIC - Register array accessors */
#define NVIC_IP(index)                           NVIC_IP_REG(NVIC_BASE_PTR,index)

/*!
 * @}
 */ /* end of group NVIC_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group NVIC_Peripheral */


/* ----------------------------------------------------------------------------
   -- OSC
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OSC_Peripheral OSC
 * @{
 */

/** OSC - Peripheral register structure */
typedef struct OSC_MemMap {
  uint8_t CR;                                      /**< OSC Control Register, offset: 0x0 */
} volatile *OSC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- OSC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OSC_Register_Accessor_Macros OSC - Register accessor macros
 * @{
 */


/* OSC - Register accessors */
#define OSC_CR_REG(base)                         ((base)->CR)

/*!
 * @}
 */ /* end of group OSC_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- OSC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OSC_Register_Masks OSC Register Masks
 * @{
 */

/* CR Bit Fields */
#define OSC_CR_OSCINIT_MASK                      0x1u
#define OSC_CR_OSCINIT_SHIFT                     0
#define OSC_CR_OSCINIT_WIDTH                     1
#define OSC_CR_OSCINIT(x)                        (((uint8_t)(((uint8_t)(x))<<OSC_CR_OSCINIT_SHIFT))&OSC_CR_OSCINIT_MASK)
#define OSC_CR_HGO_MASK                          0x2u
#define OSC_CR_HGO_SHIFT                         1
#define OSC_CR_HGO_WIDTH                         1
#define OSC_CR_HGO(x)                            (((uint8_t)(((uint8_t)(x))<<OSC_CR_HGO_SHIFT))&OSC_CR_HGO_MASK)
#define OSC_CR_RANGE_MASK                        0x4u
#define OSC_CR_RANGE_SHIFT                       2
#define OSC_CR_RANGE_WIDTH                       1
#define OSC_CR_RANGE(x)                          (((uint8_t)(((uint8_t)(x))<<OSC_CR_RANGE_SHIFT))&OSC_CR_RANGE_MASK)
#define OSC_CR_OSCOS_MASK                        0x10u
#define OSC_CR_OSCOS_SHIFT                       4
#define OSC_CR_OSCOS_WIDTH                       1
#define OSC_CR_OSCOS(x)                          (((uint8_t)(((uint8_t)(x))<<OSC_CR_OSCOS_SHIFT))&OSC_CR_OSCOS_MASK)
#define OSC_CR_OSCSTEN_MASK                      0x20u
#define OSC_CR_OSCSTEN_SHIFT                     5
#define OSC_CR_OSCSTEN_WIDTH                     1
#define OSC_CR_OSCSTEN(x)                        (((uint8_t)(((uint8_t)(x))<<OSC_CR_OSCSTEN_SHIFT))&OSC_CR_OSCSTEN_MASK)
#define OSC_CR_OSCEN_MASK                        0x80u
#define OSC_CR_OSCEN_SHIFT                       7
#define OSC_CR_OSCEN_WIDTH                       1
#define OSC_CR_OSCEN(x)                          (((uint8_t)(((uint8_t)(x))<<OSC_CR_OSCEN_SHIFT))&OSC_CR_OSCEN_MASK)

/*!
 * @}
 */ /* end of group OSC_Register_Masks */


/* OSC - Peripheral instance base addresses */
/** Peripheral OSC base pointer */
#define OSC_BASE_PTR                             ((OSC_MemMapPtr)0x40065000u)
/** Array initializer of OSC peripheral base pointers */
#define OSC_BASE_PTRS                            { OSC_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- OSC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OSC_Register_Accessor_Macros OSC - Register accessor macros
 * @{
 */


/* OSC - Register instance definitions */
/* OSC */
#define OSC_CR                                   OSC_CR_REG(OSC_BASE_PTR)

/*!
 * @}
 */ /* end of group OSC_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group OSC_Peripheral */


/* ----------------------------------------------------------------------------
   -- PIT
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PIT_Peripheral PIT
 * @{
 */

/** PIT - Peripheral register structure */
typedef struct PIT_MemMap {
  uint32_t MCR;                                    /**< PIT Module Control Register, offset: 0x0 */
  uint8_t RESERVED_0[252];
  struct {                                         /* offset: 0x100, array step: 0x10 */
    uint32_t LDVAL;                                  /**< Timer Load Value Register, array offset: 0x100, array step: 0x10 */
    uint32_t CVAL;                                   /**< Current Timer Value Register, array offset: 0x104, array step: 0x10 */
    uint32_t TCTRL;                                  /**< Timer Control Register, array offset: 0x108, array step: 0x10 */
    uint32_t TFLG;                                   /**< Timer Flag Register, array offset: 0x10C, array step: 0x10 */
  } CHANNEL[2];
} volatile *PIT_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- PIT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PIT_Register_Accessor_Macros PIT - Register accessor macros
 * @{
 */


/* PIT - Register accessors */
#define PIT_MCR_REG(base)                        ((base)->MCR)
#define PIT_LDVAL_REG(base,index)                ((base)->CHANNEL[index].LDVAL)
#define PIT_LDVAL_COUNT                          2
#define PIT_CVAL_REG(base,index)                 ((base)->CHANNEL[index].CVAL)
#define PIT_CVAL_COUNT                           2
#define PIT_TCTRL_REG(base,index)                ((base)->CHANNEL[index].TCTRL)
#define PIT_TCTRL_COUNT                          2
#define PIT_TFLG_REG(base,index)                 ((base)->CHANNEL[index].TFLG)
#define PIT_TFLG_COUNT                           2

/*!
 * @}
 */ /* end of group PIT_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- PIT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PIT_Register_Masks PIT Register Masks
 * @{
 */

/* MCR Bit Fields */
#define PIT_MCR_FRZ_MASK                         0x1u
#define PIT_MCR_FRZ_SHIFT                        0
#define PIT_MCR_FRZ_WIDTH                        1
#define PIT_MCR_FRZ(x)                           (((uint32_t)(((uint32_t)(x))<<PIT_MCR_FRZ_SHIFT))&PIT_MCR_FRZ_MASK)
#define PIT_MCR_MDIS_MASK                        0x2u
#define PIT_MCR_MDIS_SHIFT                       1
#define PIT_MCR_MDIS_WIDTH                       1
#define PIT_MCR_MDIS(x)                          (((uint32_t)(((uint32_t)(x))<<PIT_MCR_MDIS_SHIFT))&PIT_MCR_MDIS_MASK)
/* LDVAL Bit Fields */
#define PIT_LDVAL_TSV_MASK                       0xFFFFFFFFu
#define PIT_LDVAL_TSV_SHIFT                      0
#define PIT_LDVAL_TSV_WIDTH                      32
#define PIT_LDVAL_TSV(x)                         (((uint32_t)(((uint32_t)(x))<<PIT_LDVAL_TSV_SHIFT))&PIT_LDVAL_TSV_MASK)
/* CVAL Bit Fields */
#define PIT_CVAL_TVL_MASK                        0xFFFFFFFFu
#define PIT_CVAL_TVL_SHIFT                       0
#define PIT_CVAL_TVL_WIDTH                       32
#define PIT_CVAL_TVL(x)                          (((uint32_t)(((uint32_t)(x))<<PIT_CVAL_TVL_SHIFT))&PIT_CVAL_TVL_MASK)
/* TCTRL Bit Fields */
#define PIT_TCTRL_TEN_MASK                       0x1u
#define PIT_TCTRL_TEN_SHIFT                      0
#define PIT_TCTRL_TEN_WIDTH                      1
#define PIT_TCTRL_TEN(x)                         (((uint32_t)(((uint32_t)(x))<<PIT_TCTRL_TEN_SHIFT))&PIT_TCTRL_TEN_MASK)
#define PIT_TCTRL_TIE_MASK                       0x2u
#define PIT_TCTRL_TIE_SHIFT                      1
#define PIT_TCTRL_TIE_WIDTH                      1
#define PIT_TCTRL_TIE(x)                         (((uint32_t)(((uint32_t)(x))<<PIT_TCTRL_TIE_SHIFT))&PIT_TCTRL_TIE_MASK)
#define PIT_TCTRL_CHN_MASK                       0x4u
#define PIT_TCTRL_CHN_SHIFT                      2
#define PIT_TCTRL_CHN_WIDTH                      1
#define PIT_TCTRL_CHN(x)                         (((uint32_t)(((uint32_t)(x))<<PIT_TCTRL_CHN_SHIFT))&PIT_TCTRL_CHN_MASK)
/* TFLG Bit Fields */
#define PIT_TFLG_TIF_MASK                        0x1u
#define PIT_TFLG_TIF_SHIFT                       0
#define PIT_TFLG_TIF_WIDTH                       1
#define PIT_TFLG_TIF(x)                          (((uint32_t)(((uint32_t)(x))<<PIT_TFLG_TIF_SHIFT))&PIT_TFLG_TIF_MASK)

/*!
 * @}
 */ /* end of group PIT_Register_Masks */


/* PIT - Peripheral instance base addresses */
/** Peripheral PIT base pointer */
#define PIT_BASE_PTR                             ((PIT_MemMapPtr)0x40037000u)
/** Array initializer of PIT peripheral base pointers */
#define PIT_BASE_PTRS                            { PIT_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- PIT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PIT_Register_Accessor_Macros PIT - Register accessor macros
 * @{
 */


/* PIT - Register instance definitions */
/* PIT */
#define PIT_MCR                                  PIT_MCR_REG(PIT_BASE_PTR)
#define PIT_LDVAL0                               PIT_LDVAL_REG(PIT_BASE_PTR,0)
#define PIT_CVAL0                                PIT_CVAL_REG(PIT_BASE_PTR,0)
#define PIT_TCTRL0                               PIT_TCTRL_REG(PIT_BASE_PTR,0)
#define PIT_TFLG0                                PIT_TFLG_REG(PIT_BASE_PTR,0)
#define PIT_LDVAL1                               PIT_LDVAL_REG(PIT_BASE_PTR,1)
#define PIT_CVAL1                                PIT_CVAL_REG(PIT_BASE_PTR,1)
#define PIT_TCTRL1                               PIT_TCTRL_REG(PIT_BASE_PTR,1)
#define PIT_TFLG1                                PIT_TFLG_REG(PIT_BASE_PTR,1)

/* PIT - Register array accessors */
#define PIT_LDVAL(index)                         PIT_LDVAL_REG(PIT_BASE_PTR,index)
#define PIT_CVAL(index)                          PIT_CVAL_REG(PIT_BASE_PTR,index)
#define PIT_TCTRL(index)                         PIT_TCTRL_REG(PIT_BASE_PTR,index)
#define PIT_TFLG(index)                          PIT_TFLG_REG(PIT_BASE_PTR,index)

/*!
 * @}
 */ /* end of group PIT_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group PIT_Peripheral */


/* ----------------------------------------------------------------------------
   -- PMC
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PMC_Peripheral PMC
 * @{
 */

/** PMC - Peripheral register structure */
typedef struct PMC_MemMap {
  uint8_t SPMSC1;                                  /**< System Power Management Status and Control 1 Register, offset: 0x0 */
  uint8_t SPMSC2;                                  /**< System Power Management Status and Control 2 Register, offset: 0x1 */
} volatile *PMC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- PMC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PMC_Register_Accessor_Macros PMC - Register accessor macros
 * @{
 */


/* PMC - Register accessors */
#define PMC_SPMSC1_REG(base)                     ((base)->SPMSC1)
#define PMC_SPMSC2_REG(base)                     ((base)->SPMSC2)

/*!
 * @}
 */ /* end of group PMC_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- PMC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PMC_Register_Masks PMC Register Masks
 * @{
 */

/* SPMSC1 Bit Fields */
#define PMC_SPMSC1_BGBE_MASK                     0x1u
#define PMC_SPMSC1_BGBE_SHIFT                    0
#define PMC_SPMSC1_BGBE_WIDTH                    1
#define PMC_SPMSC1_BGBE(x)                       (((uint8_t)(((uint8_t)(x))<<PMC_SPMSC1_BGBE_SHIFT))&PMC_SPMSC1_BGBE_MASK)
#define PMC_SPMSC1_LVDE_MASK                     0x4u
#define PMC_SPMSC1_LVDE_SHIFT                    2
#define PMC_SPMSC1_LVDE_WIDTH                    1
#define PMC_SPMSC1_LVDE(x)                       (((uint8_t)(((uint8_t)(x))<<PMC_SPMSC1_LVDE_SHIFT))&PMC_SPMSC1_LVDE_MASK)
#define PMC_SPMSC1_LVDSE_MASK                    0x8u
#define PMC_SPMSC1_LVDSE_SHIFT                   3
#define PMC_SPMSC1_LVDSE_WIDTH                   1
#define PMC_SPMSC1_LVDSE(x)                      (((uint8_t)(((uint8_t)(x))<<PMC_SPMSC1_LVDSE_SHIFT))&PMC_SPMSC1_LVDSE_MASK)
#define PMC_SPMSC1_LVDRE_MASK                    0x10u
#define PMC_SPMSC1_LVDRE_SHIFT                   4
#define PMC_SPMSC1_LVDRE_WIDTH                   1
#define PMC_SPMSC1_LVDRE(x)                      (((uint8_t)(((uint8_t)(x))<<PMC_SPMSC1_LVDRE_SHIFT))&PMC_SPMSC1_LVDRE_MASK)
#define PMC_SPMSC1_LVWIE_MASK                    0x20u
#define PMC_SPMSC1_LVWIE_SHIFT                   5
#define PMC_SPMSC1_LVWIE_WIDTH                   1
#define PMC_SPMSC1_LVWIE(x)                      (((uint8_t)(((uint8_t)(x))<<PMC_SPMSC1_LVWIE_SHIFT))&PMC_SPMSC1_LVWIE_MASK)
#define PMC_SPMSC1_LVWACK_MASK                   0x40u
#define PMC_SPMSC1_LVWACK_SHIFT                  6
#define PMC_SPMSC1_LVWACK_WIDTH                  1
#define PMC_SPMSC1_LVWACK(x)                     (((uint8_t)(((uint8_t)(x))<<PMC_SPMSC1_LVWACK_SHIFT))&PMC_SPMSC1_LVWACK_MASK)
#define PMC_SPMSC1_LVWF_MASK                     0x80u
#define PMC_SPMSC1_LVWF_SHIFT                    7
#define PMC_SPMSC1_LVWF_WIDTH                    1
#define PMC_SPMSC1_LVWF(x)                       (((uint8_t)(((uint8_t)(x))<<PMC_SPMSC1_LVWF_SHIFT))&PMC_SPMSC1_LVWF_MASK)
/* SPMSC2 Bit Fields */
#define PMC_SPMSC2_LVWV_MASK                     0x30u
#define PMC_SPMSC2_LVWV_SHIFT                    4
#define PMC_SPMSC2_LVWV_WIDTH                    2
#define PMC_SPMSC2_LVWV(x)                       (((uint8_t)(((uint8_t)(x))<<PMC_SPMSC2_LVWV_SHIFT))&PMC_SPMSC2_LVWV_MASK)
#define PMC_SPMSC2_LVDV_MASK                     0x40u
#define PMC_SPMSC2_LVDV_SHIFT                    6
#define PMC_SPMSC2_LVDV_WIDTH                    1
#define PMC_SPMSC2_LVDV(x)                       (((uint8_t)(((uint8_t)(x))<<PMC_SPMSC2_LVDV_SHIFT))&PMC_SPMSC2_LVDV_MASK)

/*!
 * @}
 */ /* end of group PMC_Register_Masks */


/* PMC - Peripheral instance base addresses */
/** Peripheral PMC base pointer */
#define PMC_BASE_PTR                             ((PMC_MemMapPtr)0x4007D000u)
/** Array initializer of PMC peripheral base pointers */
#define PMC_BASE_PTRS                            { PMC_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- PMC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PMC_Register_Accessor_Macros PMC - Register accessor macros
 * @{
 */


/* PMC - Register instance definitions */
/* PMC */
#define PMC_SPMSC1                               PMC_SPMSC1_REG(PMC_BASE_PTR)
#define PMC_SPMSC2                               PMC_SPMSC2_REG(PMC_BASE_PTR)

/*!
 * @}
 */ /* end of group PMC_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group PMC_Peripheral */


/* ----------------------------------------------------------------------------
   -- PORT
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PORT_Peripheral PORT
 * @{
 */

/** PORT - Peripheral register structure */
typedef struct PORT_MemMap {
  uint32_t IOFLT;                                  /**< Port Filter Register, offset: 0x0 */
  uint32_t PUEL;                                   /**< Port Pullup Enable Low Register, offset: 0x4 */
  uint32_t PUEH;                                   /**< Port Pullup Enable High Register, offset: 0x8 */
  uint32_t HDRVE;                                  /**< Port High Drive Enable Register, offset: 0xC */
} volatile *PORT_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- PORT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PORT_Register_Accessor_Macros PORT - Register accessor macros
 * @{
 */


/* PORT - Register accessors */
#define PORT_IOFLT_REG(base)                     ((base)->IOFLT)
#define PORT_PUEL_REG(base)                      ((base)->PUEL)
#define PORT_PUEH_REG(base)                      ((base)->PUEH)
#define PORT_HDRVE_REG(base)                     ((base)->HDRVE)

/*!
 * @}
 */ /* end of group PORT_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- PORT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PORT_Register_Masks PORT Register Masks
 * @{
 */

/* IOFLT Bit Fields */
#define PORT_IOFLT_FLTA_MASK                     0x3u
#define PORT_IOFLT_FLTA_SHIFT                    0
#define PORT_IOFLT_FLTA_WIDTH                    2
#define PORT_IOFLT_FLTA(x)                       (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT_FLTA_SHIFT))&PORT_IOFLT_FLTA_MASK)
#define PORT_IOFLT_FLTB_MASK                     0xCu
#define PORT_IOFLT_FLTB_SHIFT                    2
#define PORT_IOFLT_FLTB_WIDTH                    2
#define PORT_IOFLT_FLTB(x)                       (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT_FLTB_SHIFT))&PORT_IOFLT_FLTB_MASK)
#define PORT_IOFLT_FLTC_MASK                     0x30u
#define PORT_IOFLT_FLTC_SHIFT                    4
#define PORT_IOFLT_FLTC_WIDTH                    2
#define PORT_IOFLT_FLTC(x)                       (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT_FLTC_SHIFT))&PORT_IOFLT_FLTC_MASK)
#define PORT_IOFLT_FLTD_MASK                     0xC0u
#define PORT_IOFLT_FLTD_SHIFT                    6
#define PORT_IOFLT_FLTD_WIDTH                    2
#define PORT_IOFLT_FLTD(x)                       (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT_FLTD_SHIFT))&PORT_IOFLT_FLTD_MASK)
#define PORT_IOFLT_FLTE_MASK                     0x300u
#define PORT_IOFLT_FLTE_SHIFT                    8
#define PORT_IOFLT_FLTE_WIDTH                    2
#define PORT_IOFLT_FLTE(x)                       (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT_FLTE_SHIFT))&PORT_IOFLT_FLTE_MASK)
#define PORT_IOFLT_FLTF_MASK                     0xC00u
#define PORT_IOFLT_FLTF_SHIFT                    10
#define PORT_IOFLT_FLTF_WIDTH                    2
#define PORT_IOFLT_FLTF(x)                       (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT_FLTF_SHIFT))&PORT_IOFLT_FLTF_MASK)
#define PORT_IOFLT_FLTG_MASK                     0x3000u
#define PORT_IOFLT_FLTG_SHIFT                    12
#define PORT_IOFLT_FLTG_WIDTH                    2
#define PORT_IOFLT_FLTG(x)                       (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT_FLTG_SHIFT))&PORT_IOFLT_FLTG_MASK)
#define PORT_IOFLT_FLTH_MASK                     0xC000u
#define PORT_IOFLT_FLTH_SHIFT                    14
#define PORT_IOFLT_FLTH_WIDTH                    2
#define PORT_IOFLT_FLTH(x)                       (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT_FLTH_SHIFT))&PORT_IOFLT_FLTH_MASK)
#define PORT_IOFLT_FLTRST_MASK                   0x30000u
#define PORT_IOFLT_FLTRST_SHIFT                  16
#define PORT_IOFLT_FLTRST_WIDTH                  2
#define PORT_IOFLT_FLTRST(x)                     (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT_FLTRST_SHIFT))&PORT_IOFLT_FLTRST_MASK)
#define PORT_IOFLT_FLTKBI0_MASK                  0xC0000u
#define PORT_IOFLT_FLTKBI0_SHIFT                 18
#define PORT_IOFLT_FLTKBI0_WIDTH                 2
#define PORT_IOFLT_FLTKBI0(x)                    (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT_FLTKBI0_SHIFT))&PORT_IOFLT_FLTKBI0_MASK)
#define PORT_IOFLT_FLTKBI1_MASK                  0x300000u
#define PORT_IOFLT_FLTKBI1_SHIFT                 20
#define PORT_IOFLT_FLTKBI1_WIDTH                 2
#define PORT_IOFLT_FLTKBI1(x)                    (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT_FLTKBI1_SHIFT))&PORT_IOFLT_FLTKBI1_MASK)
#define PORT_IOFLT_FLTNMI_MASK                   0xC00000u
#define PORT_IOFLT_FLTNMI_SHIFT                  22
#define PORT_IOFLT_FLTNMI_WIDTH                  2
#define PORT_IOFLT_FLTNMI(x)                     (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT_FLTNMI_SHIFT))&PORT_IOFLT_FLTNMI_MASK)
#define PORT_IOFLT_FLTDIV1_MASK                  0x3000000u
#define PORT_IOFLT_FLTDIV1_SHIFT                 24
#define PORT_IOFLT_FLTDIV1_WIDTH                 2
#define PORT_IOFLT_FLTDIV1(x)                    (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT_FLTDIV1_SHIFT))&PORT_IOFLT_FLTDIV1_MASK)
#define PORT_IOFLT_FLTDIV2_MASK                  0x1C000000u
#define PORT_IOFLT_FLTDIV2_SHIFT                 26
#define PORT_IOFLT_FLTDIV2_WIDTH                 3
#define PORT_IOFLT_FLTDIV2(x)                    (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT_FLTDIV2_SHIFT))&PORT_IOFLT_FLTDIV2_MASK)
#define PORT_IOFLT_FLTDIV3_MASK                  0xE0000000u
#define PORT_IOFLT_FLTDIV3_SHIFT                 29
#define PORT_IOFLT_FLTDIV3_WIDTH                 3
#define PORT_IOFLT_FLTDIV3(x)                    (((uint32_t)(((uint32_t)(x))<<PORT_IOFLT_FLTDIV3_SHIFT))&PORT_IOFLT_FLTDIV3_MASK)
/* PUEL Bit Fields */
#define PORT_PUEL_PTAPE0_MASK                    0x1u
#define PORT_PUEL_PTAPE0_SHIFT                   0
#define PORT_PUEL_PTAPE0_WIDTH                   1
#define PORT_PUEL_PTAPE0(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEL_PTAPE0_SHIFT))&PORT_PUEL_PTAPE0_MASK)
#define PORT_PUEL_PTAPE1_MASK                    0x2u
#define PORT_PUEL_PTAPE1_SHIFT                   1
#define PORT_PUEL_PTAPE1_WIDTH                   1
#define PORT_PUEL_PTAPE1(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEL_PTAPE1_SHIFT))&PORT_PUEL_PTAPE1_MASK)
#define PORT_PUEL_PTAPE2_MASK                    0x4u
#define PORT_PUEL_PTAPE2_SHIFT                   2
#define PORT_PUEL_PTAPE2_WIDTH                   1
#define PORT_PUEL_PTAPE2(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEL_PTAPE2_SHIFT))&PORT_PUEL_PTAPE2_MASK)
#define PORT_PUEL_PTAPE3_MASK                    0x8u
#define PORT_PUEL_PTAPE3_SHIFT                   3
#define PORT_PUEL_PTAPE3_WIDTH                   1
#define PORT_PUEL_PTAPE3(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEL_PTAPE3_SHIFT))&PORT_PUEL_PTAPE3_MASK)
#define PORT_PUEL_PTAPE4_MASK                    0x10u
#define PORT_PUEL_PTAPE4_SHIFT                   4
#define PORT_PUEL_PTAPE4_WIDTH                   1
#define PORT_PUEL_PTAPE4(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEL_PTAPE4_SHIFT))&PORT_PUEL_PTAPE4_MASK)
#define PORT_PUEL_PTAPE5_MASK                    0x20u
#define PORT_PUEL_PTAPE5_SHIFT                   5
#define PORT_PUEL_PTAPE5_WIDTH                   1
#define PORT_PUEL_PTAPE5(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEL_PTAPE5_SHIFT))&PORT_PUEL_PTAPE5_MASK)
#define PORT_PUEL_PTAPE6_MASK                    0x40u
#define PORT_PUEL_PTAPE6_SHIFT                   6
#define PORT_PUEL_PTAPE6_WIDTH                   1
#define PORT_PUEL_PTAPE6(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEL_PTAPE6_SHIFT))&PORT_PUEL_PTAPE6_MASK)
#define PORT_PUEL_PTAPE7_MASK                    0x80u
#define PORT_PUEL_PTAPE7_SHIFT                   7
#define PORT_PUEL_PTAPE7_WIDTH                   1
#define PORT_PUEL_PTAPE7(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEL_PTAPE7_SHIFT))&PORT_PUEL_PTAPE7_MASK)
#define PORT_PUEL_PTBPE0_MASK                    0x100u
#define PORT_PUEL_PTBPE0_SHIFT                   8
#define PORT_PUEL_PTBPE0_WIDTH                   1
#define PORT_PUEL_PTBPE0(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEL_PTBPE0_SHIFT))&PORT_PUEL_PTBPE0_MASK)
#define PORT_PUEL_PTBPE1_MASK                    0x200u
#define PORT_PUEL_PTBPE1_SHIFT                   9
#define PORT_PUEL_PTBPE1_WIDTH                   1
#define PORT_PUEL_PTBPE1(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEL_PTBPE1_SHIFT))&PORT_PUEL_PTBPE1_MASK)
#define PORT_PUEL_PTBPE2_MASK                    0x400u
#define PORT_PUEL_PTBPE2_SHIFT                   10
#define PORT_PUEL_PTBPE2_WIDTH                   1
#define PORT_PUEL_PTBPE2(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEL_PTBPE2_SHIFT))&PORT_PUEL_PTBPE2_MASK)
#define PORT_PUEL_PTBPE3_MASK                    0x800u
#define PORT_PUEL_PTBPE3_SHIFT                   11
#define PORT_PUEL_PTBPE3_WIDTH                   1
#define PORT_PUEL_PTBPE3(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEL_PTBPE3_SHIFT))&PORT_PUEL_PTBPE3_MASK)
#define PORT_PUEL_PTBPE4_MASK                    0x1000u
#define PORT_PUEL_PTBPE4_SHIFT                   12
#define PORT_PUEL_PTBPE4_WIDTH                   1
#define PORT_PUEL_PTBPE4(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEL_PTBPE4_SHIFT))&PORT_PUEL_PTBPE4_MASK)
#define PORT_PUEL_PTBPE5_MASK                    0x2000u
#define PORT_PUEL_PTBPE5_SHIFT                   13
#define PORT_PUEL_PTBPE5_WIDTH                   1
#define PORT_PUEL_PTBPE5(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEL_PTBPE5_SHIFT))&PORT_PUEL_PTBPE5_MASK)
#define PORT_PUEL_PTBPE6_MASK                    0x4000u
#define PORT_PUEL_PTBPE6_SHIFT                   14
#define PORT_PUEL_PTBPE6_WIDTH                   1
#define PORT_PUEL_PTBPE6(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEL_PTBPE6_SHIFT))&PORT_PUEL_PTBPE6_MASK)
#define PORT_PUEL_PTBPE7_MASK                    0x8000u
#define PORT_PUEL_PTBPE7_SHIFT                   15
#define PORT_PUEL_PTBPE7_WIDTH                   1
#define PORT_PUEL_PTBPE7(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEL_PTBPE7_SHIFT))&PORT_PUEL_PTBPE7_MASK)
#define PORT_PUEL_PTCPE0_MASK                    0x10000u
#define PORT_PUEL_PTCPE0_SHIFT                   16
#define PORT_PUEL_PTCPE0_WIDTH                   1
#define PORT_PUEL_PTCPE0(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEL_PTCPE0_SHIFT))&PORT_PUEL_PTCPE0_MASK)
#define PORT_PUEL_PTCPE1_MASK                    0x20000u
#define PORT_PUEL_PTCPE1_SHIFT                   17
#define PORT_PUEL_PTCPE1_WIDTH                   1
#define PORT_PUEL_PTCPE1(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEL_PTCPE1_SHIFT))&PORT_PUEL_PTCPE1_MASK)
#define PORT_PUEL_PTCPE2_MASK                    0x40000u
#define PORT_PUEL_PTCPE2_SHIFT                   18
#define PORT_PUEL_PTCPE2_WIDTH                   1
#define PORT_PUEL_PTCPE2(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEL_PTCPE2_SHIFT))&PORT_PUEL_PTCPE2_MASK)
#define PORT_PUEL_PTCPE3_MASK                    0x80000u
#define PORT_PUEL_PTCPE3_SHIFT                   19
#define PORT_PUEL_PTCPE3_WIDTH                   1
#define PORT_PUEL_PTCPE3(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEL_PTCPE3_SHIFT))&PORT_PUEL_PTCPE3_MASK)
#define PORT_PUEL_PTCPE4_MASK                    0x100000u
#define PORT_PUEL_PTCPE4_SHIFT                   20
#define PORT_PUEL_PTCPE4_WIDTH                   1
#define PORT_PUEL_PTCPE4(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEL_PTCPE4_SHIFT))&PORT_PUEL_PTCPE4_MASK)
#define PORT_PUEL_PTCPE5_MASK                    0x200000u
#define PORT_PUEL_PTCPE5_SHIFT                   21
#define PORT_PUEL_PTCPE5_WIDTH                   1
#define PORT_PUEL_PTCPE5(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEL_PTCPE5_SHIFT))&PORT_PUEL_PTCPE5_MASK)
#define PORT_PUEL_PTCPE6_MASK                    0x400000u
#define PORT_PUEL_PTCPE6_SHIFT                   22
#define PORT_PUEL_PTCPE6_WIDTH                   1
#define PORT_PUEL_PTCPE6(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEL_PTCPE6_SHIFT))&PORT_PUEL_PTCPE6_MASK)
#define PORT_PUEL_PTCPE7_MASK                    0x800000u
#define PORT_PUEL_PTCPE7_SHIFT                   23
#define PORT_PUEL_PTCPE7_WIDTH                   1
#define PORT_PUEL_PTCPE7(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEL_PTCPE7_SHIFT))&PORT_PUEL_PTCPE7_MASK)
#define PORT_PUEL_PTDPE0_MASK                    0x1000000u
#define PORT_PUEL_PTDPE0_SHIFT                   24
#define PORT_PUEL_PTDPE0_WIDTH                   1
#define PORT_PUEL_PTDPE0(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEL_PTDPE0_SHIFT))&PORT_PUEL_PTDPE0_MASK)
#define PORT_PUEL_PTDPE1_MASK                    0x2000000u
#define PORT_PUEL_PTDPE1_SHIFT                   25
#define PORT_PUEL_PTDPE1_WIDTH                   1
#define PORT_PUEL_PTDPE1(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEL_PTDPE1_SHIFT))&PORT_PUEL_PTDPE1_MASK)
#define PORT_PUEL_PTDPE2_MASK                    0x4000000u
#define PORT_PUEL_PTDPE2_SHIFT                   26
#define PORT_PUEL_PTDPE2_WIDTH                   1
#define PORT_PUEL_PTDPE2(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEL_PTDPE2_SHIFT))&PORT_PUEL_PTDPE2_MASK)
#define PORT_PUEL_PTDPE3_MASK                    0x8000000u
#define PORT_PUEL_PTDPE3_SHIFT                   27
#define PORT_PUEL_PTDPE3_WIDTH                   1
#define PORT_PUEL_PTDPE3(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEL_PTDPE3_SHIFT))&PORT_PUEL_PTDPE3_MASK)
#define PORT_PUEL_PTDPE4_MASK                    0x10000000u
#define PORT_PUEL_PTDPE4_SHIFT                   28
#define PORT_PUEL_PTDPE4_WIDTH                   1
#define PORT_PUEL_PTDPE4(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEL_PTDPE4_SHIFT))&PORT_PUEL_PTDPE4_MASK)
#define PORT_PUEL_PTDPE5_MASK                    0x20000000u
#define PORT_PUEL_PTDPE5_SHIFT                   29
#define PORT_PUEL_PTDPE5_WIDTH                   1
#define PORT_PUEL_PTDPE5(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEL_PTDPE5_SHIFT))&PORT_PUEL_PTDPE5_MASK)
#define PORT_PUEL_PTDPE6_MASK                    0x40000000u
#define PORT_PUEL_PTDPE6_SHIFT                   30
#define PORT_PUEL_PTDPE6_WIDTH                   1
#define PORT_PUEL_PTDPE6(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEL_PTDPE6_SHIFT))&PORT_PUEL_PTDPE6_MASK)
#define PORT_PUEL_PTDPE7_MASK                    0x80000000u
#define PORT_PUEL_PTDPE7_SHIFT                   31
#define PORT_PUEL_PTDPE7_WIDTH                   1
#define PORT_PUEL_PTDPE7(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEL_PTDPE7_SHIFT))&PORT_PUEL_PTDPE7_MASK)
/* PUEH Bit Fields */
#define PORT_PUEH_PTEPE0_MASK                    0x1u
#define PORT_PUEH_PTEPE0_SHIFT                   0
#define PORT_PUEH_PTEPE0_WIDTH                   1
#define PORT_PUEH_PTEPE0(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEH_PTEPE0_SHIFT))&PORT_PUEH_PTEPE0_MASK)
#define PORT_PUEH_PTEPE1_MASK                    0x2u
#define PORT_PUEH_PTEPE1_SHIFT                   1
#define PORT_PUEH_PTEPE1_WIDTH                   1
#define PORT_PUEH_PTEPE1(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEH_PTEPE1_SHIFT))&PORT_PUEH_PTEPE1_MASK)
#define PORT_PUEH_PTEPE2_MASK                    0x4u
#define PORT_PUEH_PTEPE2_SHIFT                   2
#define PORT_PUEH_PTEPE2_WIDTH                   1
#define PORT_PUEH_PTEPE2(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEH_PTEPE2_SHIFT))&PORT_PUEH_PTEPE2_MASK)
#define PORT_PUEH_PTEPE3_MASK                    0x8u
#define PORT_PUEH_PTEPE3_SHIFT                   3
#define PORT_PUEH_PTEPE3_WIDTH                   1
#define PORT_PUEH_PTEPE3(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEH_PTEPE3_SHIFT))&PORT_PUEH_PTEPE3_MASK)
#define PORT_PUEH_PTEPE4_MASK                    0x10u
#define PORT_PUEH_PTEPE4_SHIFT                   4
#define PORT_PUEH_PTEPE4_WIDTH                   1
#define PORT_PUEH_PTEPE4(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEH_PTEPE4_SHIFT))&PORT_PUEH_PTEPE4_MASK)
#define PORT_PUEH_PTEPE5_MASK                    0x20u
#define PORT_PUEH_PTEPE5_SHIFT                   5
#define PORT_PUEH_PTEPE5_WIDTH                   1
#define PORT_PUEH_PTEPE5(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEH_PTEPE5_SHIFT))&PORT_PUEH_PTEPE5_MASK)
#define PORT_PUEH_PTEPE6_MASK                    0x40u
#define PORT_PUEH_PTEPE6_SHIFT                   6
#define PORT_PUEH_PTEPE6_WIDTH                   1
#define PORT_PUEH_PTEPE6(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEH_PTEPE6_SHIFT))&PORT_PUEH_PTEPE6_MASK)
#define PORT_PUEH_PTEPE7_MASK                    0x80u
#define PORT_PUEH_PTEPE7_SHIFT                   7
#define PORT_PUEH_PTEPE7_WIDTH                   1
#define PORT_PUEH_PTEPE7(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEH_PTEPE7_SHIFT))&PORT_PUEH_PTEPE7_MASK)
#define PORT_PUEH_PTFPE0_MASK                    0x100u
#define PORT_PUEH_PTFPE0_SHIFT                   8
#define PORT_PUEH_PTFPE0_WIDTH                   1
#define PORT_PUEH_PTFPE0(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEH_PTFPE0_SHIFT))&PORT_PUEH_PTFPE0_MASK)
#define PORT_PUEH_PTFPE1_MASK                    0x200u
#define PORT_PUEH_PTFPE1_SHIFT                   9
#define PORT_PUEH_PTFPE1_WIDTH                   1
#define PORT_PUEH_PTFPE1(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEH_PTFPE1_SHIFT))&PORT_PUEH_PTFPE1_MASK)
#define PORT_PUEH_PTFPE2_MASK                    0x400u
#define PORT_PUEH_PTFPE2_SHIFT                   10
#define PORT_PUEH_PTFPE2_WIDTH                   1
#define PORT_PUEH_PTFPE2(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEH_PTFPE2_SHIFT))&PORT_PUEH_PTFPE2_MASK)
#define PORT_PUEH_PTFPE3_MASK                    0x800u
#define PORT_PUEH_PTFPE3_SHIFT                   11
#define PORT_PUEH_PTFPE3_WIDTH                   1
#define PORT_PUEH_PTFPE3(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEH_PTFPE3_SHIFT))&PORT_PUEH_PTFPE3_MASK)
#define PORT_PUEH_PTFPE4_MASK                    0x1000u
#define PORT_PUEH_PTFPE4_SHIFT                   12
#define PORT_PUEH_PTFPE4_WIDTH                   1
#define PORT_PUEH_PTFPE4(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEH_PTFPE4_SHIFT))&PORT_PUEH_PTFPE4_MASK)
#define PORT_PUEH_PTFPE5_MASK                    0x2000u
#define PORT_PUEH_PTFPE5_SHIFT                   13
#define PORT_PUEH_PTFPE5_WIDTH                   1
#define PORT_PUEH_PTFPE5(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEH_PTFPE5_SHIFT))&PORT_PUEH_PTFPE5_MASK)
#define PORT_PUEH_PTFPE6_MASK                    0x4000u
#define PORT_PUEH_PTFPE6_SHIFT                   14
#define PORT_PUEH_PTFPE6_WIDTH                   1
#define PORT_PUEH_PTFPE6(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEH_PTFPE6_SHIFT))&PORT_PUEH_PTFPE6_MASK)
#define PORT_PUEH_PTFPE7_MASK                    0x8000u
#define PORT_PUEH_PTFPE7_SHIFT                   15
#define PORT_PUEH_PTFPE7_WIDTH                   1
#define PORT_PUEH_PTFPE7(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEH_PTFPE7_SHIFT))&PORT_PUEH_PTFPE7_MASK)
#define PORT_PUEH_PTGPE0_MASK                    0x10000u
#define PORT_PUEH_PTGPE0_SHIFT                   16
#define PORT_PUEH_PTGPE0_WIDTH                   1
#define PORT_PUEH_PTGPE0(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEH_PTGPE0_SHIFT))&PORT_PUEH_PTGPE0_MASK)
#define PORT_PUEH_PTGPE1_MASK                    0x20000u
#define PORT_PUEH_PTGPE1_SHIFT                   17
#define PORT_PUEH_PTGPE1_WIDTH                   1
#define PORT_PUEH_PTGPE1(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEH_PTGPE1_SHIFT))&PORT_PUEH_PTGPE1_MASK)
#define PORT_PUEH_PTGPE2_MASK                    0x40000u
#define PORT_PUEH_PTGPE2_SHIFT                   18
#define PORT_PUEH_PTGPE2_WIDTH                   1
#define PORT_PUEH_PTGPE2(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEH_PTGPE2_SHIFT))&PORT_PUEH_PTGPE2_MASK)
#define PORT_PUEH_PTGPE3_MASK                    0x80000u
#define PORT_PUEH_PTGPE3_SHIFT                   19
#define PORT_PUEH_PTGPE3_WIDTH                   1
#define PORT_PUEH_PTGPE3(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEH_PTGPE3_SHIFT))&PORT_PUEH_PTGPE3_MASK)
#define PORT_PUEH_PTHPE0_MASK                    0x1000000u
#define PORT_PUEH_PTHPE0_SHIFT                   24
#define PORT_PUEH_PTHPE0_WIDTH                   1
#define PORT_PUEH_PTHPE0(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEH_PTHPE0_SHIFT))&PORT_PUEH_PTHPE0_MASK)
#define PORT_PUEH_PTHPE1_MASK                    0x2000000u
#define PORT_PUEH_PTHPE1_SHIFT                   25
#define PORT_PUEH_PTHPE1_WIDTH                   1
#define PORT_PUEH_PTHPE1(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEH_PTHPE1_SHIFT))&PORT_PUEH_PTHPE1_MASK)
#define PORT_PUEH_PTHPE2_MASK                    0x4000000u
#define PORT_PUEH_PTHPE2_SHIFT                   26
#define PORT_PUEH_PTHPE2_WIDTH                   1
#define PORT_PUEH_PTHPE2(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEH_PTHPE2_SHIFT))&PORT_PUEH_PTHPE2_MASK)
#define PORT_PUEH_PTHPE6_MASK                    0x40000000u
#define PORT_PUEH_PTHPE6_SHIFT                   30
#define PORT_PUEH_PTHPE6_WIDTH                   1
#define PORT_PUEH_PTHPE6(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEH_PTHPE6_SHIFT))&PORT_PUEH_PTHPE6_MASK)
#define PORT_PUEH_PTHPE7_MASK                    0x80000000u
#define PORT_PUEH_PTHPE7_SHIFT                   31
#define PORT_PUEH_PTHPE7_WIDTH                   1
#define PORT_PUEH_PTHPE7(x)                      (((uint32_t)(((uint32_t)(x))<<PORT_PUEH_PTHPE7_SHIFT))&PORT_PUEH_PTHPE7_MASK)
/* HDRVE Bit Fields */
#define PORT_HDRVE_PTB4_MASK                     0x1u
#define PORT_HDRVE_PTB4_SHIFT                    0
#define PORT_HDRVE_PTB4_WIDTH                    1
#define PORT_HDRVE_PTB4(x)                       (((uint32_t)(((uint32_t)(x))<<PORT_HDRVE_PTB4_SHIFT))&PORT_HDRVE_PTB4_MASK)
#define PORT_HDRVE_PTB5_MASK                     0x2u
#define PORT_HDRVE_PTB5_SHIFT                    1
#define PORT_HDRVE_PTB5_WIDTH                    1
#define PORT_HDRVE_PTB5(x)                       (((uint32_t)(((uint32_t)(x))<<PORT_HDRVE_PTB5_SHIFT))&PORT_HDRVE_PTB5_MASK)
#define PORT_HDRVE_PTD0_MASK                     0x4u
#define PORT_HDRVE_PTD0_SHIFT                    2
#define PORT_HDRVE_PTD0_WIDTH                    1
#define PORT_HDRVE_PTD0(x)                       (((uint32_t)(((uint32_t)(x))<<PORT_HDRVE_PTD0_SHIFT))&PORT_HDRVE_PTD0_MASK)
#define PORT_HDRVE_PTD1_MASK                     0x8u
#define PORT_HDRVE_PTD1_SHIFT                    3
#define PORT_HDRVE_PTD1_WIDTH                    1
#define PORT_HDRVE_PTD1(x)                       (((uint32_t)(((uint32_t)(x))<<PORT_HDRVE_PTD1_SHIFT))&PORT_HDRVE_PTD1_MASK)
#define PORT_HDRVE_PTE0_MASK                     0x10u
#define PORT_HDRVE_PTE0_SHIFT                    4
#define PORT_HDRVE_PTE0_WIDTH                    1
#define PORT_HDRVE_PTE0(x)                       (((uint32_t)(((uint32_t)(x))<<PORT_HDRVE_PTE0_SHIFT))&PORT_HDRVE_PTE0_MASK)
#define PORT_HDRVE_PTE1_MASK                     0x20u
#define PORT_HDRVE_PTE1_SHIFT                    5
#define PORT_HDRVE_PTE1_WIDTH                    1
#define PORT_HDRVE_PTE1(x)                       (((uint32_t)(((uint32_t)(x))<<PORT_HDRVE_PTE1_SHIFT))&PORT_HDRVE_PTE1_MASK)
#define PORT_HDRVE_PTH0_MASK                     0x40u
#define PORT_HDRVE_PTH0_SHIFT                    6
#define PORT_HDRVE_PTH0_WIDTH                    1
#define PORT_HDRVE_PTH0(x)                       (((uint32_t)(((uint32_t)(x))<<PORT_HDRVE_PTH0_SHIFT))&PORT_HDRVE_PTH0_MASK)
#define PORT_HDRVE_PTH1_MASK                     0x80u
#define PORT_HDRVE_PTH1_SHIFT                    7
#define PORT_HDRVE_PTH1_WIDTH                    1
#define PORT_HDRVE_PTH1(x)                       (((uint32_t)(((uint32_t)(x))<<PORT_HDRVE_PTH1_SHIFT))&PORT_HDRVE_PTH1_MASK)

/*!
 * @}
 */ /* end of group PORT_Register_Masks */


/* PORT - Peripheral instance base addresses */
/** Peripheral PORT base pointer */
#define PORT_BASE_PTR                            ((PORT_MemMapPtr)0x40049000u)
/** Array initializer of PORT peripheral base pointers */
#define PORT_BASE_PTRS                           { PORT_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- PORT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PORT_Register_Accessor_Macros PORT - Register accessor macros
 * @{
 */


/* PORT - Register instance definitions */
/* PORT */
#define PORT_IOFLT                               PORT_IOFLT_REG(PORT_BASE_PTR)
#define PORT_PUEL                                PORT_PUEL_REG(PORT_BASE_PTR)
#define PORT_PUEH                                PORT_PUEH_REG(PORT_BASE_PTR)
#define PORT_HDRVE                               PORT_HDRVE_REG(PORT_BASE_PTR)

/*!
 * @}
 */ /* end of group PORT_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group PORT_Peripheral */


/* ----------------------------------------------------------------------------
   -- ROM
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ROM_Peripheral ROM
 * @{
 */

/** ROM - Peripheral register structure */
typedef struct ROM_MemMap {
  uint32_t ENTRY[1];                               /**< Entry, array offset: 0x0, array step: 0x4 */
  uint32_t TABLEMARK;                              /**< End of Table Marker Register, offset: 0x4 */
  uint8_t RESERVED_0[4036];
  uint32_t SYSACCESS;                              /**< System Access Register, offset: 0xFCC */
  uint32_t PERIPHID4;                              /**< Peripheral ID Register, offset: 0xFD0 */
  uint32_t PERIPHID5;                              /**< Peripheral ID Register, offset: 0xFD4 */
  uint32_t PERIPHID6;                              /**< Peripheral ID Register, offset: 0xFD8 */
  uint32_t PERIPHID7;                              /**< Peripheral ID Register, offset: 0xFDC */
  uint32_t PERIPHID0;                              /**< Peripheral ID Register, offset: 0xFE0 */
  uint32_t PERIPHID1;                              /**< Peripheral ID Register, offset: 0xFE4 */
  uint32_t PERIPHID2;                              /**< Peripheral ID Register, offset: 0xFE8 */
  uint32_t PERIPHID3;                              /**< Peripheral ID Register, offset: 0xFEC */
  uint32_t COMPID[4];                              /**< Component ID Register, array offset: 0xFF0, array step: 0x4 */
} volatile *ROM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- ROM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ROM_Register_Accessor_Macros ROM - Register accessor macros
 * @{
 */


/* ROM - Register accessors */
#define ROM_ENTRY_REG(base,index)                ((base)->ENTRY[index])
#define ROM_ENTRY_COUNT                          1
#define ROM_TABLEMARK_REG(base)                  ((base)->TABLEMARK)
#define ROM_SYSACCESS_REG(base)                  ((base)->SYSACCESS)
#define ROM_PERIPHID4_REG(base)                  ((base)->PERIPHID4)
#define ROM_PERIPHID5_REG(base)                  ((base)->PERIPHID5)
#define ROM_PERIPHID6_REG(base)                  ((base)->PERIPHID6)
#define ROM_PERIPHID7_REG(base)                  ((base)->PERIPHID7)
#define ROM_PERIPHID0_REG(base)                  ((base)->PERIPHID0)
#define ROM_PERIPHID1_REG(base)                  ((base)->PERIPHID1)
#define ROM_PERIPHID2_REG(base)                  ((base)->PERIPHID2)
#define ROM_PERIPHID3_REG(base)                  ((base)->PERIPHID3)
#define ROM_COMPID_REG(base,index)               ((base)->COMPID[index])
#define ROM_COMPID_COUNT                         4

/*!
 * @}
 */ /* end of group ROM_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- ROM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ROM_Register_Masks ROM Register Masks
 * @{
 */

/* ENTRY Bit Fields */
#define ROM_ENTRY_ENTRY_MASK                     0xFFFFFFFFu
#define ROM_ENTRY_ENTRY_SHIFT                    0
#define ROM_ENTRY_ENTRY_WIDTH                    32
#define ROM_ENTRY_ENTRY(x)                       (((uint32_t)(((uint32_t)(x))<<ROM_ENTRY_ENTRY_SHIFT))&ROM_ENTRY_ENTRY_MASK)
/* TABLEMARK Bit Fields */
#define ROM_TABLEMARK_MARK_MASK                  0xFFFFFFFFu
#define ROM_TABLEMARK_MARK_SHIFT                 0
#define ROM_TABLEMARK_MARK_WIDTH                 32
#define ROM_TABLEMARK_MARK(x)                    (((uint32_t)(((uint32_t)(x))<<ROM_TABLEMARK_MARK_SHIFT))&ROM_TABLEMARK_MARK_MASK)
/* SYSACCESS Bit Fields */
#define ROM_SYSACCESS_SYSACCESS_MASK             0xFFFFFFFFu
#define ROM_SYSACCESS_SYSACCESS_SHIFT            0
#define ROM_SYSACCESS_SYSACCESS_WIDTH            32
#define ROM_SYSACCESS_SYSACCESS(x)               (((uint32_t)(((uint32_t)(x))<<ROM_SYSACCESS_SYSACCESS_SHIFT))&ROM_SYSACCESS_SYSACCESS_MASK)
/* PERIPHID4 Bit Fields */
#define ROM_PERIPHID4_PERIPHID_MASK              0xFFFFFFFFu
#define ROM_PERIPHID4_PERIPHID_SHIFT             0
#define ROM_PERIPHID4_PERIPHID_WIDTH             32
#define ROM_PERIPHID4_PERIPHID(x)                (((uint32_t)(((uint32_t)(x))<<ROM_PERIPHID4_PERIPHID_SHIFT))&ROM_PERIPHID4_PERIPHID_MASK)
/* PERIPHID5 Bit Fields */
#define ROM_PERIPHID5_PERIPHID_MASK              0xFFFFFFFFu
#define ROM_PERIPHID5_PERIPHID_SHIFT             0
#define ROM_PERIPHID5_PERIPHID_WIDTH             32
#define ROM_PERIPHID5_PERIPHID(x)                (((uint32_t)(((uint32_t)(x))<<ROM_PERIPHID5_PERIPHID_SHIFT))&ROM_PERIPHID5_PERIPHID_MASK)
/* PERIPHID6 Bit Fields */
#define ROM_PERIPHID6_PERIPHID_MASK              0xFFFFFFFFu
#define ROM_PERIPHID6_PERIPHID_SHIFT             0
#define ROM_PERIPHID6_PERIPHID_WIDTH             32
#define ROM_PERIPHID6_PERIPHID(x)                (((uint32_t)(((uint32_t)(x))<<ROM_PERIPHID6_PERIPHID_SHIFT))&ROM_PERIPHID6_PERIPHID_MASK)
/* PERIPHID7 Bit Fields */
#define ROM_PERIPHID7_PERIPHID_MASK              0xFFFFFFFFu
#define ROM_PERIPHID7_PERIPHID_SHIFT             0
#define ROM_PERIPHID7_PERIPHID_WIDTH             32
#define ROM_PERIPHID7_PERIPHID(x)                (((uint32_t)(((uint32_t)(x))<<ROM_PERIPHID7_PERIPHID_SHIFT))&ROM_PERIPHID7_PERIPHID_MASK)
/* PERIPHID0 Bit Fields */
#define ROM_PERIPHID0_PERIPHID_MASK              0xFFFFFFFFu
#define ROM_PERIPHID0_PERIPHID_SHIFT             0
#define ROM_PERIPHID0_PERIPHID_WIDTH             32
#define ROM_PERIPHID0_PERIPHID(x)                (((uint32_t)(((uint32_t)(x))<<ROM_PERIPHID0_PERIPHID_SHIFT))&ROM_PERIPHID0_PERIPHID_MASK)
/* PERIPHID1 Bit Fields */
#define ROM_PERIPHID1_PERIPHID_MASK              0xFFFFFFFFu
#define ROM_PERIPHID1_PERIPHID_SHIFT             0
#define ROM_PERIPHID1_PERIPHID_WIDTH             32
#define ROM_PERIPHID1_PERIPHID(x)                (((uint32_t)(((uint32_t)(x))<<ROM_PERIPHID1_PERIPHID_SHIFT))&ROM_PERIPHID1_PERIPHID_MASK)
/* PERIPHID2 Bit Fields */
#define ROM_PERIPHID2_PERIPHID_MASK              0xFFFFFFFFu
#define ROM_PERIPHID2_PERIPHID_SHIFT             0
#define ROM_PERIPHID2_PERIPHID_WIDTH             32
#define ROM_PERIPHID2_PERIPHID(x)                (((uint32_t)(((uint32_t)(x))<<ROM_PERIPHID2_PERIPHID_SHIFT))&ROM_PERIPHID2_PERIPHID_MASK)
/* PERIPHID3 Bit Fields */
#define ROM_PERIPHID3_PERIPHID_MASK              0xFFFFFFFFu
#define ROM_PERIPHID3_PERIPHID_SHIFT             0
#define ROM_PERIPHID3_PERIPHID_WIDTH             32
#define ROM_PERIPHID3_PERIPHID(x)                (((uint32_t)(((uint32_t)(x))<<ROM_PERIPHID3_PERIPHID_SHIFT))&ROM_PERIPHID3_PERIPHID_MASK)
/* COMPID Bit Fields */
#define ROM_COMPID_COMPID_MASK                   0xFFFFFFFFu
#define ROM_COMPID_COMPID_SHIFT                  0
#define ROM_COMPID_COMPID_WIDTH                  32
#define ROM_COMPID_COMPID(x)                     (((uint32_t)(((uint32_t)(x))<<ROM_COMPID_COMPID_SHIFT))&ROM_COMPID_COMPID_MASK)

/*!
 * @}
 */ /* end of group ROM_Register_Masks */


/* ROM - Peripheral instance base addresses */
/** Peripheral ROM base pointer */
#define ROM_BASE_PTR                             ((ROM_MemMapPtr)0xF0002000u)
/** Array initializer of ROM peripheral base pointers */
#define ROM_BASE_PTRS                            { ROM_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- ROM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ROM_Register_Accessor_Macros ROM - Register accessor macros
 * @{
 */


/* ROM - Register instance definitions */
/* ROM */
#define ROM_ENTRY0                               ROM_ENTRY_REG(ROM_BASE_PTR,0)
#define ROM_TABLEMARK                            ROM_TABLEMARK_REG(ROM_BASE_PTR)
#define ROM_SYSACCESS                            ROM_SYSACCESS_REG(ROM_BASE_PTR)
#define ROM_PERIPHID4                            ROM_PERIPHID4_REG(ROM_BASE_PTR)
#define ROM_PERIPHID5                            ROM_PERIPHID5_REG(ROM_BASE_PTR)
#define ROM_PERIPHID6                            ROM_PERIPHID6_REG(ROM_BASE_PTR)
#define ROM_PERIPHID7                            ROM_PERIPHID7_REG(ROM_BASE_PTR)
#define ROM_PERIPHID0                            ROM_PERIPHID0_REG(ROM_BASE_PTR)
#define ROM_PERIPHID1                            ROM_PERIPHID1_REG(ROM_BASE_PTR)
#define ROM_PERIPHID2                            ROM_PERIPHID2_REG(ROM_BASE_PTR)
#define ROM_PERIPHID3                            ROM_PERIPHID3_REG(ROM_BASE_PTR)
#define ROM_COMPID0                              ROM_COMPID_REG(ROM_BASE_PTR,0)
#define ROM_COMPID1                              ROM_COMPID_REG(ROM_BASE_PTR,1)
#define ROM_COMPID2                              ROM_COMPID_REG(ROM_BASE_PTR,2)
#define ROM_COMPID3                              ROM_COMPID_REG(ROM_BASE_PTR,3)

/* ROM - Register array accessors */
#define ROM_ENTRY(index)                         ROM_ENTRY_REG(ROM_BASE_PTR,index)
#define ROM_COMPID(index)                        ROM_COMPID_REG(ROM_BASE_PTR,index)

/*!
 * @}
 */ /* end of group ROM_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group ROM_Peripheral */


/* ----------------------------------------------------------------------------
   -- RTC
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTC_Peripheral RTC
 * @{
 */

/** RTC - Peripheral register structure */
typedef struct RTC_MemMap {
  uint32_t SC;                                     /**< RTC Status and Control Register, offset: 0x0 */
  uint32_t MOD;                                    /**< RTC Modulo Register, offset: 0x4 */
  uint32_t CNT;                                    /**< RTC Counter Register, offset: 0x8 */
} volatile *RTC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- RTC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTC_Register_Accessor_Macros RTC - Register accessor macros
 * @{
 */


/* RTC - Register accessors */
#define RTC_SC_REG(base)                         ((base)->SC)
#define RTC_MOD_REG(base)                        ((base)->MOD)
#define RTC_CNT_REG(base)                        ((base)->CNT)

/*!
 * @}
 */ /* end of group RTC_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- RTC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTC_Register_Masks RTC Register Masks
 * @{
 */

/* SC Bit Fields */
#define RTC_SC_RTCO_MASK                         0x10u
#define RTC_SC_RTCO_SHIFT                        4
#define RTC_SC_RTCO_WIDTH                        1
#define RTC_SC_RTCO(x)                           (((uint32_t)(((uint32_t)(x))<<RTC_SC_RTCO_SHIFT))&RTC_SC_RTCO_MASK)
#define RTC_SC_RTIE_MASK                         0x40u
#define RTC_SC_RTIE_SHIFT                        6
#define RTC_SC_RTIE_WIDTH                        1
#define RTC_SC_RTIE(x)                           (((uint32_t)(((uint32_t)(x))<<RTC_SC_RTIE_SHIFT))&RTC_SC_RTIE_MASK)
#define RTC_SC_RTIF_MASK                         0x80u
#define RTC_SC_RTIF_SHIFT                        7
#define RTC_SC_RTIF_WIDTH                        1
#define RTC_SC_RTIF(x)                           (((uint32_t)(((uint32_t)(x))<<RTC_SC_RTIF_SHIFT))&RTC_SC_RTIF_MASK)
#define RTC_SC_RTCPS_MASK                        0x700u
#define RTC_SC_RTCPS_SHIFT                       8
#define RTC_SC_RTCPS_WIDTH                       3
#define RTC_SC_RTCPS(x)                          (((uint32_t)(((uint32_t)(x))<<RTC_SC_RTCPS_SHIFT))&RTC_SC_RTCPS_MASK)
#define RTC_SC_RTCLKS_MASK                       0xC000u
#define RTC_SC_RTCLKS_SHIFT                      14
#define RTC_SC_RTCLKS_WIDTH                      2
#define RTC_SC_RTCLKS(x)                         (((uint32_t)(((uint32_t)(x))<<RTC_SC_RTCLKS_SHIFT))&RTC_SC_RTCLKS_MASK)
/* MOD Bit Fields */
#define RTC_MOD_MOD_MASK                         0xFFFFu
#define RTC_MOD_MOD_SHIFT                        0
#define RTC_MOD_MOD_WIDTH                        16
#define RTC_MOD_MOD(x)                           (((uint32_t)(((uint32_t)(x))<<RTC_MOD_MOD_SHIFT))&RTC_MOD_MOD_MASK)
/* CNT Bit Fields */
#define RTC_CNT_CNT_MASK                         0xFFFFu
#define RTC_CNT_CNT_SHIFT                        0
#define RTC_CNT_CNT_WIDTH                        16
#define RTC_CNT_CNT(x)                           (((uint32_t)(((uint32_t)(x))<<RTC_CNT_CNT_SHIFT))&RTC_CNT_CNT_MASK)

/*!
 * @}
 */ /* end of group RTC_Register_Masks */


/* RTC - Peripheral instance base addresses */
/** Peripheral RTC base pointer */
#define RTC_BASE_PTR                             ((RTC_MemMapPtr)0x4003D000u)
/** Array initializer of RTC peripheral base pointers */
#define RTC_BASE_PTRS                            { RTC_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- RTC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTC_Register_Accessor_Macros RTC - Register accessor macros
 * @{
 */


/* RTC - Register instance definitions */
/* RTC */
#define RTC_SC                                   RTC_SC_REG(RTC_BASE_PTR)
#define RTC_MOD                                  RTC_MOD_REG(RTC_BASE_PTR)
#define RTC_CNT                                  RTC_CNT_REG(RTC_BASE_PTR)

/*!
 * @}
 */ /* end of group RTC_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group RTC_Peripheral */


/* ----------------------------------------------------------------------------
   -- SCB
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SCB_Peripheral SCB
 * @{
 */

/** SCB - Peripheral register structure */
typedef struct SCB_MemMap {
  uint8_t RESERVED_0[8];
  uint32_t ACTLR;                                  /**< Auxiliary Control Register,, offset: 0x8 */
  uint8_t RESERVED_1[3316];
  uint32_t CPUID;                                  /**< CPUID Base Register, offset: 0xD00 */
  uint32_t ICSR;                                   /**< Interrupt Control and State Register, offset: 0xD04 */
  uint32_t VTOR;                                   /**< Vector Table Offset Register, offset: 0xD08 */
  uint32_t AIRCR;                                  /**< Application Interrupt and Reset Control Register, offset: 0xD0C */
  uint32_t SCR;                                    /**< System Control Register, offset: 0xD10 */
  uint32_t CCR;                                    /**< Configuration and Control Register, offset: 0xD14 */
  uint8_t RESERVED_2[4];
  uint32_t SHPR2;                                  /**< System Handler Priority Register 2, offset: 0xD1C */
  uint32_t SHPR3;                                  /**< System Handler Priority Register 3, offset: 0xD20 */
  uint32_t SHCSR;                                  /**< System Handler Control and State Register, offset: 0xD24 */
  uint8_t RESERVED_3[8];
  uint32_t DFSR;                                   /**< Debug Fault Status Register, offset: 0xD30 */
} volatile *SCB_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- SCB - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SCB_Register_Accessor_Macros SCB - Register accessor macros
 * @{
 */


/* SCB - Register accessors */
#define SCB_ACTLR_REG(base)                      ((base)->ACTLR)
#define SCB_CPUID_REG(base)                      ((base)->CPUID)
#define SCB_ICSR_REG(base)                       ((base)->ICSR)
#define SCB_VTOR_REG(base)                       ((base)->VTOR)
#define SCB_AIRCR_REG(base)                      ((base)->AIRCR)
#define SCB_SCR_REG(base)                        ((base)->SCR)
#define SCB_CCR_REG(base)                        ((base)->CCR)
#define SCB_SHPR2_REG(base)                      ((base)->SHPR2)
#define SCB_SHPR3_REG(base)                      ((base)->SHPR3)
#define SCB_SHCSR_REG(base)                      ((base)->SHCSR)
#define SCB_DFSR_REG(base)                       ((base)->DFSR)

/*!
 * @}
 */ /* end of group SCB_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- SCB Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SCB_Register_Masks SCB Register Masks
 * @{
 */

/* CPUID Bit Fields */
#define SCB_CPUID_REVISION_MASK                  0xFu
#define SCB_CPUID_REVISION_SHIFT                 0
#define SCB_CPUID_REVISION_WIDTH                 4
#define SCB_CPUID_REVISION(x)                    (((uint32_t)(((uint32_t)(x))<<SCB_CPUID_REVISION_SHIFT))&SCB_CPUID_REVISION_MASK)
#define SCB_CPUID_PARTNO_MASK                    0xFFF0u
#define SCB_CPUID_PARTNO_SHIFT                   4
#define SCB_CPUID_PARTNO_WIDTH                   12
#define SCB_CPUID_PARTNO(x)                      (((uint32_t)(((uint32_t)(x))<<SCB_CPUID_PARTNO_SHIFT))&SCB_CPUID_PARTNO_MASK)
#define SCB_CPUID_VARIANT_MASK                   0xF00000u
#define SCB_CPUID_VARIANT_SHIFT                  20
#define SCB_CPUID_VARIANT_WIDTH                  4
#define SCB_CPUID_VARIANT(x)                     (((uint32_t)(((uint32_t)(x))<<SCB_CPUID_VARIANT_SHIFT))&SCB_CPUID_VARIANT_MASK)
#define SCB_CPUID_IMPLEMENTER_MASK               0xFF000000u
#define SCB_CPUID_IMPLEMENTER_SHIFT              24
#define SCB_CPUID_IMPLEMENTER_WIDTH              8
#define SCB_CPUID_IMPLEMENTER(x)                 (((uint32_t)(((uint32_t)(x))<<SCB_CPUID_IMPLEMENTER_SHIFT))&SCB_CPUID_IMPLEMENTER_MASK)
/* ICSR Bit Fields */
#define SCB_ICSR_VECTPENDING_MASK                0x3F000u
#define SCB_ICSR_VECTPENDING_SHIFT               12
#define SCB_ICSR_VECTPENDING_WIDTH               6
#define SCB_ICSR_VECTPENDING(x)                  (((uint32_t)(((uint32_t)(x))<<SCB_ICSR_VECTPENDING_SHIFT))&SCB_ICSR_VECTPENDING_MASK)
#define SCB_ICSR_PENDSTCLR_MASK                  0x2000000u
#define SCB_ICSR_PENDSTCLR_SHIFT                 25
#define SCB_ICSR_PENDSTCLR_WIDTH                 1
#define SCB_ICSR_PENDSTCLR(x)                    (((uint32_t)(((uint32_t)(x))<<SCB_ICSR_PENDSTCLR_SHIFT))&SCB_ICSR_PENDSTCLR_MASK)
#define SCB_ICSR_PENDSTSET_MASK                  0x4000000u
#define SCB_ICSR_PENDSTSET_SHIFT                 26
#define SCB_ICSR_PENDSTSET_WIDTH                 1
#define SCB_ICSR_PENDSTSET(x)                    (((uint32_t)(((uint32_t)(x))<<SCB_ICSR_PENDSTSET_SHIFT))&SCB_ICSR_PENDSTSET_MASK)
#define SCB_ICSR_PENDSVCLR_MASK                  0x8000000u
#define SCB_ICSR_PENDSVCLR_SHIFT                 27
#define SCB_ICSR_PENDSVCLR_WIDTH                 1
#define SCB_ICSR_PENDSVCLR(x)                    (((uint32_t)(((uint32_t)(x))<<SCB_ICSR_PENDSVCLR_SHIFT))&SCB_ICSR_PENDSVCLR_MASK)
#define SCB_ICSR_PENDSVSET_MASK                  0x10000000u
#define SCB_ICSR_PENDSVSET_SHIFT                 28
#define SCB_ICSR_PENDSVSET_WIDTH                 1
#define SCB_ICSR_PENDSVSET(x)                    (((uint32_t)(((uint32_t)(x))<<SCB_ICSR_PENDSVSET_SHIFT))&SCB_ICSR_PENDSVSET_MASK)
#define SCB_ICSR_NMIPENDSET_MASK                 0x80000000u
#define SCB_ICSR_NMIPENDSET_SHIFT                31
#define SCB_ICSR_NMIPENDSET_WIDTH                1
#define SCB_ICSR_NMIPENDSET(x)                   (((uint32_t)(((uint32_t)(x))<<SCB_ICSR_NMIPENDSET_SHIFT))&SCB_ICSR_NMIPENDSET_MASK)
/* VTOR Bit Fields */
#define SCB_VTOR_TBLOFF_MASK                     0xFFFFFF80u
#define SCB_VTOR_TBLOFF_SHIFT                    7
#define SCB_VTOR_TBLOFF_WIDTH                    25
#define SCB_VTOR_TBLOFF(x)                       (((uint32_t)(((uint32_t)(x))<<SCB_VTOR_TBLOFF_SHIFT))&SCB_VTOR_TBLOFF_MASK)
/* AIRCR Bit Fields */
#define SCB_AIRCR_VECTCLRACTIVE_MASK             0x2u
#define SCB_AIRCR_VECTCLRACTIVE_SHIFT            1
#define SCB_AIRCR_VECTCLRACTIVE_WIDTH            1
#define SCB_AIRCR_VECTCLRACTIVE(x)               (((uint32_t)(((uint32_t)(x))<<SCB_AIRCR_VECTCLRACTIVE_SHIFT))&SCB_AIRCR_VECTCLRACTIVE_MASK)
#define SCB_AIRCR_SYSRESETREQ_MASK               0x4u
#define SCB_AIRCR_SYSRESETREQ_SHIFT              2
#define SCB_AIRCR_SYSRESETREQ_WIDTH              1
#define SCB_AIRCR_SYSRESETREQ(x)                 (((uint32_t)(((uint32_t)(x))<<SCB_AIRCR_SYSRESETREQ_SHIFT))&SCB_AIRCR_SYSRESETREQ_MASK)
#define SCB_AIRCR_ENDIANNESS_MASK                0x8000u
#define SCB_AIRCR_ENDIANNESS_SHIFT               15
#define SCB_AIRCR_ENDIANNESS_WIDTH               1
#define SCB_AIRCR_ENDIANNESS(x)                  (((uint32_t)(((uint32_t)(x))<<SCB_AIRCR_ENDIANNESS_SHIFT))&SCB_AIRCR_ENDIANNESS_MASK)
#define SCB_AIRCR_VECTKEY_MASK                   0xFFFF0000u
#define SCB_AIRCR_VECTKEY_SHIFT                  16
#define SCB_AIRCR_VECTKEY_WIDTH                  16
#define SCB_AIRCR_VECTKEY(x)                     (((uint32_t)(((uint32_t)(x))<<SCB_AIRCR_VECTKEY_SHIFT))&SCB_AIRCR_VECTKEY_MASK)
/* SCR Bit Fields */
#define SCB_SCR_SLEEPONEXIT_MASK                 0x2u
#define SCB_SCR_SLEEPONEXIT_SHIFT                1
#define SCB_SCR_SLEEPONEXIT_WIDTH                1
#define SCB_SCR_SLEEPONEXIT(x)                   (((uint32_t)(((uint32_t)(x))<<SCB_SCR_SLEEPONEXIT_SHIFT))&SCB_SCR_SLEEPONEXIT_MASK)
#define SCB_SCR_SLEEPDEEP_MASK                   0x4u
#define SCB_SCR_SLEEPDEEP_SHIFT                  2
#define SCB_SCR_SLEEPDEEP_WIDTH                  1
#define SCB_SCR_SLEEPDEEP(x)                     (((uint32_t)(((uint32_t)(x))<<SCB_SCR_SLEEPDEEP_SHIFT))&SCB_SCR_SLEEPDEEP_MASK)
#define SCB_SCR_SEVONPEND_MASK                   0x10u
#define SCB_SCR_SEVONPEND_SHIFT                  4
#define SCB_SCR_SEVONPEND_WIDTH                  1
#define SCB_SCR_SEVONPEND(x)                     (((uint32_t)(((uint32_t)(x))<<SCB_SCR_SEVONPEND_SHIFT))&SCB_SCR_SEVONPEND_MASK)
/* CCR Bit Fields */
#define SCB_CCR_UNALIGN_TRP_MASK                 0x8u
#define SCB_CCR_UNALIGN_TRP_SHIFT                3
#define SCB_CCR_UNALIGN_TRP_WIDTH                1
#define SCB_CCR_UNALIGN_TRP(x)                   (((uint32_t)(((uint32_t)(x))<<SCB_CCR_UNALIGN_TRP_SHIFT))&SCB_CCR_UNALIGN_TRP_MASK)
#define SCB_CCR_STKALIGN_MASK                    0x200u
#define SCB_CCR_STKALIGN_SHIFT                   9
#define SCB_CCR_STKALIGN_WIDTH                   1
#define SCB_CCR_STKALIGN(x)                      (((uint32_t)(((uint32_t)(x))<<SCB_CCR_STKALIGN_SHIFT))&SCB_CCR_STKALIGN_MASK)
/* SHPR2 Bit Fields */
#define SCB_SHPR2_PRI_11_MASK                    0xFF000000u
#define SCB_SHPR2_PRI_11_SHIFT                   24
#define SCB_SHPR2_PRI_11_WIDTH                   8
#define SCB_SHPR2_PRI_11(x)                      (((uint32_t)(((uint32_t)(x))<<SCB_SHPR2_PRI_11_SHIFT))&SCB_SHPR2_PRI_11_MASK)
/* SHPR3 Bit Fields */
#define SCB_SHPR3_PRI_14_MASK                    0xFF0000u
#define SCB_SHPR3_PRI_14_SHIFT                   16
#define SCB_SHPR3_PRI_14_WIDTH                   8
#define SCB_SHPR3_PRI_14(x)                      (((uint32_t)(((uint32_t)(x))<<SCB_SHPR3_PRI_14_SHIFT))&SCB_SHPR3_PRI_14_MASK)
#define SCB_SHPR3_PRI_15_MASK                    0xFF000000u
#define SCB_SHPR3_PRI_15_SHIFT                   24
#define SCB_SHPR3_PRI_15_WIDTH                   8
#define SCB_SHPR3_PRI_15(x)                      (((uint32_t)(((uint32_t)(x))<<SCB_SHPR3_PRI_15_SHIFT))&SCB_SHPR3_PRI_15_MASK)
/* SHCSR Bit Fields */
#define SCB_SHCSR_SVCALLPENDED_MASK              0x8000u
#define SCB_SHCSR_SVCALLPENDED_SHIFT             15
#define SCB_SHCSR_SVCALLPENDED_WIDTH             1
#define SCB_SHCSR_SVCALLPENDED(x)                (((uint32_t)(((uint32_t)(x))<<SCB_SHCSR_SVCALLPENDED_SHIFT))&SCB_SHCSR_SVCALLPENDED_MASK)
/* DFSR Bit Fields */
#define SCB_DFSR_HALTED_MASK                     0x1u
#define SCB_DFSR_HALTED_SHIFT                    0
#define SCB_DFSR_HALTED_WIDTH                    1
#define SCB_DFSR_HALTED(x)                       (((uint32_t)(((uint32_t)(x))<<SCB_DFSR_HALTED_SHIFT))&SCB_DFSR_HALTED_MASK)
#define SCB_DFSR_BKPT_MASK                       0x2u
#define SCB_DFSR_BKPT_SHIFT                      1
#define SCB_DFSR_BKPT_WIDTH                      1
#define SCB_DFSR_BKPT(x)                         (((uint32_t)(((uint32_t)(x))<<SCB_DFSR_BKPT_SHIFT))&SCB_DFSR_BKPT_MASK)
#define SCB_DFSR_DWTTRAP_MASK                    0x4u
#define SCB_DFSR_DWTTRAP_SHIFT                   2
#define SCB_DFSR_DWTTRAP_WIDTH                   1
#define SCB_DFSR_DWTTRAP(x)                      (((uint32_t)(((uint32_t)(x))<<SCB_DFSR_DWTTRAP_SHIFT))&SCB_DFSR_DWTTRAP_MASK)
#define SCB_DFSR_VCATCH_MASK                     0x8u
#define SCB_DFSR_VCATCH_SHIFT                    3
#define SCB_DFSR_VCATCH_WIDTH                    1
#define SCB_DFSR_VCATCH(x)                       (((uint32_t)(((uint32_t)(x))<<SCB_DFSR_VCATCH_SHIFT))&SCB_DFSR_VCATCH_MASK)
#define SCB_DFSR_EXTERNAL_MASK                   0x10u
#define SCB_DFSR_EXTERNAL_SHIFT                  4
#define SCB_DFSR_EXTERNAL_WIDTH                  1
#define SCB_DFSR_EXTERNAL(x)                     (((uint32_t)(((uint32_t)(x))<<SCB_DFSR_EXTERNAL_SHIFT))&SCB_DFSR_EXTERNAL_MASK)

/*!
 * @}
 */ /* end of group SCB_Register_Masks */


/* SCB - Peripheral instance base addresses */
/** Peripheral SystemControl base pointer */
#define SystemControl_BASE_PTR                   ((SCB_MemMapPtr)0xE000E000u)
/** Array initializer of SCB peripheral base pointers */
#define SCB_BASE_PTRS                            { SystemControl_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- SCB - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SCB_Register_Accessor_Macros SCB - Register accessor macros
 * @{
 */


/* SCB - Register instance definitions */
/* SystemControl */
#define SCB_ACTLR                                SCB_ACTLR_REG(SystemControl_BASE_PTR)
#define SCB_CPUID                                SCB_CPUID_REG(SystemControl_BASE_PTR)
#define SCB_ICSR                                 SCB_ICSR_REG(SystemControl_BASE_PTR)
#define SCB_VTOR                                 SCB_VTOR_REG(SystemControl_BASE_PTR)
#define SCB_AIRCR                                SCB_AIRCR_REG(SystemControl_BASE_PTR)
#define SCB_SCR                                  SCB_SCR_REG(SystemControl_BASE_PTR)
#define SCB_CCR                                  SCB_CCR_REG(SystemControl_BASE_PTR)
#define SCB_SHPR2                                SCB_SHPR2_REG(SystemControl_BASE_PTR)
#define SCB_SHPR3                                SCB_SHPR3_REG(SystemControl_BASE_PTR)
#define SCB_SHCSR                                SCB_SHCSR_REG(SystemControl_BASE_PTR)
#define SCB_DFSR                                 SCB_DFSR_REG(SystemControl_BASE_PTR)

/*!
 * @}
 */ /* end of group SCB_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group SCB_Peripheral */


/* ----------------------------------------------------------------------------
   -- SIM
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SIM_Peripheral SIM
 * @{
 */

/** SIM - Peripheral register structure */
typedef struct SIM_MemMap {
  uint32_t SRSID;                                  /**< System Reset Status and ID Register, offset: 0x0 */
  uint32_t SOPT;                                   /**< System Options Register, offset: 0x4 */
  uint32_t PINSEL;                                 /**< Pin Selection Register, offset: 0x8 */
  uint32_t SCGC;                                   /**< System Clock Gating Control Register, offset: 0xC */
  uint32_t UUIDL;                                  /**< Universally Unique Identifier Low Register, offset: 0x10 */
  uint32_t UUIDH;                                  /**< Universally Unique Identifier High Register, offset: 0x14 */
  uint32_t BUSDIV;                                 /**< BUS Clock Divider Register, offset: 0x18 */
} volatile *SIM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- SIM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SIM_Register_Accessor_Macros SIM - Register accessor macros
 * @{
 */


/* SIM - Register accessors */
#define SIM_SRSID_REG(base)                      ((base)->SRSID)
#define SIM_SOPT_REG(base)                       ((base)->SOPT)
#define SIM_PINSEL_REG(base)                     ((base)->PINSEL)
#define SIM_SCGC_REG(base)                       ((base)->SCGC)
#define SIM_UUIDL_REG(base)                      ((base)->UUIDL)
#define SIM_UUIDH_REG(base)                      ((base)->UUIDH)
#define SIM_BUSDIV_REG(base)                     ((base)->BUSDIV)

/*!
 * @}
 */ /* end of group SIM_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- SIM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SIM_Register_Masks SIM Register Masks
 * @{
 */

/* SRSID Bit Fields */
#define SIM_SRSID_LVD_MASK                       0x2u
#define SIM_SRSID_LVD_SHIFT                      1
#define SIM_SRSID_LVD_WIDTH                      1
#define SIM_SRSID_LVD(x)                         (((uint32_t)(((uint32_t)(x))<<SIM_SRSID_LVD_SHIFT))&SIM_SRSID_LVD_MASK)
#define SIM_SRSID_LOC_MASK                       0x4u
#define SIM_SRSID_LOC_SHIFT                      2
#define SIM_SRSID_LOC_WIDTH                      1
#define SIM_SRSID_LOC(x)                         (((uint32_t)(((uint32_t)(x))<<SIM_SRSID_LOC_SHIFT))&SIM_SRSID_LOC_MASK)
#define SIM_SRSID_WDOG_MASK                      0x20u
#define SIM_SRSID_WDOG_SHIFT                     5
#define SIM_SRSID_WDOG_WIDTH                     1
#define SIM_SRSID_WDOG(x)                        (((uint32_t)(((uint32_t)(x))<<SIM_SRSID_WDOG_SHIFT))&SIM_SRSID_WDOG_MASK)
#define SIM_SRSID_PIN_MASK                       0x40u
#define SIM_SRSID_PIN_SHIFT                      6
#define SIM_SRSID_PIN_WIDTH                      1
#define SIM_SRSID_PIN(x)                         (((uint32_t)(((uint32_t)(x))<<SIM_SRSID_PIN_SHIFT))&SIM_SRSID_PIN_MASK)
#define SIM_SRSID_POR_MASK                       0x80u
#define SIM_SRSID_POR_SHIFT                      7
#define SIM_SRSID_POR_WIDTH                      1
#define SIM_SRSID_POR(x)                         (((uint32_t)(((uint32_t)(x))<<SIM_SRSID_POR_SHIFT))&SIM_SRSID_POR_MASK)
#define SIM_SRSID_LOCKUP_MASK                    0x200u
#define SIM_SRSID_LOCKUP_SHIFT                   9
#define SIM_SRSID_LOCKUP_WIDTH                   1
#define SIM_SRSID_LOCKUP(x)                      (((uint32_t)(((uint32_t)(x))<<SIM_SRSID_LOCKUP_SHIFT))&SIM_SRSID_LOCKUP_MASK)
#define SIM_SRSID_SW_MASK                        0x400u
#define SIM_SRSID_SW_SHIFT                       10
#define SIM_SRSID_SW_WIDTH                       1
#define SIM_SRSID_SW(x)                          (((uint32_t)(((uint32_t)(x))<<SIM_SRSID_SW_SHIFT))&SIM_SRSID_SW_MASK)
#define SIM_SRSID_MDMAP_MASK                     0x800u
#define SIM_SRSID_MDMAP_SHIFT                    11
#define SIM_SRSID_MDMAP_WIDTH                    1
#define SIM_SRSID_MDMAP(x)                       (((uint32_t)(((uint32_t)(x))<<SIM_SRSID_MDMAP_SHIFT))&SIM_SRSID_MDMAP_MASK)
#define SIM_SRSID_SACKERR_MASK                   0x2000u
#define SIM_SRSID_SACKERR_SHIFT                  13
#define SIM_SRSID_SACKERR_WIDTH                  1
#define SIM_SRSID_SACKERR(x)                     (((uint32_t)(((uint32_t)(x))<<SIM_SRSID_SACKERR_SHIFT))&SIM_SRSID_SACKERR_MASK)
#define SIM_SRSID_PINID_MASK                     0xF0000u
#define SIM_SRSID_PINID_SHIFT                    16
#define SIM_SRSID_PINID_WIDTH                    4
#define SIM_SRSID_PINID(x)                       (((uint32_t)(((uint32_t)(x))<<SIM_SRSID_PINID_SHIFT))&SIM_SRSID_PINID_MASK)
#define SIM_SRSID_RevID_MASK                     0xF00000u
#define SIM_SRSID_RevID_SHIFT                    20
#define SIM_SRSID_RevID_WIDTH                    4
#define SIM_SRSID_RevID(x)                       (((uint32_t)(((uint32_t)(x))<<SIM_SRSID_RevID_SHIFT))&SIM_SRSID_RevID_MASK)
#define SIM_SRSID_SUBFAMID_MASK                  0xF000000u
#define SIM_SRSID_SUBFAMID_SHIFT                 24
#define SIM_SRSID_SUBFAMID_WIDTH                 4
#define SIM_SRSID_SUBFAMID(x)                    (((uint32_t)(((uint32_t)(x))<<SIM_SRSID_SUBFAMID_SHIFT))&SIM_SRSID_SUBFAMID_MASK)
#define SIM_SRSID_FAMID_MASK                     0xF0000000u
#define SIM_SRSID_FAMID_SHIFT                    28
#define SIM_SRSID_FAMID_WIDTH                    4
#define SIM_SRSID_FAMID(x)                       (((uint32_t)(((uint32_t)(x))<<SIM_SRSID_FAMID_SHIFT))&SIM_SRSID_FAMID_MASK)
/* SOPT Bit Fields */
#define SIM_SOPT_NMIE_MASK                       0x2u
#define SIM_SOPT_NMIE_SHIFT                      1
#define SIM_SOPT_NMIE_WIDTH                      1
#define SIM_SOPT_NMIE(x)                         (((uint32_t)(((uint32_t)(x))<<SIM_SOPT_NMIE_SHIFT))&SIM_SOPT_NMIE_MASK)
#define SIM_SOPT_RSTPE_MASK                      0x4u
#define SIM_SOPT_RSTPE_SHIFT                     2
#define SIM_SOPT_RSTPE_WIDTH                     1
#define SIM_SOPT_RSTPE(x)                        (((uint32_t)(((uint32_t)(x))<<SIM_SOPT_RSTPE_SHIFT))&SIM_SOPT_RSTPE_MASK)
#define SIM_SOPT_SWDE_MASK                       0x8u
#define SIM_SOPT_SWDE_SHIFT                      3
#define SIM_SOPT_SWDE_WIDTH                      1
#define SIM_SOPT_SWDE(x)                         (((uint32_t)(((uint32_t)(x))<<SIM_SOPT_SWDE_SHIFT))&SIM_SOPT_SWDE_MASK)
#define SIM_SOPT_ADHWT_MASK                      0x300u
#define SIM_SOPT_ADHWT_SHIFT                     8
#define SIM_SOPT_ADHWT_WIDTH                     2
#define SIM_SOPT_ADHWT(x)                        (((uint32_t)(((uint32_t)(x))<<SIM_SOPT_ADHWT_SHIFT))&SIM_SOPT_ADHWT_MASK)
#define SIM_SOPT_RTCC_MASK                       0x400u
#define SIM_SOPT_RTCC_SHIFT                      10
#define SIM_SOPT_RTCC_WIDTH                      1
#define SIM_SOPT_RTCC(x)                         (((uint32_t)(((uint32_t)(x))<<SIM_SOPT_RTCC_SHIFT))&SIM_SOPT_RTCC_MASK)
#define SIM_SOPT_ACIC_MASK                       0x800u
#define SIM_SOPT_ACIC_SHIFT                      11
#define SIM_SOPT_ACIC_WIDTH                      1
#define SIM_SOPT_ACIC(x)                         (((uint32_t)(((uint32_t)(x))<<SIM_SOPT_ACIC_SHIFT))&SIM_SOPT_ACIC_MASK)
#define SIM_SOPT_RXDCE_MASK                      0x1000u
#define SIM_SOPT_RXDCE_SHIFT                     12
#define SIM_SOPT_RXDCE_WIDTH                     1
#define SIM_SOPT_RXDCE(x)                        (((uint32_t)(((uint32_t)(x))<<SIM_SOPT_RXDCE_SHIFT))&SIM_SOPT_RXDCE_MASK)
#define SIM_SOPT_RXDFE_MASK                      0x2000u
#define SIM_SOPT_RXDFE_SHIFT                     13
#define SIM_SOPT_RXDFE_WIDTH                     1
#define SIM_SOPT_RXDFE(x)                        (((uint32_t)(((uint32_t)(x))<<SIM_SOPT_RXDFE_SHIFT))&SIM_SOPT_RXDFE_MASK)
#define SIM_SOPT_FTMSYNC_MASK                    0x4000u
#define SIM_SOPT_FTMSYNC_SHIFT                   14
#define SIM_SOPT_FTMSYNC_WIDTH                   1
#define SIM_SOPT_FTMSYNC(x)                      (((uint32_t)(((uint32_t)(x))<<SIM_SOPT_FTMSYNC_SHIFT))&SIM_SOPT_FTMSYNC_MASK)
#define SIM_SOPT_TXDME_MASK                      0x8000u
#define SIM_SOPT_TXDME_SHIFT                     15
#define SIM_SOPT_TXDME_WIDTH                     1
#define SIM_SOPT_TXDME(x)                        (((uint32_t)(((uint32_t)(x))<<SIM_SOPT_TXDME_SHIFT))&SIM_SOPT_TXDME_MASK)
#define SIM_SOPT_BUSREF_MASK                     0x70000u
#define SIM_SOPT_BUSREF_SHIFT                    16
#define SIM_SOPT_BUSREF_WIDTH                    3
#define SIM_SOPT_BUSREF(x)                       (((uint32_t)(((uint32_t)(x))<<SIM_SOPT_BUSREF_SHIFT))&SIM_SOPT_BUSREF_MASK)
#define SIM_SOPT_CLKOE_MASK                      0x80000u
#define SIM_SOPT_CLKOE_SHIFT                     19
#define SIM_SOPT_CLKOE_WIDTH                     1
#define SIM_SOPT_CLKOE(x)                        (((uint32_t)(((uint32_t)(x))<<SIM_SOPT_CLKOE_SHIFT))&SIM_SOPT_CLKOE_MASK)
#define SIM_SOPT_DLYACT_MASK                     0x800000u
#define SIM_SOPT_DLYACT_SHIFT                    23
#define SIM_SOPT_DLYACT_WIDTH                    1
#define SIM_SOPT_DLYACT(x)                       (((uint32_t)(((uint32_t)(x))<<SIM_SOPT_DLYACT_SHIFT))&SIM_SOPT_DLYACT_MASK)
#define SIM_SOPT_DELAY_MASK                      0xFF000000u
#define SIM_SOPT_DELAY_SHIFT                     24
#define SIM_SOPT_DELAY_WIDTH                     8
#define SIM_SOPT_DELAY(x)                        (((uint32_t)(((uint32_t)(x))<<SIM_SOPT_DELAY_SHIFT))&SIM_SOPT_DELAY_MASK)
/* PINSEL Bit Fields */
#define SIM_PINSEL_RTCPS_MASK                    0x10u
#define SIM_PINSEL_RTCPS_SHIFT                   4
#define SIM_PINSEL_RTCPS_WIDTH                   1
#define SIM_PINSEL_RTCPS(x)                      (((uint32_t)(((uint32_t)(x))<<SIM_PINSEL_RTCPS_SHIFT))&SIM_PINSEL_RTCPS_MASK)
#define SIM_PINSEL_I2C0PS_MASK                   0x20u
#define SIM_PINSEL_I2C0PS_SHIFT                  5
#define SIM_PINSEL_I2C0PS_WIDTH                  1
#define SIM_PINSEL_I2C0PS(x)                     (((uint32_t)(((uint32_t)(x))<<SIM_PINSEL_I2C0PS_SHIFT))&SIM_PINSEL_I2C0PS_MASK)
#define SIM_PINSEL_SPI0PS_MASK                   0x40u
#define SIM_PINSEL_SPI0PS_SHIFT                  6
#define SIM_PINSEL_SPI0PS_WIDTH                  1
#define SIM_PINSEL_SPI0PS(x)                     (((uint32_t)(((uint32_t)(x))<<SIM_PINSEL_SPI0PS_SHIFT))&SIM_PINSEL_SPI0PS_MASK)
#define SIM_PINSEL_UART0PS_MASK                  0x80u
#define SIM_PINSEL_UART0PS_SHIFT                 7
#define SIM_PINSEL_UART0PS_WIDTH                 1
#define SIM_PINSEL_UART0PS(x)                    (((uint32_t)(((uint32_t)(x))<<SIM_PINSEL_UART0PS_SHIFT))&SIM_PINSEL_UART0PS_MASK)
#define SIM_PINSEL_FTM0PS0_MASK                  0x100u
#define SIM_PINSEL_FTM0PS0_SHIFT                 8
#define SIM_PINSEL_FTM0PS0_WIDTH                 1
#define SIM_PINSEL_FTM0PS0(x)                    (((uint32_t)(((uint32_t)(x))<<SIM_PINSEL_FTM0PS0_SHIFT))&SIM_PINSEL_FTM0PS0_MASK)
#define SIM_PINSEL_FTM0PS1_MASK                  0x200u
#define SIM_PINSEL_FTM0PS1_SHIFT                 9
#define SIM_PINSEL_FTM0PS1_WIDTH                 1
#define SIM_PINSEL_FTM0PS1(x)                    (((uint32_t)(((uint32_t)(x))<<SIM_PINSEL_FTM0PS1_SHIFT))&SIM_PINSEL_FTM0PS1_MASK)
#define SIM_PINSEL_FTM1PS0_MASK                  0x400u
#define SIM_PINSEL_FTM1PS0_SHIFT                 10
#define SIM_PINSEL_FTM1PS0_WIDTH                 1
#define SIM_PINSEL_FTM1PS0(x)                    (((uint32_t)(((uint32_t)(x))<<SIM_PINSEL_FTM1PS0_SHIFT))&SIM_PINSEL_FTM1PS0_MASK)
#define SIM_PINSEL_FTM1PS1_MASK                  0x800u
#define SIM_PINSEL_FTM1PS1_SHIFT                 11
#define SIM_PINSEL_FTM1PS1_WIDTH                 1
#define SIM_PINSEL_FTM1PS1(x)                    (((uint32_t)(((uint32_t)(x))<<SIM_PINSEL_FTM1PS1_SHIFT))&SIM_PINSEL_FTM1PS1_MASK)
#define SIM_PINSEL_FTM2PS0_MASK                  0x1000u
#define SIM_PINSEL_FTM2PS0_SHIFT                 12
#define SIM_PINSEL_FTM2PS0_WIDTH                 1
#define SIM_PINSEL_FTM2PS0(x)                    (((uint32_t)(((uint32_t)(x))<<SIM_PINSEL_FTM2PS0_SHIFT))&SIM_PINSEL_FTM2PS0_MASK)
#define SIM_PINSEL_FTM2PS1_MASK                  0x2000u
#define SIM_PINSEL_FTM2PS1_SHIFT                 13
#define SIM_PINSEL_FTM2PS1_WIDTH                 1
#define SIM_PINSEL_FTM2PS1(x)                    (((uint32_t)(((uint32_t)(x))<<SIM_PINSEL_FTM2PS1_SHIFT))&SIM_PINSEL_FTM2PS1_MASK)
#define SIM_PINSEL_FTM2PS2_MASK                  0x4000u
#define SIM_PINSEL_FTM2PS2_SHIFT                 14
#define SIM_PINSEL_FTM2PS2_WIDTH                 1
#define SIM_PINSEL_FTM2PS2(x)                    (((uint32_t)(((uint32_t)(x))<<SIM_PINSEL_FTM2PS2_SHIFT))&SIM_PINSEL_FTM2PS2_MASK)
#define SIM_PINSEL_FTM2PS3_MASK                  0x8000u
#define SIM_PINSEL_FTM2PS3_SHIFT                 15
#define SIM_PINSEL_FTM2PS3_WIDTH                 1
#define SIM_PINSEL_FTM2PS3(x)                    (((uint32_t)(((uint32_t)(x))<<SIM_PINSEL_FTM2PS3_SHIFT))&SIM_PINSEL_FTM2PS3_MASK)
/* SCGC Bit Fields */
#define SIM_SCGC_RTC_MASK                        0x1u
#define SIM_SCGC_RTC_SHIFT                       0
#define SIM_SCGC_RTC_WIDTH                       1
#define SIM_SCGC_RTC(x)                          (((uint32_t)(((uint32_t)(x))<<SIM_SCGC_RTC_SHIFT))&SIM_SCGC_RTC_MASK)
#define SIM_SCGC_PIT_MASK                        0x2u
#define SIM_SCGC_PIT_SHIFT                       1
#define SIM_SCGC_PIT_WIDTH                       1
#define SIM_SCGC_PIT(x)                          (((uint32_t)(((uint32_t)(x))<<SIM_SCGC_PIT_SHIFT))&SIM_SCGC_PIT_MASK)
#define SIM_SCGC_FTM0_MASK                       0x20u
#define SIM_SCGC_FTM0_SHIFT                      5
#define SIM_SCGC_FTM0_WIDTH                      1
#define SIM_SCGC_FTM0(x)                         (((uint32_t)(((uint32_t)(x))<<SIM_SCGC_FTM0_SHIFT))&SIM_SCGC_FTM0_MASK)
#define SIM_SCGC_FTM1_MASK                       0x40u
#define SIM_SCGC_FTM1_SHIFT                      6
#define SIM_SCGC_FTM1_WIDTH                      1
#define SIM_SCGC_FTM1(x)                         (((uint32_t)(((uint32_t)(x))<<SIM_SCGC_FTM1_SHIFT))&SIM_SCGC_FTM1_MASK)
#define SIM_SCGC_FTM2_MASK                       0x80u
#define SIM_SCGC_FTM2_SHIFT                      7
#define SIM_SCGC_FTM2_WIDTH                      1
#define SIM_SCGC_FTM2(x)                         (((uint32_t)(((uint32_t)(x))<<SIM_SCGC_FTM2_SHIFT))&SIM_SCGC_FTM2_MASK)
#define SIM_SCGC_CRC_MASK                        0x400u
#define SIM_SCGC_CRC_SHIFT                       10
#define SIM_SCGC_CRC_WIDTH                       1
#define SIM_SCGC_CRC(x)                          (((uint32_t)(((uint32_t)(x))<<SIM_SCGC_CRC_SHIFT))&SIM_SCGC_CRC_MASK)
#define SIM_SCGC_FLASH_MASK                      0x1000u
#define SIM_SCGC_FLASH_SHIFT                     12
#define SIM_SCGC_FLASH_WIDTH                     1
#define SIM_SCGC_FLASH(x)                        (((uint32_t)(((uint32_t)(x))<<SIM_SCGC_FLASH_SHIFT))&SIM_SCGC_FLASH_MASK)
#define SIM_SCGC_SWD_MASK                        0x2000u
#define SIM_SCGC_SWD_SHIFT                       13
#define SIM_SCGC_SWD_WIDTH                       1
#define SIM_SCGC_SWD(x)                          (((uint32_t)(((uint32_t)(x))<<SIM_SCGC_SWD_SHIFT))&SIM_SCGC_SWD_MASK)
#define SIM_SCGC_I2C_MASK                        0x20000u
#define SIM_SCGC_I2C_SHIFT                       17
#define SIM_SCGC_I2C_WIDTH                       1
#define SIM_SCGC_I2C(x)                          (((uint32_t)(((uint32_t)(x))<<SIM_SCGC_I2C_SHIFT))&SIM_SCGC_I2C_MASK)
#define SIM_SCGC_SPI0_MASK                       0x40000u
#define SIM_SCGC_SPI0_SHIFT                      18
#define SIM_SCGC_SPI0_WIDTH                      1
#define SIM_SCGC_SPI0(x)                         (((uint32_t)(((uint32_t)(x))<<SIM_SCGC_SPI0_SHIFT))&SIM_SCGC_SPI0_MASK)
#define SIM_SCGC_SPI1_MASK                       0x80000u
#define SIM_SCGC_SPI1_SHIFT                      19
#define SIM_SCGC_SPI1_WIDTH                      1
#define SIM_SCGC_SPI1(x)                         (((uint32_t)(((uint32_t)(x))<<SIM_SCGC_SPI1_SHIFT))&SIM_SCGC_SPI1_MASK)
#define SIM_SCGC_UART0_MASK                      0x100000u
#define SIM_SCGC_UART0_SHIFT                     20
#define SIM_SCGC_UART0_WIDTH                     1
#define SIM_SCGC_UART0(x)                        (((uint32_t)(((uint32_t)(x))<<SIM_SCGC_UART0_SHIFT))&SIM_SCGC_UART0_MASK)
#define SIM_SCGC_UART1_MASK                      0x200000u
#define SIM_SCGC_UART1_SHIFT                     21
#define SIM_SCGC_UART1_WIDTH                     1
#define SIM_SCGC_UART1(x)                        (((uint32_t)(((uint32_t)(x))<<SIM_SCGC_UART1_SHIFT))&SIM_SCGC_UART1_MASK)
#define SIM_SCGC_UART2_MASK                      0x400000u
#define SIM_SCGC_UART2_SHIFT                     22
#define SIM_SCGC_UART2_WIDTH                     1
#define SIM_SCGC_UART2(x)                        (((uint32_t)(((uint32_t)(x))<<SIM_SCGC_UART2_SHIFT))&SIM_SCGC_UART2_MASK)
#define SIM_SCGC_KBI0_MASK                       0x1000000u
#define SIM_SCGC_KBI0_SHIFT                      24
#define SIM_SCGC_KBI0_WIDTH                      1
#define SIM_SCGC_KBI0(x)                         (((uint32_t)(((uint32_t)(x))<<SIM_SCGC_KBI0_SHIFT))&SIM_SCGC_KBI0_MASK)
#define SIM_SCGC_KBI1_MASK                       0x2000000u
#define SIM_SCGC_KBI1_SHIFT                      25
#define SIM_SCGC_KBI1_WIDTH                      1
#define SIM_SCGC_KBI1(x)                         (((uint32_t)(((uint32_t)(x))<<SIM_SCGC_KBI1_SHIFT))&SIM_SCGC_KBI1_MASK)
#define SIM_SCGC_IRQ_MASK                        0x8000000u
#define SIM_SCGC_IRQ_SHIFT                       27
#define SIM_SCGC_IRQ_WIDTH                       1
#define SIM_SCGC_IRQ(x)                          (((uint32_t)(((uint32_t)(x))<<SIM_SCGC_IRQ_SHIFT))&SIM_SCGC_IRQ_MASK)
#define SIM_SCGC_ADC_MASK                        0x20000000u
#define SIM_SCGC_ADC_SHIFT                       29
#define SIM_SCGC_ADC_WIDTH                       1
#define SIM_SCGC_ADC(x)                          (((uint32_t)(((uint32_t)(x))<<SIM_SCGC_ADC_SHIFT))&SIM_SCGC_ADC_MASK)
#define SIM_SCGC_ACMP0_MASK                      0x40000000u
#define SIM_SCGC_ACMP0_SHIFT                     30
#define SIM_SCGC_ACMP0_WIDTH                     1
#define SIM_SCGC_ACMP0(x)                        (((uint32_t)(((uint32_t)(x))<<SIM_SCGC_ACMP0_SHIFT))&SIM_SCGC_ACMP0_MASK)
#define SIM_SCGC_ACMP1_MASK                      0x80000000u
#define SIM_SCGC_ACMP1_SHIFT                     31
#define SIM_SCGC_ACMP1_WIDTH                     1
#define SIM_SCGC_ACMP1(x)                        (((uint32_t)(((uint32_t)(x))<<SIM_SCGC_ACMP1_SHIFT))&SIM_SCGC_ACMP1_MASK)
/* UUIDL Bit Fields */
#define SIM_UUIDL_ID_MASK                        0xFFFFFFFFu
#define SIM_UUIDL_ID_SHIFT                       0
#define SIM_UUIDL_ID_WIDTH                       32
#define SIM_UUIDL_ID(x)                          (((uint32_t)(((uint32_t)(x))<<SIM_UUIDL_ID_SHIFT))&SIM_UUIDL_ID_MASK)
/* UUIDH Bit Fields */
#define SIM_UUIDH_ID_MASK                        0xFFFFFFFFu
#define SIM_UUIDH_ID_SHIFT                       0
#define SIM_UUIDH_ID_WIDTH                       32
#define SIM_UUIDH_ID(x)                          (((uint32_t)(((uint32_t)(x))<<SIM_UUIDH_ID_SHIFT))&SIM_UUIDH_ID_MASK)
/* BUSDIV Bit Fields */
#define SIM_BUSDIV_BUSDIV_MASK                   0x1u
#define SIM_BUSDIV_BUSDIV_SHIFT                  0
#define SIM_BUSDIV_BUSDIV_WIDTH                  1
#define SIM_BUSDIV_BUSDIV(x)                     (((uint32_t)(((uint32_t)(x))<<SIM_BUSDIV_BUSDIV_SHIFT))&SIM_BUSDIV_BUSDIV_MASK)

/*!
 * @}
 */ /* end of group SIM_Register_Masks */


/* SIM - Peripheral instance base addresses */
/** Peripheral SIM base pointer */
#define SIM_BASE_PTR                             ((SIM_MemMapPtr)0x40048000u)
/** Array initializer of SIM peripheral base pointers */
#define SIM_BASE_PTRS                            { SIM_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- SIM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SIM_Register_Accessor_Macros SIM - Register accessor macros
 * @{
 */


/* SIM - Register instance definitions */
/* SIM */
#define SIM_SRSID                                SIM_SRSID_REG(SIM_BASE_PTR)
#define SIM_SOPT                                 SIM_SOPT_REG(SIM_BASE_PTR)
#define SIM_PINSEL                               SIM_PINSEL_REG(SIM_BASE_PTR)
#define SIM_SCGC                                 SIM_SCGC_REG(SIM_BASE_PTR)
#define SIM_UUIDL                                SIM_UUIDL_REG(SIM_BASE_PTR)
#define SIM_UUIDH                                SIM_UUIDH_REG(SIM_BASE_PTR)
#define SIM_BUSDIV                               SIM_BUSDIV_REG(SIM_BASE_PTR)

/*!
 * @}
 */ /* end of group SIM_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group SIM_Peripheral */


/* ----------------------------------------------------------------------------
   -- SPI
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SPI_Peripheral SPI
 * @{
 */

/** SPI - Peripheral register structure */
typedef struct SPI_MemMap {
  uint8_t C1;                                      /**< SPI Control Register 1, offset: 0x0 */
  uint8_t C2;                                      /**< SPI Control Register 2, offset: 0x1 */
  uint8_t BR;                                      /**< SPI Baud Rate Register, offset: 0x2 */
  uint8_t S;                                       /**< SPI Status Register, offset: 0x3 */
  uint8_t RESERVED_0[1];
  uint8_t D;                                       /**< SPI Data Register, offset: 0x5 */
  uint8_t RESERVED_1[1];
  uint8_t M;                                       /**< SPI Match Register, offset: 0x7 */
} volatile *SPI_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- SPI - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SPI_Register_Accessor_Macros SPI - Register accessor macros
 * @{
 */


/* SPI - Register accessors */
#define SPI_C1_REG(base)                         ((base)->C1)
#define SPI_C2_REG(base)                         ((base)->C2)
#define SPI_BR_REG(base)                         ((base)->BR)
#define SPI_S_REG(base)                          ((base)->S)
#define SPI_D_REG(base)                          ((base)->D)
#define SPI_M_REG(base)                          ((base)->M)

/*!
 * @}
 */ /* end of group SPI_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- SPI Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SPI_Register_Masks SPI Register Masks
 * @{
 */

/* C1 Bit Fields */
#define SPI_C1_LSBFE_MASK                        0x1u
#define SPI_C1_LSBFE_SHIFT                       0
#define SPI_C1_LSBFE_WIDTH                       1
#define SPI_C1_LSBFE(x)                          (((uint8_t)(((uint8_t)(x))<<SPI_C1_LSBFE_SHIFT))&SPI_C1_LSBFE_MASK)
#define SPI_C1_SSOE_MASK                         0x2u
#define SPI_C1_SSOE_SHIFT                        1
#define SPI_C1_SSOE_WIDTH                        1
#define SPI_C1_SSOE(x)                           (((uint8_t)(((uint8_t)(x))<<SPI_C1_SSOE_SHIFT))&SPI_C1_SSOE_MASK)
#define SPI_C1_CPHA_MASK                         0x4u
#define SPI_C1_CPHA_SHIFT                        2
#define SPI_C1_CPHA_WIDTH                        1
#define SPI_C1_CPHA(x)                           (((uint8_t)(((uint8_t)(x))<<SPI_C1_CPHA_SHIFT))&SPI_C1_CPHA_MASK)
#define SPI_C1_CPOL_MASK                         0x8u
#define SPI_C1_CPOL_SHIFT                        3
#define SPI_C1_CPOL_WIDTH                        1
#define SPI_C1_CPOL(x)                           (((uint8_t)(((uint8_t)(x))<<SPI_C1_CPOL_SHIFT))&SPI_C1_CPOL_MASK)
#define SPI_C1_MSTR_MASK                         0x10u
#define SPI_C1_MSTR_SHIFT                        4
#define SPI_C1_MSTR_WIDTH                        1
#define SPI_C1_MSTR(x)                           (((uint8_t)(((uint8_t)(x))<<SPI_C1_MSTR_SHIFT))&SPI_C1_MSTR_MASK)
#define SPI_C1_SPTIE_MASK                        0x20u
#define SPI_C1_SPTIE_SHIFT                       5
#define SPI_C1_SPTIE_WIDTH                       1
#define SPI_C1_SPTIE(x)                          (((uint8_t)(((uint8_t)(x))<<SPI_C1_SPTIE_SHIFT))&SPI_C1_SPTIE_MASK)
#define SPI_C1_SPE_MASK                          0x40u
#define SPI_C1_SPE_SHIFT                         6
#define SPI_C1_SPE_WIDTH                         1
#define SPI_C1_SPE(x)                            (((uint8_t)(((uint8_t)(x))<<SPI_C1_SPE_SHIFT))&SPI_C1_SPE_MASK)
#define SPI_C1_SPIE_MASK                         0x80u
#define SPI_C1_SPIE_SHIFT                        7
#define SPI_C1_SPIE_WIDTH                        1
#define SPI_C1_SPIE(x)                           (((uint8_t)(((uint8_t)(x))<<SPI_C1_SPIE_SHIFT))&SPI_C1_SPIE_MASK)
/* C2 Bit Fields */
#define SPI_C2_SPC0_MASK                         0x1u
#define SPI_C2_SPC0_SHIFT                        0
#define SPI_C2_SPC0_WIDTH                        1
#define SPI_C2_SPC0(x)                           (((uint8_t)(((uint8_t)(x))<<SPI_C2_SPC0_SHIFT))&SPI_C2_SPC0_MASK)
#define SPI_C2_SPISWAI_MASK                      0x2u
#define SPI_C2_SPISWAI_SHIFT                     1
#define SPI_C2_SPISWAI_WIDTH                     1
#define SPI_C2_SPISWAI(x)                        (((uint8_t)(((uint8_t)(x))<<SPI_C2_SPISWAI_SHIFT))&SPI_C2_SPISWAI_MASK)
#define SPI_C2_BIDIROE_MASK                      0x8u
#define SPI_C2_BIDIROE_SHIFT                     3
#define SPI_C2_BIDIROE_WIDTH                     1
#define SPI_C2_BIDIROE(x)                        (((uint8_t)(((uint8_t)(x))<<SPI_C2_BIDIROE_SHIFT))&SPI_C2_BIDIROE_MASK)
#define SPI_C2_MODFEN_MASK                       0x10u
#define SPI_C2_MODFEN_SHIFT                      4
#define SPI_C2_MODFEN_WIDTH                      1
#define SPI_C2_MODFEN(x)                         (((uint8_t)(((uint8_t)(x))<<SPI_C2_MODFEN_SHIFT))&SPI_C2_MODFEN_MASK)
#define SPI_C2_SPMIE_MASK                        0x80u
#define SPI_C2_SPMIE_SHIFT                       7
#define SPI_C2_SPMIE_WIDTH                       1
#define SPI_C2_SPMIE(x)                          (((uint8_t)(((uint8_t)(x))<<SPI_C2_SPMIE_SHIFT))&SPI_C2_SPMIE_MASK)
/* BR Bit Fields */
#define SPI_BR_SPR_MASK                          0xFu
#define SPI_BR_SPR_SHIFT                         0
#define SPI_BR_SPR_WIDTH                         4
#define SPI_BR_SPR(x)                            (((uint8_t)(((uint8_t)(x))<<SPI_BR_SPR_SHIFT))&SPI_BR_SPR_MASK)
#define SPI_BR_SPPR_MASK                         0x70u
#define SPI_BR_SPPR_SHIFT                        4
#define SPI_BR_SPPR_WIDTH                        3
#define SPI_BR_SPPR(x)                           (((uint8_t)(((uint8_t)(x))<<SPI_BR_SPPR_SHIFT))&SPI_BR_SPPR_MASK)
/* S Bit Fields */
#define SPI_S_MODF_MASK                          0x10u
#define SPI_S_MODF_SHIFT                         4
#define SPI_S_MODF_WIDTH                         1
#define SPI_S_MODF(x)                            (((uint8_t)(((uint8_t)(x))<<SPI_S_MODF_SHIFT))&SPI_S_MODF_MASK)
#define SPI_S_SPTEF_MASK                         0x20u
#define SPI_S_SPTEF_SHIFT                        5
#define SPI_S_SPTEF_WIDTH                        1
#define SPI_S_SPTEF(x)                           (((uint8_t)(((uint8_t)(x))<<SPI_S_SPTEF_SHIFT))&SPI_S_SPTEF_MASK)
#define SPI_S_SPMF_MASK                          0x40u
#define SPI_S_SPMF_SHIFT                         6
#define SPI_S_SPMF_WIDTH                         1
#define SPI_S_SPMF(x)                            (((uint8_t)(((uint8_t)(x))<<SPI_S_SPMF_SHIFT))&SPI_S_SPMF_MASK)
#define SPI_S_SPRF_MASK                          0x80u
#define SPI_S_SPRF_SHIFT                         7
#define SPI_S_SPRF_WIDTH                         1
#define SPI_S_SPRF(x)                            (((uint8_t)(((uint8_t)(x))<<SPI_S_SPRF_SHIFT))&SPI_S_SPRF_MASK)
/* D Bit Fields */
#define SPI_D_Bits_MASK                          0xFFu
#define SPI_D_Bits_SHIFT                         0
#define SPI_D_Bits_WIDTH                         8
#define SPI_D_Bits(x)                            (((uint8_t)(((uint8_t)(x))<<SPI_D_Bits_SHIFT))&SPI_D_Bits_MASK)
/* M Bit Fields */
#define SPI_M_Bits_MASK                          0xFFu
#define SPI_M_Bits_SHIFT                         0
#define SPI_M_Bits_WIDTH                         8
#define SPI_M_Bits(x)                            (((uint8_t)(((uint8_t)(x))<<SPI_M_Bits_SHIFT))&SPI_M_Bits_MASK)

/*!
 * @}
 */ /* end of group SPI_Register_Masks */


/* SPI - Peripheral instance base addresses */
/** Peripheral SPI0 base pointer */
#define SPI0_BASE_PTR                            ((SPI_MemMapPtr)0x40076000u)
/** Peripheral SPI1 base pointer */
#define SPI1_BASE_PTR                            ((SPI_MemMapPtr)0x40077000u)
/** Array initializer of SPI peripheral base pointers */
#define SPI_BASE_PTRS                            { SPI0_BASE_PTR, SPI1_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- SPI - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SPI_Register_Accessor_Macros SPI - Register accessor macros
 * @{
 */


/* SPI - Register instance definitions */
/* SPI0 */
#define SPI0_C1                                  SPI_C1_REG(SPI0_BASE_PTR)
#define SPI0_C2                                  SPI_C2_REG(SPI0_BASE_PTR)
#define SPI0_BR                                  SPI_BR_REG(SPI0_BASE_PTR)
#define SPI0_S                                   SPI_S_REG(SPI0_BASE_PTR)
#define SPI0_D                                   SPI_D_REG(SPI0_BASE_PTR)
#define SPI0_M                                   SPI_M_REG(SPI0_BASE_PTR)
/* SPI1 */
#define SPI1_C1                                  SPI_C1_REG(SPI1_BASE_PTR)
#define SPI1_C2                                  SPI_C2_REG(SPI1_BASE_PTR)
#define SPI1_BR                                  SPI_BR_REG(SPI1_BASE_PTR)
#define SPI1_S                                   SPI_S_REG(SPI1_BASE_PTR)
#define SPI1_D                                   SPI_D_REG(SPI1_BASE_PTR)
#define SPI1_M                                   SPI_M_REG(SPI1_BASE_PTR)

/*!
 * @}
 */ /* end of group SPI_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group SPI_Peripheral */


/* ----------------------------------------------------------------------------
   -- SysTick
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SysTick_Peripheral SysTick
 * @{
 */

/** SysTick - Peripheral register structure */
typedef struct SysTick_MemMap {
  uint32_t CSR;                                    /**< SysTick Control and Status Register, offset: 0x0 */
  uint32_t RVR;                                    /**< SysTick Reload Value Register, offset: 0x4 */
  uint32_t CVR;                                    /**< SysTick Current Value Register, offset: 0x8 */
  uint32_t CALIB;                                  /**< SysTick Calibration Value Register, offset: 0xC */
} volatile *SysTick_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- SysTick - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SysTick_Register_Accessor_Macros SysTick - Register accessor macros
 * @{
 */


/* SysTick - Register accessors */
#define SysTick_CSR_REG(base)                    ((base)->CSR)
#define SysTick_RVR_REG(base)                    ((base)->RVR)
#define SysTick_CVR_REG(base)                    ((base)->CVR)
#define SysTick_CALIB_REG(base)                  ((base)->CALIB)

/*!
 * @}
 */ /* end of group SysTick_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- SysTick Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SysTick_Register_Masks SysTick Register Masks
 * @{
 */

/* CSR Bit Fields */
#define SysTick_CSR_ENABLE_MASK                  0x1u
#define SysTick_CSR_ENABLE_SHIFT                 0
#define SysTick_CSR_ENABLE_WIDTH                 1
#define SysTick_CSR_ENABLE(x)                    (((uint32_t)(((uint32_t)(x))<<SysTick_CSR_ENABLE_SHIFT))&SysTick_CSR_ENABLE_MASK)
#define SysTick_CSR_TICKINT_MASK                 0x2u
#define SysTick_CSR_TICKINT_SHIFT                1
#define SysTick_CSR_TICKINT_WIDTH                1
#define SysTick_CSR_TICKINT(x)                   (((uint32_t)(((uint32_t)(x))<<SysTick_CSR_TICKINT_SHIFT))&SysTick_CSR_TICKINT_MASK)
#define SysTick_CSR_CLKSOURCE_MASK               0x4u
#define SysTick_CSR_CLKSOURCE_SHIFT              2
#define SysTick_CSR_CLKSOURCE_WIDTH              1
#define SysTick_CSR_CLKSOURCE(x)                 (((uint32_t)(((uint32_t)(x))<<SysTick_CSR_CLKSOURCE_SHIFT))&SysTick_CSR_CLKSOURCE_MASK)
#define SysTick_CSR_COUNTFLAG_MASK               0x10000u
#define SysTick_CSR_COUNTFLAG_SHIFT              16
#define SysTick_CSR_COUNTFLAG_WIDTH              1
#define SysTick_CSR_COUNTFLAG(x)                 (((uint32_t)(((uint32_t)(x))<<SysTick_CSR_COUNTFLAG_SHIFT))&SysTick_CSR_COUNTFLAG_MASK)
/* RVR Bit Fields */
#define SysTick_RVR_RELOAD_MASK                  0xFFFFFFu
#define SysTick_RVR_RELOAD_SHIFT                 0
#define SysTick_RVR_RELOAD_WIDTH                 24
#define SysTick_RVR_RELOAD(x)                    (((uint32_t)(((uint32_t)(x))<<SysTick_RVR_RELOAD_SHIFT))&SysTick_RVR_RELOAD_MASK)
/* CVR Bit Fields */
#define SysTick_CVR_CURRENT_MASK                 0xFFFFFFu
#define SysTick_CVR_CURRENT_SHIFT                0
#define SysTick_CVR_CURRENT_WIDTH                24
#define SysTick_CVR_CURRENT(x)                   (((uint32_t)(((uint32_t)(x))<<SysTick_CVR_CURRENT_SHIFT))&SysTick_CVR_CURRENT_MASK)
/* CALIB Bit Fields */
#define SysTick_CALIB_TENMS_MASK                 0xFFFFFFu
#define SysTick_CALIB_TENMS_SHIFT                0
#define SysTick_CALIB_TENMS_WIDTH                24
#define SysTick_CALIB_TENMS(x)                   (((uint32_t)(((uint32_t)(x))<<SysTick_CALIB_TENMS_SHIFT))&SysTick_CALIB_TENMS_MASK)
#define SysTick_CALIB_SKEW_MASK                  0x40000000u
#define SysTick_CALIB_SKEW_SHIFT                 30
#define SysTick_CALIB_SKEW_WIDTH                 1
#define SysTick_CALIB_SKEW(x)                    (((uint32_t)(((uint32_t)(x))<<SysTick_CALIB_SKEW_SHIFT))&SysTick_CALIB_SKEW_MASK)
#define SysTick_CALIB_NOREF_MASK                 0x80000000u
#define SysTick_CALIB_NOREF_SHIFT                31
#define SysTick_CALIB_NOREF_WIDTH                1
#define SysTick_CALIB_NOREF(x)                   (((uint32_t)(((uint32_t)(x))<<SysTick_CALIB_NOREF_SHIFT))&SysTick_CALIB_NOREF_MASK)

/*!
 * @}
 */ /* end of group SysTick_Register_Masks */


/* SysTick - Peripheral instance base addresses */
/** Peripheral SysTick base pointer */
#define SysTick_BASE_PTR                         ((SysTick_MemMapPtr)0xE000E010u)
/** Array initializer of SysTick peripheral base pointers */
#define SysTick_BASE_PTRS                        { SysTick_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- SysTick - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SysTick_Register_Accessor_Macros SysTick - Register accessor macros
 * @{
 */


/* SysTick - Register instance definitions */
/* SysTick */
#define SYST_CSR                                 SysTick_CSR_REG(SysTick_BASE_PTR)
#define SYST_RVR                                 SysTick_RVR_REG(SysTick_BASE_PTR)
#define SYST_CVR                                 SysTick_CVR_REG(SysTick_BASE_PTR)
#define SYST_CALIB                               SysTick_CALIB_REG(SysTick_BASE_PTR)

/*!
 * @}
 */ /* end of group SysTick_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group SysTick_Peripheral */


/* ----------------------------------------------------------------------------
   -- UART
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup UART_Peripheral UART
 * @{
 */

/** UART - Peripheral register structure */
typedef struct UART_MemMap {
  uint8_t BDH;                                     /**< UART Baud Rate Register: High, offset: 0x0 */
  uint8_t BDL;                                     /**< UART Baud Rate Register: Low, offset: 0x1 */
  uint8_t C1;                                      /**< UART Control Register 1, offset: 0x2 */
  uint8_t C2;                                      /**< UART Control Register 2, offset: 0x3 */
  uint8_t S1;                                      /**< UART Status Register 1, offset: 0x4 */
  uint8_t S2;                                      /**< UART Status Register 2, offset: 0x5 */
  uint8_t C3;                                      /**< UART Control Register 3, offset: 0x6 */
  uint8_t D;                                       /**< UART Data Register, offset: 0x7 */
} volatile *UART_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- UART - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup UART_Register_Accessor_Macros UART - Register accessor macros
 * @{
 */


/* UART - Register accessors */
#define UART_BDH_REG(base)                       ((base)->BDH)
#define UART_BDL_REG(base)                       ((base)->BDL)
#define UART_C1_REG(base)                        ((base)->C1)
#define UART_C2_REG(base)                        ((base)->C2)
#define UART_S1_REG(base)                        ((base)->S1)
#define UART_S2_REG(base)                        ((base)->S2)
#define UART_C3_REG(base)                        ((base)->C3)
#define UART_D_REG(base)                         ((base)->D)

/*!
 * @}
 */ /* end of group UART_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- UART Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup UART_Register_Masks UART Register Masks
 * @{
 */

/* BDH Bit Fields */
#define UART_BDH_SBR_MASK                        0x1Fu
#define UART_BDH_SBR_SHIFT                       0
#define UART_BDH_SBR_WIDTH                       5
#define UART_BDH_SBR(x)                          (((uint8_t)(((uint8_t)(x))<<UART_BDH_SBR_SHIFT))&UART_BDH_SBR_MASK)
#define UART_BDH_SBNS_MASK                       0x20u
#define UART_BDH_SBNS_SHIFT                      5
#define UART_BDH_SBNS_WIDTH                      1
#define UART_BDH_SBNS(x)                         (((uint8_t)(((uint8_t)(x))<<UART_BDH_SBNS_SHIFT))&UART_BDH_SBNS_MASK)
#define UART_BDH_RXEDGIE_MASK                    0x40u
#define UART_BDH_RXEDGIE_SHIFT                   6
#define UART_BDH_RXEDGIE_WIDTH                   1
#define UART_BDH_RXEDGIE(x)                      (((uint8_t)(((uint8_t)(x))<<UART_BDH_RXEDGIE_SHIFT))&UART_BDH_RXEDGIE_MASK)
#define UART_BDH_LBKDIE_MASK                     0x80u
#define UART_BDH_LBKDIE_SHIFT                    7
#define UART_BDH_LBKDIE_WIDTH                    1
#define UART_BDH_LBKDIE(x)                       (((uint8_t)(((uint8_t)(x))<<UART_BDH_LBKDIE_SHIFT))&UART_BDH_LBKDIE_MASK)
/* BDL Bit Fields */
#define UART_BDL_SBR_MASK                        0xFFu
#define UART_BDL_SBR_SHIFT                       0
#define UART_BDL_SBR_WIDTH                       8
#define UART_BDL_SBR(x)                          (((uint8_t)(((uint8_t)(x))<<UART_BDL_SBR_SHIFT))&UART_BDL_SBR_MASK)
/* C1 Bit Fields */
#define UART_C1_PT_MASK                          0x1u
#define UART_C1_PT_SHIFT                         0
#define UART_C1_PT_WIDTH                         1
#define UART_C1_PT(x)                            (((uint8_t)(((uint8_t)(x))<<UART_C1_PT_SHIFT))&UART_C1_PT_MASK)
#define UART_C1_PE_MASK                          0x2u
#define UART_C1_PE_SHIFT                         1
#define UART_C1_PE_WIDTH                         1
#define UART_C1_PE(x)                            (((uint8_t)(((uint8_t)(x))<<UART_C1_PE_SHIFT))&UART_C1_PE_MASK)
#define UART_C1_ILT_MASK                         0x4u
#define UART_C1_ILT_SHIFT                        2
#define UART_C1_ILT_WIDTH                        1
#define UART_C1_ILT(x)                           (((uint8_t)(((uint8_t)(x))<<UART_C1_ILT_SHIFT))&UART_C1_ILT_MASK)
#define UART_C1_WAKE_MASK                        0x8u
#define UART_C1_WAKE_SHIFT                       3
#define UART_C1_WAKE_WIDTH                       1
#define UART_C1_WAKE(x)                          (((uint8_t)(((uint8_t)(x))<<UART_C1_WAKE_SHIFT))&UART_C1_WAKE_MASK)
#define UART_C1_M_MASK                           0x10u
#define UART_C1_M_SHIFT                          4
#define UART_C1_M_WIDTH                          1
#define UART_C1_M(x)                             (((uint8_t)(((uint8_t)(x))<<UART_C1_M_SHIFT))&UART_C1_M_MASK)
#define UART_C1_RSRC_MASK                        0x20u
#define UART_C1_RSRC_SHIFT                       5
#define UART_C1_RSRC_WIDTH                       1
#define UART_C1_RSRC(x)                          (((uint8_t)(((uint8_t)(x))<<UART_C1_RSRC_SHIFT))&UART_C1_RSRC_MASK)
#define UART_C1_UARTSWAI_MASK                    0x40u
#define UART_C1_UARTSWAI_SHIFT                   6
#define UART_C1_UARTSWAI_WIDTH                   1
#define UART_C1_UARTSWAI(x)                      (((uint8_t)(((uint8_t)(x))<<UART_C1_UARTSWAI_SHIFT))&UART_C1_UARTSWAI_MASK)
#define UART_C1_LOOPS_MASK                       0x80u
#define UART_C1_LOOPS_SHIFT                      7
#define UART_C1_LOOPS_WIDTH                      1
#define UART_C1_LOOPS(x)                         (((uint8_t)(((uint8_t)(x))<<UART_C1_LOOPS_SHIFT))&UART_C1_LOOPS_MASK)
/* C2 Bit Fields */
#define UART_C2_SBK_MASK                         0x1u
#define UART_C2_SBK_SHIFT                        0
#define UART_C2_SBK_WIDTH                        1
#define UART_C2_SBK(x)                           (((uint8_t)(((uint8_t)(x))<<UART_C2_SBK_SHIFT))&UART_C2_SBK_MASK)
#define UART_C2_RWU_MASK                         0x2u
#define UART_C2_RWU_SHIFT                        1
#define UART_C2_RWU_WIDTH                        1
#define UART_C2_RWU(x)                           (((uint8_t)(((uint8_t)(x))<<UART_C2_RWU_SHIFT))&UART_C2_RWU_MASK)
#define UART_C2_RE_MASK                          0x4u
#define UART_C2_RE_SHIFT                         2
#define UART_C2_RE_WIDTH                         1
#define UART_C2_RE(x)                            (((uint8_t)(((uint8_t)(x))<<UART_C2_RE_SHIFT))&UART_C2_RE_MASK)
#define UART_C2_TE_MASK                          0x8u
#define UART_C2_TE_SHIFT                         3
#define UART_C2_TE_WIDTH                         1
#define UART_C2_TE(x)                            (((uint8_t)(((uint8_t)(x))<<UART_C2_TE_SHIFT))&UART_C2_TE_MASK)
#define UART_C2_ILIE_MASK                        0x10u
#define UART_C2_ILIE_SHIFT                       4
#define UART_C2_ILIE_WIDTH                       1
#define UART_C2_ILIE(x)                          (((uint8_t)(((uint8_t)(x))<<UART_C2_ILIE_SHIFT))&UART_C2_ILIE_MASK)
#define UART_C2_RIE_MASK                         0x20u
#define UART_C2_RIE_SHIFT                        5
#define UART_C2_RIE_WIDTH                        1
#define UART_C2_RIE(x)                           (((uint8_t)(((uint8_t)(x))<<UART_C2_RIE_SHIFT))&UART_C2_RIE_MASK)
#define UART_C2_TCIE_MASK                        0x40u
#define UART_C2_TCIE_SHIFT                       6
#define UART_C2_TCIE_WIDTH                       1
#define UART_C2_TCIE(x)                          (((uint8_t)(((uint8_t)(x))<<UART_C2_TCIE_SHIFT))&UART_C2_TCIE_MASK)
#define UART_C2_TIE_MASK                         0x80u
#define UART_C2_TIE_SHIFT                        7
#define UART_C2_TIE_WIDTH                        1
#define UART_C2_TIE(x)                           (((uint8_t)(((uint8_t)(x))<<UART_C2_TIE_SHIFT))&UART_C2_TIE_MASK)
/* S1 Bit Fields */
#define UART_S1_PF_MASK                          0x1u
#define UART_S1_PF_SHIFT                         0
#define UART_S1_PF_WIDTH                         1
#define UART_S1_PF(x)                            (((uint8_t)(((uint8_t)(x))<<UART_S1_PF_SHIFT))&UART_S1_PF_MASK)
#define UART_S1_FE_MASK                          0x2u
#define UART_S1_FE_SHIFT                         1
#define UART_S1_FE_WIDTH                         1
#define UART_S1_FE(x)                            (((uint8_t)(((uint8_t)(x))<<UART_S1_FE_SHIFT))&UART_S1_FE_MASK)
#define UART_S1_NF_MASK                          0x4u
#define UART_S1_NF_SHIFT                         2
#define UART_S1_NF_WIDTH                         1
#define UART_S1_NF(x)                            (((uint8_t)(((uint8_t)(x))<<UART_S1_NF_SHIFT))&UART_S1_NF_MASK)
#define UART_S1_OR_MASK                          0x8u
#define UART_S1_OR_SHIFT                         3
#define UART_S1_OR_WIDTH                         1
#define UART_S1_OR(x)                            (((uint8_t)(((uint8_t)(x))<<UART_S1_OR_SHIFT))&UART_S1_OR_MASK)
#define UART_S1_IDLE_MASK                        0x10u
#define UART_S1_IDLE_SHIFT                       4
#define UART_S1_IDLE_WIDTH                       1
#define UART_S1_IDLE(x)                          (((uint8_t)(((uint8_t)(x))<<UART_S1_IDLE_SHIFT))&UART_S1_IDLE_MASK)
#define UART_S1_RDRF_MASK                        0x20u
#define UART_S1_RDRF_SHIFT                       5
#define UART_S1_RDRF_WIDTH                       1
#define UART_S1_RDRF(x)                          (((uint8_t)(((uint8_t)(x))<<UART_S1_RDRF_SHIFT))&UART_S1_RDRF_MASK)
#define UART_S1_TC_MASK                          0x40u
#define UART_S1_TC_SHIFT                         6
#define UART_S1_TC_WIDTH                         1
#define UART_S1_TC(x)                            (((uint8_t)(((uint8_t)(x))<<UART_S1_TC_SHIFT))&UART_S1_TC_MASK)
#define UART_S1_TDRE_MASK                        0x80u
#define UART_S1_TDRE_SHIFT                       7
#define UART_S1_TDRE_WIDTH                       1
#define UART_S1_TDRE(x)                          (((uint8_t)(((uint8_t)(x))<<UART_S1_TDRE_SHIFT))&UART_S1_TDRE_MASK)
/* S2 Bit Fields */
#define UART_S2_RAF_MASK                         0x1u
#define UART_S2_RAF_SHIFT                        0
#define UART_S2_RAF_WIDTH                        1
#define UART_S2_RAF(x)                           (((uint8_t)(((uint8_t)(x))<<UART_S2_RAF_SHIFT))&UART_S2_RAF_MASK)
#define UART_S2_LBKDE_MASK                       0x2u
#define UART_S2_LBKDE_SHIFT                      1
#define UART_S2_LBKDE_WIDTH                      1
#define UART_S2_LBKDE(x)                         (((uint8_t)(((uint8_t)(x))<<UART_S2_LBKDE_SHIFT))&UART_S2_LBKDE_MASK)
#define UART_S2_BRK13_MASK                       0x4u
#define UART_S2_BRK13_SHIFT                      2
#define UART_S2_BRK13_WIDTH                      1
#define UART_S2_BRK13(x)                         (((uint8_t)(((uint8_t)(x))<<UART_S2_BRK13_SHIFT))&UART_S2_BRK13_MASK)
#define UART_S2_RWUID_MASK                       0x8u
#define UART_S2_RWUID_SHIFT                      3
#define UART_S2_RWUID_WIDTH                      1
#define UART_S2_RWUID(x)                         (((uint8_t)(((uint8_t)(x))<<UART_S2_RWUID_SHIFT))&UART_S2_RWUID_MASK)
#define UART_S2_RXINV_MASK                       0x10u
#define UART_S2_RXINV_SHIFT                      4
#define UART_S2_RXINV_WIDTH                      1
#define UART_S2_RXINV(x)                         (((uint8_t)(((uint8_t)(x))<<UART_S2_RXINV_SHIFT))&UART_S2_RXINV_MASK)
#define UART_S2_RXEDGIF_MASK                     0x40u
#define UART_S2_RXEDGIF_SHIFT                    6
#define UART_S2_RXEDGIF_WIDTH                    1
#define UART_S2_RXEDGIF(x)                       (((uint8_t)(((uint8_t)(x))<<UART_S2_RXEDGIF_SHIFT))&UART_S2_RXEDGIF_MASK)
#define UART_S2_LBKDIF_MASK                      0x80u
#define UART_S2_LBKDIF_SHIFT                     7
#define UART_S2_LBKDIF_WIDTH                     1
#define UART_S2_LBKDIF(x)                        (((uint8_t)(((uint8_t)(x))<<UART_S2_LBKDIF_SHIFT))&UART_S2_LBKDIF_MASK)
/* C3 Bit Fields */
#define UART_C3_PEIE_MASK                        0x1u
#define UART_C3_PEIE_SHIFT                       0
#define UART_C3_PEIE_WIDTH                       1
#define UART_C3_PEIE(x)                          (((uint8_t)(((uint8_t)(x))<<UART_C3_PEIE_SHIFT))&UART_C3_PEIE_MASK)
#define UART_C3_FEIE_MASK                        0x2u
#define UART_C3_FEIE_SHIFT                       1
#define UART_C3_FEIE_WIDTH                       1
#define UART_C3_FEIE(x)                          (((uint8_t)(((uint8_t)(x))<<UART_C3_FEIE_SHIFT))&UART_C3_FEIE_MASK)
#define UART_C3_NEIE_MASK                        0x4u
#define UART_C3_NEIE_SHIFT                       2
#define UART_C3_NEIE_WIDTH                       1
#define UART_C3_NEIE(x)                          (((uint8_t)(((uint8_t)(x))<<UART_C3_NEIE_SHIFT))&UART_C3_NEIE_MASK)
#define UART_C3_ORIE_MASK                        0x8u
#define UART_C3_ORIE_SHIFT                       3
#define UART_C3_ORIE_WIDTH                       1
#define UART_C3_ORIE(x)                          (((uint8_t)(((uint8_t)(x))<<UART_C3_ORIE_SHIFT))&UART_C3_ORIE_MASK)
#define UART_C3_TXINV_MASK                       0x10u
#define UART_C3_TXINV_SHIFT                      4
#define UART_C3_TXINV_WIDTH                      1
#define UART_C3_TXINV(x)                         (((uint8_t)(((uint8_t)(x))<<UART_C3_TXINV_SHIFT))&UART_C3_TXINV_MASK)
#define UART_C3_TXDIR_MASK                       0x20u
#define UART_C3_TXDIR_SHIFT                      5
#define UART_C3_TXDIR_WIDTH                      1
#define UART_C3_TXDIR(x)                         (((uint8_t)(((uint8_t)(x))<<UART_C3_TXDIR_SHIFT))&UART_C3_TXDIR_MASK)
#define UART_C3_T8_MASK                          0x40u
#define UART_C3_T8_SHIFT                         6
#define UART_C3_T8_WIDTH                         1
#define UART_C3_T8(x)                            (((uint8_t)(((uint8_t)(x))<<UART_C3_T8_SHIFT))&UART_C3_T8_MASK)
#define UART_C3_R8_MASK                          0x80u
#define UART_C3_R8_SHIFT                         7
#define UART_C3_R8_WIDTH                         1
#define UART_C3_R8(x)                            (((uint8_t)(((uint8_t)(x))<<UART_C3_R8_SHIFT))&UART_C3_R8_MASK)
/* D Bit Fields */
#define UART_D_R0T0_MASK                         0x1u
#define UART_D_R0T0_SHIFT                        0
#define UART_D_R0T0_WIDTH                        1
#define UART_D_R0T0(x)                           (((uint8_t)(((uint8_t)(x))<<UART_D_R0T0_SHIFT))&UART_D_R0T0_MASK)
#define UART_D_R1T1_MASK                         0x2u
#define UART_D_R1T1_SHIFT                        1
#define UART_D_R1T1_WIDTH                        1
#define UART_D_R1T1(x)                           (((uint8_t)(((uint8_t)(x))<<UART_D_R1T1_SHIFT))&UART_D_R1T1_MASK)
#define UART_D_R2T2_MASK                         0x4u
#define UART_D_R2T2_SHIFT                        2
#define UART_D_R2T2_WIDTH                        1
#define UART_D_R2T2(x)                           (((uint8_t)(((uint8_t)(x))<<UART_D_R2T2_SHIFT))&UART_D_R2T2_MASK)
#define UART_D_R3T3_MASK                         0x8u
#define UART_D_R3T3_SHIFT                        3
#define UART_D_R3T3_WIDTH                        1
#define UART_D_R3T3(x)                           (((uint8_t)(((uint8_t)(x))<<UART_D_R3T3_SHIFT))&UART_D_R3T3_MASK)
#define UART_D_R4T4_MASK                         0x10u
#define UART_D_R4T4_SHIFT                        4
#define UART_D_R4T4_WIDTH                        1
#define UART_D_R4T4(x)                           (((uint8_t)(((uint8_t)(x))<<UART_D_R4T4_SHIFT))&UART_D_R4T4_MASK)
#define UART_D_R5T5_MASK                         0x20u
#define UART_D_R5T5_SHIFT                        5
#define UART_D_R5T5_WIDTH                        1
#define UART_D_R5T5(x)                           (((uint8_t)(((uint8_t)(x))<<UART_D_R5T5_SHIFT))&UART_D_R5T5_MASK)
#define UART_D_R6T6_MASK                         0x40u
#define UART_D_R6T6_SHIFT                        6
#define UART_D_R6T6_WIDTH                        1
#define UART_D_R6T6(x)                           (((uint8_t)(((uint8_t)(x))<<UART_D_R6T6_SHIFT))&UART_D_R6T6_MASK)
#define UART_D_R7T7_MASK                         0x80u
#define UART_D_R7T7_SHIFT                        7
#define UART_D_R7T7_WIDTH                        1
#define UART_D_R7T7(x)                           (((uint8_t)(((uint8_t)(x))<<UART_D_R7T7_SHIFT))&UART_D_R7T7_MASK)

/*!
 * @}
 */ /* end of group UART_Register_Masks */


/* UART - Peripheral instance base addresses */
/** Peripheral UART0 base pointer */
#define UART0_BASE_PTR                           ((UART_MemMapPtr)0x4006A000u)
/** Peripheral UART1 base pointer */
#define UART1_BASE_PTR                           ((UART_MemMapPtr)0x4006B000u)
/** Peripheral UART2 base pointer */
#define UART2_BASE_PTR                           ((UART_MemMapPtr)0x4006C000u)
/** Array initializer of UART peripheral base pointers */
#define UART_BASE_PTRS                           { UART0_BASE_PTR, UART1_BASE_PTR, UART2_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- UART - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup UART_Register_Accessor_Macros UART - Register accessor macros
 * @{
 */


/* UART - Register instance definitions */
/* UART0 */
#define UART0_BDH                                UART_BDH_REG(UART0_BASE_PTR)
#define UART0_BDL                                UART_BDL_REG(UART0_BASE_PTR)
#define UART0_C1                                 UART_C1_REG(UART0_BASE_PTR)
#define UART0_C2                                 UART_C2_REG(UART0_BASE_PTR)
#define UART0_S1                                 UART_S1_REG(UART0_BASE_PTR)
#define UART0_S2                                 UART_S2_REG(UART0_BASE_PTR)
#define UART0_C3                                 UART_C3_REG(UART0_BASE_PTR)
#define UART0_D                                  UART_D_REG(UART0_BASE_PTR)
/* UART1 */
#define UART1_BDH                                UART_BDH_REG(UART1_BASE_PTR)
#define UART1_BDL                                UART_BDL_REG(UART1_BASE_PTR)
#define UART1_C1                                 UART_C1_REG(UART1_BASE_PTR)
#define UART1_C2                                 UART_C2_REG(UART1_BASE_PTR)
#define UART1_S1                                 UART_S1_REG(UART1_BASE_PTR)
#define UART1_S2                                 UART_S2_REG(UART1_BASE_PTR)
#define UART1_C3                                 UART_C3_REG(UART1_BASE_PTR)
#define UART1_D                                  UART_D_REG(UART1_BASE_PTR)
/* UART2 */
#define UART2_BDH                                UART_BDH_REG(UART2_BASE_PTR)
#define UART2_BDL                                UART_BDL_REG(UART2_BASE_PTR)
#define UART2_C1                                 UART_C1_REG(UART2_BASE_PTR)
#define UART2_C2                                 UART_C2_REG(UART2_BASE_PTR)
#define UART2_S1                                 UART_S1_REG(UART2_BASE_PTR)
#define UART2_S2                                 UART_S2_REG(UART2_BASE_PTR)
#define UART2_C3                                 UART_C3_REG(UART2_BASE_PTR)
#define UART2_D                                  UART_D_REG(UART2_BASE_PTR)

/*!
 * @}
 */ /* end of group UART_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group UART_Peripheral */


/* ----------------------------------------------------------------------------
   -- WDOG
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup WDOG_Peripheral WDOG
 * @{
 */

/** WDOG - Peripheral register structure */
typedef struct WDOG_MemMap {
  uint8_t CS1;                                     /**< Watchdog Control and Status Register 1, offset: 0x0 */
  uint8_t CS2;                                     /**< Watchdog Control and Status Register 2, offset: 0x1 */
  union {                                          /* offset: 0x2 */
    uint16_t CNT;                                    /**< Watchdog Counter Register., offset: 0x2 */
    struct {                                         /* offset: 0x2 */
      uint8_t CNTH;                                    /**< Watchdog Counter Register: High, offset: 0x2 */
      uint8_t CNTL;                                    /**< Watchdog Counter Register: Low, offset: 0x3 */
    } CNT8B;
  };
  union {                                          /* offset: 0x4 */
    uint16_t TOVAL;                                  /**< Watchdog Timeout Value Register., offset: 0x4 */
    struct {                                         /* offset: 0x4 */
      uint8_t TOVALH;                                  /**< Watchdog Timeout Value Register: High, offset: 0x4 */
      uint8_t TOVALL;                                  /**< Watchdog Timeout Value Register: Low, offset: 0x5 */
    } TOVAL8B;
  };
  union {                                          /* offset: 0x6 */
    uint16_t WIN;                                    /**< Watchdog Window Register., offset: 0x6 */
    struct {                                         /* offset: 0x6 */
      uint8_t WINH;                                    /**< Watchdog Window Register: High, offset: 0x6 */
      uint8_t WINL;                                    /**< Watchdog Window Register: Low, offset: 0x7 */
    } WIN8B;
  };
} volatile *WDOG_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- WDOG - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup WDOG_Register_Accessor_Macros WDOG - Register accessor macros
 * @{
 */


/* WDOG - Register accessors */
#define WDOG_CS1_REG(base)                       ((base)->CS1)
#define WDOG_CS2_REG(base)                       ((base)->CS2)
#define WDOG_CNT_REG(base)                       ((base)->CNT)
#define WDOG_CNTH_REG(base)                      ((base)->CNT8B.CNTH)
#define WDOG_CNTL_REG(base)                      ((base)->CNT8B.CNTL)
#define WDOG_TOVAL_REG(base)                     ((base)->TOVAL)
#define WDOG_TOVALH_REG(base)                    ((base)->TOVAL8B.TOVALH)
#define WDOG_TOVALL_REG(base)                    ((base)->TOVAL8B.TOVALL)
#define WDOG_WIN_REG(base)                       ((base)->WIN)
#define WDOG_WINH_REG(base)                      ((base)->WIN8B.WINH)
#define WDOG_WINL_REG(base)                      ((base)->WIN8B.WINL)

/*!
 * @}
 */ /* end of group WDOG_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- WDOG Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup WDOG_Register_Masks WDOG Register Masks
 * @{
 */

/* CS1 Bit Fields */
#define WDOG_CS1_STOP_MASK                       0x1u
#define WDOG_CS1_STOP_SHIFT                      0
#define WDOG_CS1_STOP_WIDTH                      1
#define WDOG_CS1_STOP(x)                         (((uint8_t)(((uint8_t)(x))<<WDOG_CS1_STOP_SHIFT))&WDOG_CS1_STOP_MASK)
#define WDOG_CS1_WAIT_MASK                       0x2u
#define WDOG_CS1_WAIT_SHIFT                      1
#define WDOG_CS1_WAIT_WIDTH                      1
#define WDOG_CS1_WAIT(x)                         (((uint8_t)(((uint8_t)(x))<<WDOG_CS1_WAIT_SHIFT))&WDOG_CS1_WAIT_MASK)
#define WDOG_CS1_DBG_MASK                        0x4u
#define WDOG_CS1_DBG_SHIFT                       2
#define WDOG_CS1_DBG_WIDTH                       1
#define WDOG_CS1_DBG(x)                          (((uint8_t)(((uint8_t)(x))<<WDOG_CS1_DBG_SHIFT))&WDOG_CS1_DBG_MASK)
#define WDOG_CS1_TST_MASK                        0x18u
#define WDOG_CS1_TST_SHIFT                       3
#define WDOG_CS1_TST_WIDTH                       2
#define WDOG_CS1_TST(x)                          (((uint8_t)(((uint8_t)(x))<<WDOG_CS1_TST_SHIFT))&WDOG_CS1_TST_MASK)
#define WDOG_CS1_UPDATE_MASK                     0x20u
#define WDOG_CS1_UPDATE_SHIFT                    5
#define WDOG_CS1_UPDATE_WIDTH                    1
#define WDOG_CS1_UPDATE(x)                       (((uint8_t)(((uint8_t)(x))<<WDOG_CS1_UPDATE_SHIFT))&WDOG_CS1_UPDATE_MASK)
#define WDOG_CS1_INT_MASK                        0x40u
#define WDOG_CS1_INT_SHIFT                       6
#define WDOG_CS1_INT_WIDTH                       1
#define WDOG_CS1_INT(x)                          (((uint8_t)(((uint8_t)(x))<<WDOG_CS1_INT_SHIFT))&WDOG_CS1_INT_MASK)
#define WDOG_CS1_EN_MASK                         0x80u
#define WDOG_CS1_EN_SHIFT                        7
#define WDOG_CS1_EN_WIDTH                        1
#define WDOG_CS1_EN(x)                           (((uint8_t)(((uint8_t)(x))<<WDOG_CS1_EN_SHIFT))&WDOG_CS1_EN_MASK)
/* CS2 Bit Fields */
#define WDOG_CS2_CLK_MASK                        0x3u
#define WDOG_CS2_CLK_SHIFT                       0
#define WDOG_CS2_CLK_WIDTH                       2
#define WDOG_CS2_CLK(x)                          (((uint8_t)(((uint8_t)(x))<<WDOG_CS2_CLK_SHIFT))&WDOG_CS2_CLK_MASK)
#define WDOG_CS2_PRES_MASK                       0x10u
#define WDOG_CS2_PRES_SHIFT                      4
#define WDOG_CS2_PRES_WIDTH                      1
#define WDOG_CS2_PRES(x)                         (((uint8_t)(((uint8_t)(x))<<WDOG_CS2_PRES_SHIFT))&WDOG_CS2_PRES_MASK)
#define WDOG_CS2_FLG_MASK                        0x40u
#define WDOG_CS2_FLG_SHIFT                       6
#define WDOG_CS2_FLG_WIDTH                       1
#define WDOG_CS2_FLG(x)                          (((uint8_t)(((uint8_t)(x))<<WDOG_CS2_FLG_SHIFT))&WDOG_CS2_FLG_MASK)
#define WDOG_CS2_WIN_MASK                        0x80u
#define WDOG_CS2_WIN_SHIFT                       7
#define WDOG_CS2_WIN_WIDTH                       1
#define WDOG_CS2_WIN(x)                          (((uint8_t)(((uint8_t)(x))<<WDOG_CS2_WIN_SHIFT))&WDOG_CS2_WIN_MASK)
/* CNT Bit Fields */
#define WDOG_CNT_CNT_MASK                        0xFFFFu
#define WDOG_CNT_CNT_SHIFT                       0
#define WDOG_CNT_CNT_WIDTH                       16
#define WDOG_CNT_CNT(x)                          (((uint16_t)(((uint16_t)(x))<<WDOG_CNT_CNT_SHIFT))&WDOG_CNT_CNT_MASK)
/* CNTH Bit Fields */
#define WDOG_CNTH_CNTHIGH_MASK                   0xFFu
#define WDOG_CNTH_CNTHIGH_SHIFT                  0
#define WDOG_CNTH_CNTHIGH_WIDTH                  8
#define WDOG_CNTH_CNTHIGH(x)                     (((uint8_t)(((uint8_t)(x))<<WDOG_CNTH_CNTHIGH_SHIFT))&WDOG_CNTH_CNTHIGH_MASK)
/* CNTL Bit Fields */
#define WDOG_CNTL_CNTLOW_MASK                    0xFFu
#define WDOG_CNTL_CNTLOW_SHIFT                   0
#define WDOG_CNTL_CNTLOW_WIDTH                   8
#define WDOG_CNTL_CNTLOW(x)                      (((uint8_t)(((uint8_t)(x))<<WDOG_CNTL_CNTLOW_SHIFT))&WDOG_CNTL_CNTLOW_MASK)
/* TOVAL Bit Fields */
#define WDOG_TOVAL_TOVAL_MASK                    0xFFFFu
#define WDOG_TOVAL_TOVAL_SHIFT                   0
#define WDOG_TOVAL_TOVAL_WIDTH                   16
#define WDOG_TOVAL_TOVAL(x)                      (((uint16_t)(((uint16_t)(x))<<WDOG_TOVAL_TOVAL_SHIFT))&WDOG_TOVAL_TOVAL_MASK)
/* TOVALH Bit Fields */
#define WDOG_TOVALH_TOVALHIGH_MASK               0xFFu
#define WDOG_TOVALH_TOVALHIGH_SHIFT              0
#define WDOG_TOVALH_TOVALHIGH_WIDTH              8
#define WDOG_TOVALH_TOVALHIGH(x)                 (((uint8_t)(((uint8_t)(x))<<WDOG_TOVALH_TOVALHIGH_SHIFT))&WDOG_TOVALH_TOVALHIGH_MASK)
/* TOVALL Bit Fields */
#define WDOG_TOVALL_TOVALLOW_MASK                0xFFu
#define WDOG_TOVALL_TOVALLOW_SHIFT               0
#define WDOG_TOVALL_TOVALLOW_WIDTH               8
#define WDOG_TOVALL_TOVALLOW(x)                  (((uint8_t)(((uint8_t)(x))<<WDOG_TOVALL_TOVALLOW_SHIFT))&WDOG_TOVALL_TOVALLOW_MASK)
/* WIN Bit Fields */
#define WDOG_WIN_WIN_MASK                        0xFFFFu
#define WDOG_WIN_WIN_SHIFT                       0
#define WDOG_WIN_WIN_WIDTH                       16
#define WDOG_WIN_WIN(x)                          (((uint16_t)(((uint16_t)(x))<<WDOG_WIN_WIN_SHIFT))&WDOG_WIN_WIN_MASK)
/* WINH Bit Fields */
#define WDOG_WINH_WINHIGH_MASK                   0xFFu
#define WDOG_WINH_WINHIGH_SHIFT                  0
#define WDOG_WINH_WINHIGH_WIDTH                  8
#define WDOG_WINH_WINHIGH(x)                     (((uint8_t)(((uint8_t)(x))<<WDOG_WINH_WINHIGH_SHIFT))&WDOG_WINH_WINHIGH_MASK)
/* WINL Bit Fields */
#define WDOG_WINL_WINLOW_MASK                    0xFFu
#define WDOG_WINL_WINLOW_SHIFT                   0
#define WDOG_WINL_WINLOW_WIDTH                   8
#define WDOG_WINL_WINLOW(x)                      (((uint8_t)(((uint8_t)(x))<<WDOG_WINL_WINLOW_SHIFT))&WDOG_WINL_WINLOW_MASK)

/*!
 * @}
 */ /* end of group WDOG_Register_Masks */


/* WDOG - Peripheral instance base addresses */
/** Peripheral WDOG base pointer */
#define WDOG_BASE_PTR                            ((WDOG_MemMapPtr)0x40052000u)
/** Array initializer of WDOG peripheral base pointers */
#define WDOG_BASE_PTRS                           { WDOG_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- WDOG - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup WDOG_Register_Accessor_Macros WDOG - Register accessor macros
 * @{
 */


/* WDOG - Register instance definitions */
/* WDOG */
#define WDOG_CS1                                 WDOG_CS1_REG(WDOG_BASE_PTR)
#define WDOG_CS2                                 WDOG_CS2_REG(WDOG_BASE_PTR)
#define WDOG_CNT                                 WDOG_CNT_REG(WDOG_BASE_PTR)
#define WDOG_CNTH                                WDOG_CNTH_REG(WDOG_BASE_PTR)
#define WDOG_CNTL                                WDOG_CNTL_REG(WDOG_BASE_PTR)
#define WDOG_TOVAL                               WDOG_TOVAL_REG(WDOG_BASE_PTR)
#define WDOG_TOVALH                              WDOG_TOVALH_REG(WDOG_BASE_PTR)
#define WDOG_TOVALL                              WDOG_TOVALL_REG(WDOG_BASE_PTR)
#define WDOG_WIN                                 WDOG_WIN_REG(WDOG_BASE_PTR)
#define WDOG_WINH                                WDOG_WINH_REG(WDOG_BASE_PTR)
#define WDOG_WINL                                WDOG_WINL_REG(WDOG_BASE_PTR)

/*!
 * @}
 */ /* end of group WDOG_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group WDOG_Peripheral */


/*
** End of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #pragma pop
#elif defined(__CWCC__)
  #pragma pop
#elif defined(__GNUC__)
  /* leave anonymous unions enabled */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=default
#else
  #error Not supported compiler type
#endif

/*!
 * @}
 */ /* end of group Peripheral_defines */


/* ----------------------------------------------------------------------------
   -- Backward Compatibility
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Backward_Compatibility_Symbols Backward Compatibility
 * @{
 */

#define FPTA_BASE_PTR                     FGPIOA_BASE_PTR
#define FPTB_BASE_PTR                     FGPIOB_BASE_PTR
#define PTA_BASE_PTR                      GPIOA_BASE_PTR
#define PTB_BASE_PTR                      GPIOB_BASE_PTR
#define FTM0_CNTIN                        This_symbol_has_been_deprecated
#define FTM0_STATUS                       This_symbol_has_been_deprecated
#define FTM0_MODE                         This_symbol_has_been_deprecated
#define FTM0_SYNC                         This_symbol_has_been_deprecated
#define FTM0_OUTINIT                      This_symbol_has_been_deprecated
#define FTM0_OUTMASK                      This_symbol_has_been_deprecated
#define FTM0_COMBINE                      This_symbol_has_been_deprecated
#define FTM0_DEADTIME                     This_symbol_has_been_deprecated
#define FTM0_EXTTRIG                      This_symbol_has_been_deprecated
#define FTM0_POL                          This_symbol_has_been_deprecated
#define FTM0_FMS                          This_symbol_has_been_deprecated
#define FTM0_FILTER                       This_symbol_has_been_deprecated
#define FTM0_FLTCTRL                      This_symbol_has_been_deprecated
#define FTM0_CONF                         This_symbol_has_been_deprecated
#define FTM0_FLTPOL                       This_symbol_has_been_deprecated
#define FTM0_SYNCONF                      This_symbol_has_been_deprecated
#define FTM0_INVCTRL                      This_symbol_has_been_deprecated
#define FTM0_SWOCTRL                      This_symbol_has_been_deprecated
#define FTM0_PWMLOAD                      This_symbol_has_been_deprecated
#define FTM1_CNTIN                        This_symbol_has_been_deprecated
#define FTM1_STATUS                       This_symbol_has_been_deprecated
#define FTM1_MODE                         This_symbol_has_been_deprecated
#define FTM1_SYNC                         This_symbol_has_been_deprecated
#define FTM1_OUTINIT                      This_symbol_has_been_deprecated
#define FTM1_OUTMASK                      This_symbol_has_been_deprecated
#define FTM1_COMBINE                      This_symbol_has_been_deprecated
#define FTM1_DEADTIME                     This_symbol_has_been_deprecated
#define FTM1_EXTTRIG                      This_symbol_has_been_deprecated
#define FTM1_POL                          This_symbol_has_been_deprecated
#define FTM1_FMS                          This_symbol_has_been_deprecated
#define FTM1_FILTER                       This_symbol_has_been_deprecated
#define FTM1_FLTCTRL                      This_symbol_has_been_deprecated
#define FTM1_CONF                         This_symbol_has_been_deprecated
#define FTM1_FLTPOL                       This_symbol_has_been_deprecated
#define FTM1_SYNCONF                      This_symbol_has_been_deprecated
#define FTM1_INVCTRL                      This_symbol_has_been_deprecated
#define FTM1_SWOCTRL                      This_symbol_has_been_deprecated
#define FTM1_PWMLOAD                      This_symbol_has_been_deprecated
#define NV_DFPROT_REG(base)               NV_EEPROT_REG(base)
#define NV_DFPROT_DPS_MASK                NV_EEPROT_DPS_MASK
#define NV_DFPROT_DPS_SHIFT               NV_EEPROT_DPS_SHIFT
#define NV_DFPROT_DPS(x)                  NV_EEPROT_DPS(x)
#define NV_DFPROT_DPOPEN_MASK             NV_EEPROT_DPOPEN_MASK
#define NV_DFPROT_DPOPEN_SHIFT            NV_EEPROT_DPOPEN_SHIFT
#define NV_DFPROT_DPOPEN_SHIFT            NV_EEPROT_DPOPEN_SHIFT
#define PMC_SPMSC1_BGBDS_MASK             This_symbol_has_been_deprecated
#define PMC_SPMSC1_BGBDS_SHIFT            This_symbol_has_been_deprecated
#define SIM_PINSEL_IICPS_MASK             SIM_PINSEL_I2C0PS_MASK
#define SIM_PINSEL_IICPS_SHIFT            SIM_PINSEL_I2C0PS_SHIFT
#define SIM_SCGC_IIC_MASK                 SIM_SCGC_I2C_MASK
#define SIM_SCGC_IIC_SHIFT                SIM_SCGC_I2C_SHIFT
#define NVIC_ISER_SETENA_MASK             0xFFFFFFFFu
#define NVIC_ISER_SETENA_SHIFT            0
#define NVIC_ISER_SETENA(x)               (((uint32_t)(((uint32_t)(x))<<NVIC_ISER_SETENA_SHIFT))&NVIC_ISER_SETENA_MASK)
#define NVIC_ICER_CLRENA_MASK             0xFFFFFFFFu
#define NVIC_ICER_CLRENA_SHIFT            0
#define NVIC_ICER_CLRENA(x)               (((uint32_t)(((uint32_t)(x))<<NVIC_ICER_CLRENA_SHIFT))&NVIC_ICER_CLRENA_MASK)
#define NVIC_ISPR_SETPEND_MASK            0xFFFFFFFFu
#define NVIC_ISPR_SETPEND_SHIFT           0
#define NVIC_ISPR_SETPEND(x)              (((uint32_t)(((uint32_t)(x))<<NVIC_ISPR_SETPEND_SHIFT))&NVIC_ISPR_SETPEND_MASK)
#define NVIC_ICPR_CLRPEND_MASK            0xFFFFFFFFu
#define NVIC_ICPR_CLRPEND_SHIFT           0
#define NVIC_ICPR_CLRPEND(x)              (((uint32_t)(((uint32_t)(x))<<NVIC_ICPR_CLRPEND_SHIFT))&NVIC_ICPR_CLRPEND_MASK)
#define SCB_ICSR_VECTACTIVE_MASK          This_symbol_has_been_deprecated
#define SCB_ICSR_VECTACTIVE_SHIFT         This_symbol_has_been_deprecated
#define SCB_ICSR_VECTACTIVE(x)            This_symbol_has_been_deprecated
#define SCB_ICSR_ISRPENDING_MASK          This_symbol_has_been_deprecated
#define SCB_ICSR_ISRPENDING_SHIFT         This_symbol_has_been_deprecated
#define INT_Watchdog                      INT_WDOG_EWM

/*!
 * @}
 */ /* end of group Backward_Compatibility_Symbols */


#else /* #if !defined(MCU_MKE02Z2) && !defined(MCU_MKE02Z4) && !defined(MCU_SKEAZN642) */
  /* There is already included the same memory map. Check if it is compatible (has the same major version) */
  #if (MCU_MEM_MAP_VERSION != 0x0100u)
    #if (!defined(MCU_MEM_MAP_SUPPRESS_VERSION_WARNING))
      #warning There are included two not compatible versions of memory maps. Please check possible differences.
    #endif /* (!defined(MCU_MEM_MAP_SUPPRESS_VERSION_WARNING)) */
  #endif /* (MCU_MEM_MAP_VERSION != 0x0100u) */
#endif  /* #if !defined(MCU_MKE02Z2) && !defined(MCU_MKE02Z4) && !defined(MCU_SKEAZN642) */

/* MKE02Z2.h, eof. */
