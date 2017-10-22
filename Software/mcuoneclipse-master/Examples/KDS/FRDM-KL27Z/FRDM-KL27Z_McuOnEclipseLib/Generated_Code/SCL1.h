/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : SCL1.h
**     Project     : FRDM-KL27Z_McuOnEclipseLib
**     Processor   : MKL25Z128VLK4
**     Component   : SDK_BitIO
**     Version     : Component 01.022, Driver 01.00, CPU db: 3.00.000
**     Repository  : Legacy User Components
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-03-13, 09:07, # CodeGen: 108
**     Abstract    :
**
**     Settings    :
**          Component name                                 : SCL1
**          SDK                                            : MCUC1
**          GPIO Name                                      : GPIOD
**          PORT Name                                      : PORTD
**          Pin Number                                     : 7
**          Pin Symbol                                     : I2C1_SCL
**          Do Pin Muxing                                  : yes
**          Init Direction                                 : Input
**          Init Value                                     : 0
**     Contents    :
**         GetDir    - bool SCL1_GetDir(void);
**         SetDir    - void SCL1_SetDir(bool Dir);
**         SetInput  - void SCL1_SetInput(void);
**         SetOutput - void SCL1_SetOutput(void);
**         GetVal    - bool SCL1_GetVal(void);
**         PutVal    - void SCL1_PutVal(bool Val);
**         ClrVal    - void SCL1_ClrVal(void);
**         SetVal    - void SCL1_SetVal(void);
**         NegVal    - void SCL1_NegVal(void);
**         Init      - void SCL1_Init(void);
**         Deinit    - void SCL1_Deinit(void);
**
**     * Copyright (c) 2015-2017, Erich Styger
**      * Web:         https://mcuoneclipse.com
**      * SourceForge: https://sourceforge.net/projects/mcuoneclipse
**      * Git:         https://github.com/ErichStyger/McuOnEclipse_PEx
**      * All rights reserved.
**      *
**      * Redistribution and use in source and binary forms, with or without modification,
**      * are permitted provided that the following conditions are met:
**      *
**      * - Redistributions of source code must retain the above copyright notice, this list
**      *   of conditions and the following disclaimer.
**      *
**      * - Redistributions in binary form must reproduce the above copyright notice, this
**      *   list of conditions and the following disclaimer in the documentation and/or
**      *   other materials provided with the distribution.
**      *
**      * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**      * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**      * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**      * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**      * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**      * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**      * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**      * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**      * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**      * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
** ###################################################################*/
/*!
** @file SCL1.h
** @version 01.00
** @brief
**
*/         
/*!
**  @addtogroup SCL1_module SCL1 module documentation
**  @{
*/         

#ifndef __SCL1_H
#define __SCL1_H

/* MODULE SCL1. */
#include "MCUC1.h" /* SDK and API used */
#include "SCL1config.h" /* configuration */

#if MCUC1_CONFIG_SDK_VERSION_USED == MCUC1_CONFIG_SDK_KINETIS_1_3
  #include "fsl_gpio_driver.h"

  /* only GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF and GPIOG are currently supported */
  #define SCL1_GPIO_IDX GPIOD_IDX   /* GPIOD */

  enum SCL1_pinNames{
    I2C1_SCL = GPIO_MAKE_PIN(SCL1_GPIO_IDX, SCL1_CONFIG_PIN_NUMBER),
  };

  extern const gpio_output_pin_user_config_t SCL1_OutputConfig[];
  extern const gpio_input_pin_user_config_t SCL1_InputConfig[];
#endif

void SCL1_Init(void);
/*
** ===================================================================
**     Method      :  SCL1_Init (component SDK_BitIO)
**     Description :
**         Driver initialization method
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void SCL1_ClrVal(void);
/*
** ===================================================================
**     Method      :  SCL1_ClrVal (component SDK_BitIO)
**     Description :
**         Clears the pin value (sets it to a low level)
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void SCL1_SetVal(void);
/*
** ===================================================================
**     Method      :  SCL1_SetVal (component SDK_BitIO)
**     Description :
**         Sets the pin value to a high value.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void SCL1_NegVal(void);
/*
** ===================================================================
**     Method      :  SCL1_NegVal (component SDK_BitIO)
**     Description :
**         Toggles/negates the pin value
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void SCL1_Deinit(void);
/*
** ===================================================================
**     Method      :  SCL1_Deinit (component SDK_BitIO)
**     Description :
**         Driver de-initialization method
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

bool SCL1_GetVal(void);
/*
** ===================================================================
**     Method      :  SCL1_GetVal (component SDK_BitIO)
**     Description :
**         Returns the pin value
**     Parameters  : None
**     Returns     :
**         ---             - Returns the value of the pin:
**                           FALSE/logical level '0' or TRUE/logical
**                           level '1'
** ===================================================================
*/

bool SCL1_GetDir(void);
/*
** ===================================================================
**     Method      :  SCL1_GetDir (component SDK_BitIO)
**     Description :
**         Return the direction of the pin (input/output)
**     Parameters  : None
**     Returns     :
**         ---             - FALSE if port is input, TRUE if port is
**                           output
** ===================================================================
*/

void SCL1_SetDir(bool Dir);
/*
** ===================================================================
**     Method      :  SCL1_SetDir (component SDK_BitIO)
**     Description :
**         Sets the direction of the pin (input or output)
**     Parameters  :
**         NAME            - DESCRIPTION
**         Dir             - FALSE: input, TRUE: output
**     Returns     : Nothing
** ===================================================================
*/

void SCL1_SetInput(void);
/*
** ===================================================================
**     Method      :  SCL1_SetInput (component SDK_BitIO)
**     Description :
**         Sets the pin as input
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void SCL1_SetOutput(void);
/*
** ===================================================================
**     Method      :  SCL1_SetOutput (component SDK_BitIO)
**     Description :
**         Sets the pin as output
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void SCL1_PutVal(bool Val);
/*
** ===================================================================
**     Method      :  SCL1_PutVal (component SDK_BitIO)
**     Description :
**         Sets the pin value
**     Parameters  :
**         NAME            - DESCRIPTION
**         Val             - Value to set. FALSE/logical '0' or
**                           TRUE/logical '1'
**     Returns     : Nothing
** ===================================================================
*/

/* END SCL1. */

#endif
/* ifndef __SCL1_H */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
