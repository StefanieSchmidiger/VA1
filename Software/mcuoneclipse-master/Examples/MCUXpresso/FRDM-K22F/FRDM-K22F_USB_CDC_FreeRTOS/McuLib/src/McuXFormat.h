/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : McuXFormat.h
**     Project     : FRDM-K64F_Generator
**     Processor   : MK64FN1M0VLL12
**     Component   : XFormat
**     Version     : Component 01.021, Driver 01.00, CPU db: 3.00.000
**     Repository  : Legacy User Components
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-05-05, 07:35, # CodeGen: 172
**     Abstract    :
**
**     Settings    :
**          Component name                                 : McuXFormat
**          SDK                                            : McuLib
**          Floating Point                                 : no
**     Contents    :
**         xvformat  - unsigned McuXFormat_xvformat(void (*outchar)(void *,char), void *arg, const...
**         xformat   - unsigned McuXFormat_xformat(void (*outchar)(void *,char), void *arg, const...
**         xsprintf  - int McuXFormat_xsprintf(char *buf, const char *fmt, ...);
**         xsnprintf - int McuXFormat_xsnprintf(char *buf, size_t max_len, const char *fmt, ...);
**
**     *  Copyright : (c) Copyright Mario Viara, 2014-2017, https://github.com/MarioViara/xprintfc
**      * Adopted for Processor Expert: Erich Styger
**      * xsnprintf() contributed by Engin Lee
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
** @file McuXFormat.h
** @version 01.00
** @brief
**
*/         
/*!
**  @addtogroup McuXFormat_module McuXFormat module documentation
**  @{
*/         

#ifndef __McuXFormat_H
#define __McuXFormat_H

/* MODULE McuXFormat. */
#include "McuLib.h" /* SDK and API used */
#include "McuXFormatconfig.h" /* configuration */

/* other includes needed */
#include <stdarg.h> /* open argument list support */
#include <stddef.h> /* for size_t */
/* GCC have printf type attribute check. */
#ifdef __GNUC__
  /* inform the GNU compiler about printf() style functions, so the compiler can check the arguments */
  #define McuXFormat_PRINTF_ATTRIBUTE(a,b) __attribute__ ((__format__ (__printf__, a, b)))
#else
  #define McuXFormat_PRINTF_ATTRIBUTE(a,b)
#endif /* __GNUC__ */


unsigned McuXFormat_xformat(void (*outchar)(void *,char), void *arg, const char * fmt, ...) McuXFormat_PRINTF_ATTRIBUTE(3,4);
/*
** ===================================================================
**     Method      :  McuXFormat_xformat (component XFormat)
**     Description :
**         Printf() like function using variable arguments
**     Parameters  :
**         NAME            - DESCRIPTION
**         outchar         - Function pointer to output one new
**                           character
**         arg             - Argument for the output function
**         fmt             - Format options for the list of parameters
**         openArgList     - Open argument list
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

unsigned McuXFormat_xvformat(void (*outchar)(void *,char), void *arg, const char * fmt, va_list args);
/*
** ===================================================================
**     Method      :  McuXFormat_xvformat (component XFormat)
**     Description :
**         Printf() like format function
**     Parameters  :
**         NAME            - DESCRIPTION
**         outchar         - Function pointer to the function
**                           to output one char.
**       * arg             - Argument for the output function.
**         fmt             - Format options for the list of parameters.
**         args            - List of parameters
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

int McuXFormat_xsprintf(char *buf, const char *fmt, ...) McuXFormat_PRINTF_ATTRIBUTE(2,3);
/*
** ===================================================================
**     Method      :  McuXFormat_xsprintf (component XFormat)
**     Description :
**         sprintf() like function
**     Parameters  :
**         NAME            - DESCRIPTION
**       * buf             - Pointer to buffer to be written
**       * fmt             - Pointer to formatting string
**         argList         - Open Argument List
**     Returns     :
**         ---             - number of characters written, negative for
**                           error case
** ===================================================================
*/

int McuXFormat_xsnprintf(char *buf, size_t max_len, const char *fmt, ...) McuXFormat_PRINTF_ATTRIBUTE(3,4);
/*
** ===================================================================
**     Method      :  McuXFormat_xsnprintf (component XFormat)
**     Description :
**         snprintf() like function, returns the number of characters
**         written, negative in case of error.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * buf             - Pointer to buffer to be written
**         max_len         - size of output buffer (in size)
**       * fmt             - Pointer to formatting string
**         argList         - Open Argument List
**     Returns     :
**         ---             - number of characters written, negative for
**                           error case
** ===================================================================
*/

/* END McuXFormat. */

#endif
/* ifndef __McuXFormat_H */
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
