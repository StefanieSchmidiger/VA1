/*
 * NeoConfig.h
 *
 *  Created on: 07.07.2014
 *      Author: tastyger
 */

#ifndef NEOCONFIG_H_
#define NEOCONFIG_H_

#include "PE_Types.h"

#define NEOC_NOF_LANES         (2) /* number of data lanes. For a matrix it is assumed that the number of pixels are divided to the available lanes! */
#define NEOC_NOF_LEDS_IN_LANE  (1*64) /* number of LEDs in each lane */

#define NEOC_NOF_PIXEL   ((NEOC_NOF_LANES)*(NEOC_NOF_LEDS_IN_LANE)) /* number of pixels */

#endif /* NEOCONFIG_H_ */
