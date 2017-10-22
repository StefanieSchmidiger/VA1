/** ###################################################################
**     Filename  : I2C.H
**     Project   : TWR_LCD_JM128
**     Processor : MCF51JM128VLH
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 06.02.2010, 12:17
**     Contents  :
**         User source code
**
** ###################################################################*/

#ifndef __I2C_H
#define __I2C_H

/* MODULE I2C */
#include "PE_Types.h"
#include "Platform.h"

/* accelerometer */
int16_t I2C_GetAccelX(void);
int16_t I2C_GetAccelY(void);
int16_t I2C_GetAccelZ(void);

#if PL_HAS_RUNNER
/* runner */
  #define I2C_RUNNER_I2C_MSG_SIZE  128

  uint8_t I2C_GetRunnerMessage(unsigned char *buf, size_t bufSize);
#endif

uint8_t I2C_GetEKGHeartRate(void);
int16_t I2C_GetEKGRaw(uint8_t index);
bool I2C_GetEKGIsDataReady(void);
void I2C_ResetEKGIsDataReady(void);

/* motor */
int32_t I2C_GetMotorActualSpeed(void);

int32_t I2C_GetMotorDesiredSpeed(void);
void I2C_SetMotorDesiredSpeed(int32_t speed);

int8_t I2C_GetMotorPWMPercent(void);
void I2C_SetMotorPWMPercent(int8_t percent);

int32_t I2C_GetMotorPID_P(void);
void I2C_SetMotorPID_P(int32_t p);

int32_t I2C_GetMotorPID_I(void);
void I2C_SetMotorPID_I(int32_t i);

int32_t I2C_GetMotorPID_D(void);
void I2C_SetMotorPID_D(int32_t d);

/* events generated by the low level driver */
void I2C_OnTxChar(void);
void I2C_OnRxChar(void);
void I2C_OnReadReq(void);
void I2C_OnWriteReq(void);

void I2C_HandleEvent(byte event);

void I2C_ClearBuffers(void);

void I2C_StoreCmd(void);

void I2C_Init(void);

/* END I2C */

#endif

