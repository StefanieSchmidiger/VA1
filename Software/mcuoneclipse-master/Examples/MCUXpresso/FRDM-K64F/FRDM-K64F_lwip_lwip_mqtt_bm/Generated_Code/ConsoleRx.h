/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : ConsoleRx.h
**     Project     : FRDM-K64F_lwip_mqtt_bm
**     Processor   : MK64FN1M0VLL12
**     Component   : RingBuffer
**     Version     : Component 01.051, Driver 01.00, CPU db: 3.00.000
**     Repository  : Legacy User Components
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-05-26, 06:31, # CodeGen: 39
**     Abstract    :
**         This component implements a ring buffer for different integer data type.
**     Settings    :
**          Component name                                 : ConsoleRx
**          SDK                                            : MCUC1
**          Reentrant                                      : yes
**          Critical Section                               : CS1
**          Buffer Elements                                : 64
**          Element Size                                   : 1 Byte
**     Contents    :
**         Clear           - void ConsoleRx_Clear(void);
**         Put             - uint8_t ConsoleRx_Put(ConsoleRx_ElementType elem);
**         Get             - uint8_t ConsoleRx_Get(ConsoleRx_ElementType *elemP);
**         Peek            - uint8_t ConsoleRx_Peek(ConsoleRx_BufSizeType index, ConsoleRx_ElementType...
**         Update          - uint8_t ConsoleRx_Update(ConsoleRx_BufSizeType index, ConsoleRx_ElementType...
**         Putn            - uint8_t ConsoleRx_Putn(ConsoleRx_ElementType *elem, ConsoleRx_BufSizeType nof);
**         Getn            - uint8_t ConsoleRx_Getn(ConsoleRx_ElementType *buf, ConsoleRx_BufSizeType nof);
**         Compare         - uint8_t ConsoleRx_Compare(ConsoleRx_BufSizeType index, ConsoleRx_ElementType...
**         Delete          - uint8_t ConsoleRx_Delete(void);
**         NofElements     - ConsoleRx_BufSizeType ConsoleRx_NofElements(void);
**         NofFreeElements - ConsoleRx_BufSizeType ConsoleRx_NofFreeElements(void);
**         Deinit          - void ConsoleRx_Deinit(void);
**         Init            - void ConsoleRx_Init(void);
**
**     * Copyright (c) 2014-2017, Erich Styger
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
** @file ConsoleRx.h
** @version 01.00
** @brief
**         This component implements a ring buffer for different integer data type.
*/         
/*!
**  @addtogroup ConsoleRx_module ConsoleRx module documentation
**  @{
*/         

#ifndef __ConsoleRx_H
#define __ConsoleRx_H

/* MODULE ConsoleRx. */
#include "MCUC1.h" /* SDK and API used */
#include "ConsoleRxconfig.h" /* configuration */

/* Include inherited components */
#include "MCUC1.h"
#include "CS1.h"


#ifdef __cplusplus
extern "C" {
#endif

#if ConsoleRx_CONFIG_ELEM_SIZE==1
  typedef uint8_t ConsoleRx_ElementType; /* type of single element */
#elif ConsoleRx_CONFIG_ELEM_SIZE==2
  typedef uint16_t ConsoleRx_ElementType; /* type of single element */
#elif ConsoleRx_CONFIG_ELEM_SIZE==4
  typedef uint32_t ConsoleRx_ElementType; /* type of single element */
#else
  #error "illegal element type size in properties"
#endif
#if ConsoleRx_CONFIG_BUF_SIZE<256
  typedef uint8_t ConsoleRx_BufSizeType; /* up to 255 elements (index 0x00..0xff) */
#else
  typedef uint16_t ConsoleRx_BufSizeType; /* more than 255 elements, up to 2^16 */
#endif

uint8_t ConsoleRx_Put(ConsoleRx_ElementType elem);
/*
** ===================================================================
**     Method      :  ConsoleRx_Put (component RingBuffer)
**     Description :
**         Puts a new element into the buffer
**     Parameters  :
**         NAME            - DESCRIPTION
**         elem            - New element to be put into the buffer
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

uint8_t ConsoleRx_Get(ConsoleRx_ElementType *elemP);
/*
** ===================================================================
**     Method      :  ConsoleRx_Get (component RingBuffer)
**     Description :
**         Removes an element from the buffer
**     Parameters  :
**         NAME            - DESCRIPTION
**       * elemP           - Pointer to where to store the received
**                           element
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

ConsoleRx_BufSizeType ConsoleRx_NofElements(void);
/*
** ===================================================================
**     Method      :  ConsoleRx_NofElements (component RingBuffer)
**     Description :
**         Returns the actual number of elements in the buffer.
**     Parameters  : None
**     Returns     :
**         ---             - Number of elements in the buffer.
** ===================================================================
*/

void ConsoleRx_Init(void);
/*
** ===================================================================
**     Method      :  ConsoleRx_Init (component RingBuffer)
**     Description :
**         Initializes the data structure
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

ConsoleRx_BufSizeType ConsoleRx_NofFreeElements(void);
/*
** ===================================================================
**     Method      :  ConsoleRx_NofFreeElements (component RingBuffer)
**     Description :
**         Returns the actual number of free elements/space in the
**         buffer.
**     Parameters  : None
**     Returns     :
**         ---             - Number of elements in the buffer.
** ===================================================================
*/

void ConsoleRx_Clear(void);
/*
** ===================================================================
**     Method      :  ConsoleRx_Clear (component RingBuffer)
**     Description :
**         Clear (empty) the ring buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

uint8_t ConsoleRx_Peek(ConsoleRx_BufSizeType index, ConsoleRx_ElementType *elemP);
/*
** ===================================================================
**     Method      :  ConsoleRx_Peek (component RingBuffer)
**     Description :
**         Returns an element of the buffer without removiing it.
**     Parameters  :
**         NAME            - DESCRIPTION
**         index           - Index of element. 0 peeks the top
**                           element, 1 the next, and so on.
**       * elemP           - Pointer to where to store the received
**                           element
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

#define ConsoleRx_Deinit() \
   /* nothing to deinitialize */
/*
** ===================================================================
**     Method      :  ConsoleRx_Deinit (component RingBuffer)
**     Description :
**         Driver de-initialization
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

uint8_t ConsoleRx_Delete(void);
/*
** ===================================================================
**     Method      :  ConsoleRx_Delete (component RingBuffer)
**     Description :
**         Removes an element from the buffer
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

uint8_t ConsoleRx_Putn(ConsoleRx_ElementType *elem, ConsoleRx_BufSizeType nof);
/*
** ===================================================================
**     Method      :  ConsoleRx_Putn (component RingBuffer)
**     Description :
**         Put a number new element into the buffer.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * elem            - Pointer to new elements to be put into
**                           the buffer
**         nof             - number of elements
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

uint8_t ConsoleRx_Compare(ConsoleRx_BufSizeType index, ConsoleRx_ElementType *elemP, ConsoleRx_BufSizeType nof);
/*
** ===================================================================
**     Method      :  ConsoleRx_Compare (component RingBuffer)
**     Description :
**         Compares the elements in the buffer.
**     Parameters  :
**         NAME            - DESCRIPTION
**         index           - Index of element. 0 peeks the top
**                           element, 1 the next, and so on.
**       * elemP           - Pointer to elements to compare with
**         nof             - number of elements to compare
**     Returns     :
**         ---             - zero if elements are the same, -1 otherwise
** ===================================================================
*/

uint8_t ConsoleRx_Getn(ConsoleRx_ElementType *buf, ConsoleRx_BufSizeType nof);
/*
** ===================================================================
**     Method      :  ConsoleRx_Getn (component RingBuffer)
**     Description :
**         Get a number elements into a buffer.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * buf             - Pointer to buffer where to store the
**                           elements
**         nof             - number of elements
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

uint8_t ConsoleRx_Update(ConsoleRx_BufSizeType index, ConsoleRx_ElementType *elemP);
/*
** ===================================================================
**     Method      :  ConsoleRx_Update (component RingBuffer)
**     Description :
**         Updates the data of an element.
**     Parameters  :
**         NAME            - DESCRIPTION
**         index           - Index of element. 0 peeks the top
**                           element, 1 the next, and so on.
**       * elemP           - Pointer to where to store the received
**                           element
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

/* END ConsoleRx. */

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif
/* ifndef __ConsoleRx_H */
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
