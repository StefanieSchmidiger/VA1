// wirelessPackageExtractor.h

#ifndef _WIRELESSPACKAGEEXTRACTOR_h
#define _WIRELESSPACKAGEEXTRACTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


/*!
* \fn void wirelessPackageExtractor_TaskEntry(void)
* \brief Task that reads the incoming data from the wireless connections and generates receive acknowledges from it plus sends the valid data to the corresponding devices.
*/
void wirelessPackageExtractor_TaskEntry(void);


#endif

