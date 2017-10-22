/*
 * Platform_Local.h
 *
 *      Author: tastyger
 */

#ifndef PLATFORM_LOCAL_H_
#define PLATFORM_LOCAL_H_

/* overwrites defines present in Platform.h. Platform.h includes this file first */
#define PL_DO_ACCEL_CONTROL          (0) /* if we use a remote accelerometer as remote controller */
#define PL_DO_LINE_FOLLOWING         (1) /* simple line following */
#define PL_DO_LINE_MAZE              (0) /* maze line solving */
#define PL_DO_FOLLOW_OBSTACLE        (0) /* obstacle following mode */


#endif /* PLATFORM_LOCAL_H_ */
