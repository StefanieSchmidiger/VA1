/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : McuArmTools.c
**     Project     : FRDM-K64F_Generator
**     Processor   : MK64FN1M0VLL12
**     Component   : KinetisTools
**     Version     : Component 01.038, Driver 01.00, CPU db: 3.00.000
**     Repository  : Legacy User Components
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-08-18, 14:15, # CodeGen: 228
**     Abstract    :
**
**     Settings    :
**          Component name                                 : McuArmTools
**          SDK                                            : McuLib
**          Utility                                        : McuUtility
**          Shell                                          : Enabled
**            Shell                                        : McuShell
**     Contents    :
**         SoftwareReset          - void McuArmTools_SoftwareReset(void);
**         UIDGet                 - uint8_t McuArmTools_UIDGet(McuArmTools_UID *uid);
**         UIDSame                - bool McuArmTools_UIDSame(const McuArmTools_UID *src, const McuArmTools_UID...
**         UIDtoString            - uint8_t McuArmTools_UIDtoString(const McuArmTools_UID *uid, uint8_t *buf,...
**         GetKinetisFamilyString - McuArmTools_ConstCharPtr McuArmTools_GetKinetisFamilyString(void);
**         GetPC                  - void* McuArmTools_GetPC(void);
**         GetSP                  - void* McuArmTools_GetSP(void);
**         SetPSP                 - void McuArmTools_SetPSP(void *setval);
**         SetLR                  - void McuArmTools_SetLR(uint32_t setval);
**         InitCycleCounter       - void McuArmTools_InitCycleCounter(void);
**         ResetCycleCounter      - void McuArmTools_ResetCycleCounter(void);
**         EnableCycleCounter     - void McuArmTools_EnableCycleCounter(void);
**         DisableCycleCounter    - void McuArmTools_DisableCycleCounter(void);
**         GetCycleCounter        - uint32_t McuArmTools_GetCycleCounter(void);
**         ParseCommand           - uint8_t McuArmTools_ParseCommand(const unsigned char* cmd, bool *handled,...
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
** @file McuArmTools.c
** @version 01.00
** @brief
**
*/         
/*!
**  @addtogroup McuArmTools_module McuArmTools module documentation
**  @{
*/         

/* MODULE McuArmTools. */

#include "McuArmTools.h"
#include "McuUtility.h" /* various utility functions */
#if McuLib_CONFIG_NXP_SDK_2_0_USED
  #include "fsl_sim.h" /* system integration module */
#elif McuLib_CONFIG_SDK_VERSION_USED==McuLib_CONFIG_SDK_KINETIS_1_3
  #include "Cpu.h" /* include CPU related interfaces and defines */
#endif

#if McuLib_CONFIG_CORTEX_M==4
static const unsigned char *KinetisM4FamilyStrings[] =
{ /* FAMID (3 bits) are used as index */
  (const unsigned char *)"K10 or K12 Family",          /* 000 */
  (const unsigned char *)"K20 or K22 Family",          /* 001 */
  (const unsigned char *)"K30, K11 or K61 Family",     /* 010 */
  (const unsigned char *)"K40 or K21 Family",          /* 011 */
  (const unsigned char *)"K60 or K62 Family",          /* 100 */
  (const unsigned char *)"K70 Family",                 /* 101 */
  (const unsigned char *)"Reserved",                   /* 110 */
  (const unsigned char *)"Reserved"                    /* 111 */
};
#endif

#if McuLib_CONFIG_CORTEX_M==0
static const unsigned char *KinetisM0FamilyStrings[] =
{ /* FAMID (3 bits) are used as index */
  (const unsigned char *)"KL0x",          /* 0000 */
  (const unsigned char *)"KL1x",          /* 0001 */
  (const unsigned char *)"KL2x",          /* 0010 */
  (const unsigned char *)"KL3x",          /* 0011 */
  (const unsigned char *)"KL4x",          /* 0100 */
  (const unsigned char *)"Reserved",      /* 0101 */
  (const unsigned char *)"Reserved",      /* 0110 */
  (const unsigned char *)"Reserved"       /* 0111 */
};
#endif

#if McuArmTools_CONFIG_PARSE_COMMAND_ENABLED
static uint8_t PrintStatus(const McuShell_StdIOType *io)
{
  uint8_t buf[1+(16*5)+1+1]; /* "{0xAA,...0xBB}" */
  uint8_t res;
  McuArmTools_UID uid;

  McuShell_SendStatusStr((unsigned char*)"McuArmTools", (unsigned char*)"\r\n", io->stdOut);
  res = McuArmTools_UIDGet(&uid);
  if (res==ERR_OK) {
    res = McuArmTools_UIDtoString(&uid, buf, sizeof(buf));
  }
  if (res!=ERR_OK) {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"ERROR\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  UID", buf, io->stdOut);
  McuShell_SendStr((unsigned char*)"\r\n", io->stdOut);

  McuShell_SendStatusStr((unsigned char*)"  Family", (uint8_t*)McuArmTools_GetKinetisFamilyString(), io->stdOut);
  McuShell_SendStr((unsigned char*)"\r\n", io->stdOut);
  return ERR_OK;
}
#endif

#if McuArmTools_CONFIG_PARSE_COMMAND_ENABLED
static uint8_t PrintHelp(const McuShell_StdIOType *io)
{
  McuShell_SendHelpStr((unsigned char*)"McuArmTools", (unsigned char*)"Group of McuArmTools commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  reset", (unsigned char*)"Performs a software reset\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  return ERR_OK;
}
#endif

/*
** ===================================================================
**     Method      :  McuArmTools_SoftwareReset (component KinetisTools)
**     Description :
**         Performs a reset of the device
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void McuArmTools_SoftwareReset(void)
{
  /* Generic way to request a reset from software for ARM Cortex */
  /* See https://community.freescale.com/thread/99740
     To write to this register, you must write 0x5FA to the VECTKEY field, otherwise the processor ignores the write.
     SYSRESETREQ will cause a system reset asynchronously, so need to wait afterwards.
   */
#if McuLib_CONFIG_CPU_IS_KINETIS
#if McuLib_CONFIG_PEX_SDK_USED
  SCB_AIRCR = SCB_AIRCR_VECTKEY(0x5FA) | SCB_AIRCR_SYSRESETREQ_MASK;
#else
  SCB->AIRCR = (0x5FA<<SCB_AIRCR_VECTKEY_Pos)|SCB_AIRCR_SYSRESETREQ_Msk;
#endif
#endif
  for(;;) {
    /* wait until reset */
  }
}

/*
** ===================================================================
**     Method      :  McuArmTools_UIDGet (component KinetisTools)
**     Description :
**         Return the 128bit UID of the device
**     Parameters  :
**         NAME            - DESCRIPTION
**       * uid             - Pointer to 
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
/*!
 * \brief Return the 80bit UID of the device
 * \param uid Pointer to the buffer where to store the UID
 * \return Error code, ERR_OK if everything is ok.
 */
uint8_t McuArmTools_UIDGet(McuArmTools_UID *uid)
{
#if McuLib_CONFIG_CPU_IS_KINETIS
#if McuLib_CONFIG_NXP_SDK_2_0_USED
  sim_uid_t tmp;
  int i, j;

  SIM_GetUniqueId(&tmp);
  /* init */
  for(i=0;i<sizeof(McuArmTools_UID);i++) {
    uid->id[i] = 0;
  }
  if (sizeof(sim_uid_t)>sizeof(McuArmTools_UID)) {
    return ERR_OVERFLOW;
  }
  /* copy into our own structure, data is right justified */
  for(i=0,j=sizeof(McuArmTools_UID)-sizeof(sim_uid_t);i<sizeof(sim_uid_t)&&i<sizeof(McuArmTools_UID);i++,j++) {
    uid->id[j] = ((uint8_t*)&tmp)[i];
  }
#else
#ifdef SIM_UIDMH /* 80 or 128 bit UUID: SIM_UIDMH, SIM_UIDML and SIM_UIDL */
#ifdef SIM_UIDH
  uid->id[0] = (SIM_UIDH>>24)&0xff;
  uid->id[1] = (SIM_UIDH>>16)&0xff;
  uid->id[2] = (SIM_UIDH>>8)&0xff;
  uid->id[3] = SIM_UIDH&0xff;
#else
  uid->id[0] = 0;
  uid->id[1] = 0;
  uid->id[2] = 0;
  uid->id[3] = 0;
#endif
  uid->id[4] = (SIM_UIDMH>>24)&0xff;
  uid->id[5] = (SIM_UIDMH>>16)&0xff;
  uid->id[6] = (SIM_UIDMH>>8)&0xff;
  uid->id[7] = SIM_UIDMH&0xff;

  uid->id[8] = (SIM_UIDML>>24)&0xff;
  uid->id[9] = (SIM_UIDML>>16)&0xff;
  uid->id[10] = (SIM_UIDML>>8)&0xff;
  uid->id[11] = SIM_UIDML&0xff;

  uid->id[12] = (SIM_UIDL>>24)&0xff;
  uid->id[13] = (SIM_UIDL>>16)&0xff;
  uid->id[14] = (SIM_UIDL>>8)&0xff;
  uid->id[15] = SIM_UIDL&0xff;
#elif defined(SIM_UUIDMH) /* KE06Z: SIM_UUIDMH, SIM_UUIDML and SIM_UUIDL */
  uid->id[0] = 0;
  uid->id[1] = 0;
  uid->id[2] = 0;
  uid->id[3] = 0;
  uid->id[4] = 0;
  uid->id[5] = 0;
  uid->id[6] = (SIM_UUIDMH>>8)&0xff;
  uid->id[7] = SIM_UUIDMH&0xff;

  uid->id[8] = (SIM_UUIDML>>24)&0xff;
  uid->id[9] = (SIM_UUIDML>>16)&0xff;
  uid->id[10] = (SIM_UUIDML>>8)&0xff;
  uid->id[11] = SIM_UUIDML&0xff;

  uid->id[12] = (SIM_UUIDL>>24)&0xff;
  uid->id[13] = (SIM_UUIDL>>16)&0xff;
  uid->id[14] = (SIM_UUIDL>>8)&0xff;
  uid->id[15] = SIM_UUIDL&0xff;
#else /* some devices like the KE02Z only have 64bit UUID: only SIM_UUIDH and SIM_UUIDL */
  uid->id[0] = 0;
  uid->id[1] = 0;
  uid->id[2] = 0;
  uid->id[3] = 0;
  uid->id[4] = 0;
  uid->id[5] = 0;
  uid->id[6] = 0;
  uid->id[7] = 0;
  uid->id[8] = (SIM_UUIDH>>24)&0xff;
  uid->id[9] = (SIM_UUIDH>>16)&0xff;
  uid->id[10] = (SIM_UUIDH>>8)&0xff;
  uid->id[11] = SIM_UUIDH&0xff;

  uid->id[12] = (SIM_UUIDL>>24)&0xff;
  uid->id[13] = (SIM_UUIDL>>16)&0xff;
  uid->id[14] = (SIM_UUIDL>>8)&0xff;
  uid->id[15] = SIM_UUIDL&0xff;
#endif
#endif /* SDK V2.0 */
  return ERR_OK;
#else
  return ERR_FAILED;
#endif
}

/*
** ===================================================================
**     Method      :  McuArmTools_UIDSame (component KinetisTools)
**     Description :
**         Compares two UID
**     Parameters  :
**         NAME            - DESCRIPTION
**       * src             - Pointer to 
**         Variable_1      - 
**     Returns     :
**         ---             - TRUE if the same, FALSE otherwise
** ===================================================================
*/
/*!
 * \brief Compares two UID
 * \param src One UID
 * \param dst The other UID
 * \return TRUE if the two UID's are the same
 */
bool McuArmTools_UIDSame(const McuArmTools_UID *src, const McuArmTools_UID *dst)
{
  unsigned int i;

  for(i=0; i<sizeof(McuArmTools_UID); i++) {
    if (src->id[i]!=dst->id[i]) {
      return FALSE; /* no match */
    }
  }
  return TRUE;
}

/*
** ===================================================================
**     Method      :  McuArmTools_UIDtoString (component KinetisTools)
**     Description :
**         Returns the value of the UID as string
**     Parameters  :
**         NAME            - DESCRIPTION
**         uid             - 
**       * buf             - Pointer to 
**         bufSize         - 
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
/*!
 * \brief Transforms the 80bit UID into a string
 * \param id Pointer to the buffer where to store the string
 * \param bufSize Size of buffer in bytes
 * \return Error code, ERR_OK if everything is ok.
 */
uint8_t McuArmTools_UIDtoString(const McuArmTools_UID *uid, uint8_t *buf, size_t bufSize)
{
  unsigned int i;

  McuUtility_strcpy(buf, bufSize, (unsigned char*)"{");
  for(i=0;i<sizeof(McuArmTools_UID);i++) {
    McuUtility_strcat(buf, bufSize, (unsigned char*)"0x");
    McuUtility_strcatNum8Hex(buf, bufSize, uid->id[i]);
    if (i<sizeof(McuArmTools_UID)-1) {
      McuUtility_strcat(buf, bufSize, (unsigned char*)",");
    }
  }
  McuUtility_strcat(buf, bufSize, (unsigned char*)"}");
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  McuArmTools_ParseCommand (component KinetisTools)
**     Description :
**         Shell Command Line parser. Method is only available if Shell
**         is enabled in the component properties.
**     Parameters  :
**         NAME            - DESCRIPTION
**         cmd             - Pointer to command string
**       * handled         - Pointer to variable which tells if
**                           the command has been handled or not
**       * io              - Pointer to I/O structure
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
#if McuArmTools_CONFIG_PARSE_COMMAND_ENABLED
uint8_t McuArmTools_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io)
{
  uint8_t res = ERR_OK;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP) == 0
    || McuUtility_strcmp((char*)cmd, "McuArmTools help") == 0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if (   (McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0)
             || (McuUtility_strcmp((char*)cmd, "McuArmTools status") == 0)
            )
  {
    *handled = TRUE;
    res = PrintStatus(io);
  } else if (McuUtility_strcmp((char*)cmd, "McuArmTools reset") == 0) {
    *handled = TRUE;
    McuArmTools_SoftwareReset(); /* will perform RESET and does NOT return here! */
  }
  return res;
}
#endif

/*
** ===================================================================
**     Method      :  McuArmTools_GetKinetisFamilyString (component KinetisTools)
**     Description :
**         Determines the Kinetis Familiy based on SIM_SDID register
**     Parameters  : None
**     Returns     :
**         ---             - String describing the Kinetis Family
** ===================================================================
*/
McuArmTools_ConstCharPtr McuArmTools_GetKinetisFamilyString(void)
{
#if McuLib_CONFIG_CPU_IS_KINETIS
#if McuLib_CONFIG_CORTEX_M==0
  #ifdef SIM_SDID /* normal Kinetis define this */
    int32_t val;

    val = (SIM_SDID>>28)&0x3; /* bits 30..28 */
    if (val>=0 && val<=(int32_t)(sizeof(KinetisM0FamilyStrings)/sizeof(KinetisM0FamilyStrings[0]))) {
      return KinetisM0FamilyStrings[val];
    } else {
      return (McuArmTools_ConstCharPtr)"M0 Family ID out of bounds!";
    }
  #elif defined(SIM_SRSID_FAMID) /* MKE02Z4 defines this, hopefully all other KE too... */
    return "KE0x Family"; /* 0000 only KE0x supported */
  #elif defined(SIM_SDID_FAMID)
    int32_t val;

    val = ((SIM->SDID)>>28)&0xF; /* bits 31..28 */
    if (val>=0 && val<=(int32_t)(sizeof(KinetisM0FamilyStrings)/sizeof(KinetisM0FamilyStrings[0]))) {
      return KinetisM0FamilyStrings[val];
    } else {
      return (McuArmTools_ConstCharPtr)"M0 Family ID out of bounds!";
    }
  #else
    #error "Unknown architecture!"
    return (McuArmTools_ConstCharPtr)"ERROR";
  #endif
#elif McuLib_CONFIG_CORTEX_M==4
  int32_t val;

  val = (SIM_SDID>>4)&0x3; /* bits 6..4 */
  if (val>=0 && val<=(int32_t)(sizeof(KinetisM4FamilyStrings)/sizeof(KinetisM4FamilyStrings[0]))) {
    return KinetisM4FamilyStrings[val];
  } else {
    return (McuArmTools_ConstCharPtr)"M4 Family ID out of bounds!";
  }
#elif McuLib_CONFIG_CORTEX_M==7
  return (McuArmTools_ConstCharPtr)"Cortex-M7";
#else
  #error "Unknown architecture!"
  return (McuArmTools_ConstCharPtr)"ERROR";
#endif
#else
  return (McuArmTools_ConstCharPtr)"NOT KINETIS";
#endif
}

/*
** ===================================================================
**     Method      :  McuArmTools_GetPC (component KinetisTools)
**     Description :
**         returns the program counter
**     Parameters  : None
**     Returns     :
**         ---             - program counter
** ===================================================================
*/
void* McuArmTools_GetPC(void)
{
#ifdef __GNUC__
  void *pc;

  __asm__ __volatile__ ("mov %0, pc" : "=r"(pc));
  return pc;
#else
  #warning "only for GCC"
  return NULL;
#endif
}

/*
** ===================================================================
**     Method      :  McuArmTools_GetSP (component KinetisTools)
**     Description :
**         returns the stack pointer
**     Parameters  : None
**     Returns     :
**         ---             - stack pointer
** ===================================================================
*/
void* McuArmTools_GetSP(void)
{
#ifdef __GNUC__
  void *sp;

  __asm__ __volatile__ ("mrs %0, msp" : "=r"(sp));
  return sp;
#else
  #warning "only for GCC"
  return NULL;
#endif
}

/*
** ===================================================================
**     Method      :  McuArmTools_SetPSP (component KinetisTools)
**     Description :
**         sets the process stack pointer
**     Parameters  :
**         NAME            - DESCRIPTION
**         setval          - new PSP value
**     Returns     : Nothing
** ===================================================================
*/
void McuArmTools_SetPSP(void *setval)
{
#ifdef __GNUC__
  __asm__ volatile ("msr psp, %[value]\n\t""dmb\n\t""dsb\n\t""isb\n\t"::[value]"r"(setval):);
  __asm__ volatile ("" ::: "memory");
#else
  #warning "only for GCC implemented"
#endif
}

/*
** ===================================================================
**     Method      :  McuArmTools_SetLR (component KinetisTools)
**     Description :
**         Sets the link register
**     Parameters  :
**         NAME            - DESCRIPTION
**         setval          - new LR value
**     Returns     : Nothing
** ===================================================================
*/
void McuArmTools_SetLR(uint32_t setval)
{
#ifdef __GNUC__
  __asm__ volatile ("mov lr, %[value]\n\t"::[value]"r"(setval):);
  __asm__ volatile ("" ::: "memory");
#else
  #warning "only for GCC"
#endif
}

/*
** ===================================================================
**     Method      :  McuArmTools_InitCycleCounter (component KinetisTools)
**     Description :
**         Initializes the cycle counter, available if the core has a
**         DWT (Data Watchpoint and Trace) unit, usually present on
**         M3/M4/M7
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/**
void McuArmTools_InitCycleCounter(void)
{
  ** Implemented as macro in header file
}
*/

/*
** ===================================================================
**     Method      :  McuArmTools_ResetCycleCounter (component KinetisTools)
**     Description :
**         Reset the cycle counter (set it to zero)
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/**
void McuArmTools_ResetCycleCounter(void)
{
  ** Implemented as macro in header file
}
*/

/*
** ===================================================================
**     Method      :  McuArmTools_EnableCycleCounter (component KinetisTools)
**     Description :
**         Enables counting the cycles.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/**
void McuArmTools_EnableCycleCounter(void)
{
  ** Implemented as macro in header file
}
*/

/*
** ===================================================================
**     Method      :  McuArmTools_DisableCycleCounter (component KinetisTools)
**     Description :
**         Disables the cycle counter.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/**
void McuArmTools_DisableCycleCounter(void)
{
  ** Implemented as macro in header file
}
*/

/*
** ===================================================================
**     Method      :  McuArmTools_GetCycleCounter (component KinetisTools)
**     Description :
**         Return the current cycle counter value
**     Parameters  : None
**     Returns     :
**         ---             - cycle counter
** ===================================================================
*/
/**
uint32_t McuArmTools_GetCycleCounter(void)
{
  ** Implemented as macro in header file
}
*/

/* END McuArmTools. */

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
