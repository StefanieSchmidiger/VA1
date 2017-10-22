/*
 * Application.c
 *
 *  Created on: 04.03.2016
 *      Author: Erich Styger
 */

#include "Application.h"
#include "VL6180X.h"
#include "LED1.h"
#include "WAIT1.h"
#include "CLS1.h"

void APP_Start(void) {
  uint8_t val=0;
  int16_t range;
  uint8_t res;
  uint16_t ambient;
  float lux;
  CLS1_ConstStdIOType *io = CLS1_GetStdio();

  VL_Init(); /* initialize sensor driver */
  res = VL_InitAndConfigureDevice(VL6180X_DEFAULT_I2C_ADDRESS);
  if (res!=ERR_OK) {
    CLS1_SendStr("ERROR: Failed init of TOF device: ", io->stdErr);
    CLS1_SendNum8u(VL6180X_DEFAULT_I2C_ADDRESS, io->stdErr);
    CLS1_SendStr("\r\n", io->stdErr);
  }
  for(;;) {
    res = VL_ReadRangeSingle(VL6180X_DEFAULT_I2C_ADDRESS, &range);
    if (res!=ERR_OK) {
      CLS1_SendStr("ERROR Range: ", io->stdErr);
      CLS1_SendNum8u(res, io->stdErr);
    } else {
      CLS1_SendStr("Range: ", io->stdOut);
      CLS1_SendNum8u(range, io->stdOut);
    }
    res = VL_ReadAmbientSingle(VL6180X_DEFAULT_I2C_ADDRESS, &ambient);
    if (res!=ERR_OK) {
      CLS1_SendStr(" ERROR Ambient: ", io->stdErr);
      CLS1_SendNum8u(res, io->stdErr);
    } else {
      CLS1_SendStr(" Ambient: ", io->stdOut);
      CLS1_SendNum16u(ambient, io->stdOut);
    }

    res = VL6180X_readLux(VL6180X_DEFAULT_I2C_ADDRESS, VL6180X_ALS_GAIN_1, &lux);
    if (res!=ERR_OK) {
      CLS1_SendStr(" ERROR Lux: ", io->stdErr);
      CLS1_SendNum8u(res, io->stdErr);
    } else {
      CLS1_printf(" Lux: %f", lux);
    }
    CLS1_SendStr("\r\n", io->stdOut);

    LED1_Neg();
    WAIT1_Waitms(500);
  }
}
