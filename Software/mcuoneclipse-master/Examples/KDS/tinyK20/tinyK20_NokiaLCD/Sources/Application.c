/*
 * Application.c
 *
 *  Created on: 04.03.2016
 *      Author: Erich Styger
 */

#include "Application.h"
#include "LED1.h"
#include "LCD_LED.h"
#include "WAIT1.h"
#include "PDC1.h"
#include "GDisp1.h"
#include "GFONT1.h"
#include "FDisp1.h"

static void DrawLines(void) {
  int i;
  GDisp1_PixelDim x, y, w, h;

  GDisp1_Clear();
  GDisp1_UpdateFull();

  GDisp1_DrawBox(0, 0, 10, 10, 1, GDisp1_COLOR_BLACK);
  GDisp1_UpdateFull();
  WAIT1_Waitms(500);

  GDisp1_DrawBox(GDisp1_GetWidth()-10, 0, 10, 10, 1, GDisp1_COLOR_BLACK);
  GDisp1_UpdateFull();
  WAIT1_Waitms(500);


  GDisp1_DrawLine(0, 0, GDisp1_GetWidth(), GDisp1_GetHeight(), GDisp1_COLOR_BLACK);
  GDisp1_UpdateFull();
  WAIT1_Waitms(500);
  GDisp1_DrawLine(0, GDisp1_GetHeight(), GDisp1_GetWidth(), 0, GDisp1_COLOR_BLACK);
  GDisp1_UpdateFull();
  WAIT1_Waitms(500);
  for(i=0;i<10;i++) {
    GDisp1_DrawCircle(GDisp1_GetWidth()/2, GDisp1_GetHeight()/2, 5+i*2, GDisp1_COLOR_BLACK);
    GDisp1_UpdateFull();
    WAIT1_Waitms(500);
  }
}

static void DrawFont(void) {
  FDisp1_PixelDim x, y;

  GDisp1_Clear();
  GDisp1_UpdateFull();
  x = 0;
  y = 10;
  FDisp1_WriteString("Hello World!", GDisp1_COLOR_BLACK, &x, &y, GFONT1_GetFont());
  GDisp1_UpdateFull();
  WAIT1_Waitms(500);
  x = 0;
  y += GFONT1_GetBoxHeight();
  FDisp1_WriteString("with Fonts!", GDisp1_COLOR_BLACK, &x, &y, GFONT1_GetFont());
  GDisp1_UpdateFull();
  WAIT1_Waitms(1000);
}

static void DrawText(void) {
  GDisp1_Clear();
  GDisp1_UpdateFull();
  PDC1_WriteLineStr(1, "hello");
  WAIT1_Waitms(500);
  PDC1_WriteLineStr(2, "world");
  WAIT1_Waitms(500);
  PDC1_WriteLineStr(3, "out");
  WAIT1_Waitms(500);
  PDC1_WriteLineStr(4, "there");
  WAIT1_Waitms(500);
  PDC1_WriteLineStr(5, "!!!!!");
  WAIT1_Waitms(500);
}

void APP_Start(void) {
  for(;;) {
    LED1_Neg();

    LCD_LED_On(); /* turn LCD backlight on */
    DrawText();
    LCD_LED_Off(); /* LCD backlight off */
    WAIT1_Waitms(1000);
    LCD_LED_On(); /* turn LCD backlight on */
    DrawLines();
    LCD_LED_On(); /* turn LCD backlight on */
    WAIT1_Waitms(1000);
    LCD_LED_On(); /* turn LCD backlight on */
    DrawFont();
    LCD_LED_On(); /* turn LCD backlight on */
  }
}
