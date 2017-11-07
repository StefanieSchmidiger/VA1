#include "FRTOS.h" // task
#include "Platform.h" // PL_HAS_TEENSY_LED
#if PL_HAS_TEENSY_LED
	#include "LedTeensy.h"
#else
	#include "LedGreen.h"
#endif
void blinky_TaskEntry(void *p)
{
  TickType_t xLastWakeTime;
  const TickType_t xDelayMs = pdMS_TO_TICKS(1000); // 1sek
  for(;;)
  {
	xLastWakeTime = xTaskGetTickCount(); /* Initialise the xLastWakeTime variable with the current time. */
	#if PL_HAS_TEENSY_LED
    LedTeensy_Neg();
	#else
    LedGreen_Neg();
	#endif
    vTaskDelayUntil( &xLastWakeTime, xDelayMs ); /* Wait for the next cycle */
  }
}
