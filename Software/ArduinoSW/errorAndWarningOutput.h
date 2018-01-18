#pragma once

#include "serialSwitch_General.h"



/*!
* \fn inline void showInfo(const char* funct, const char* hint)
* \brief Prints an info string via the serial interface of the Teensy.
* \param funct: Function where this warning is called. Simpy put in __FUNCTION__, the compiler will do the rest.
* \param hint: Info string that should be printed out.
*/
inline void showInfo(const char* funct, const char* hint)
{
	Serial.print("INFO from function ");
	Serial.print(funct);
	Serial.print(": ");
	Serial.println(hint);
}


/*!
* \fn inline void showWarning(const char* hint)
* \brief Shows a warning by a printout over USB of the teensy plus enable the warning LED.
* \param funct: Function where this warning is called. Simpy put in __FUNCTION__, the compiler will do the rest.
* \param hint: Hint that should be printed out in order to describe the warning.
*/
inline void showWarning(const char* funct, const char* hint)
{
	Serial.print("WARNING in function ");
	Serial.print(funct);
	Serial.print(": ");
	Serial.println(hint);
	/* enable orange LED if not already enabled */
	digitalWrite(LED_ORANGE_PIN, HIGH);
}


/*!
* \fn inline void showError(const char* hint)
* \brief Shows an error by a printout over USB of the teensy plus enable the error LED.
* \param funct: Function where this warning is called. Simpy put in __FUNCTION__, the compiler will do the rest.
* \param hint: Hint that should be printed out in order to describe the warning.
*/
inline void showError(const char* funct, const char* hint)
{
	Serial.print("ERROR in function ");
	Serial.print(funct);
	Serial.print(": ");
	Serial.println(hint);
	/* enable red LED if not already enabled */
	digitalWrite(LED_RED_PIN, HIGH);
}


