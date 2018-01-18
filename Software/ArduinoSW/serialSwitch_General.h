#pragma once
#include <Queue.h>



/*! \def TEST_HW_LOOPBACK_ONLY
*  \brief Set to 0 for normal operation, 1 in order to enable loopback on all serial interfaces in order to test the hardware.
*/
#define TEST_HW_LOOPBACK_ONLY						0

/*! \def ENABLE_TEST_DATA_GEN
*  \brief Set to 0 for normal operation, 1 in order to enable the generation of test data output.
*/
#define ENABLE_TEST_DATA_GEN						0

/*! \def GENERATE_DEBUG_OUTPUT
*  \brief Set to 0 for normal operation, 1 in order to print out debug infos (might be less performant).
*/
#define GENERATE_DEBUG_OUTPUT						0

/*! \def GENERATE_DEBUG_OUTPUT
*  \brief If > 0, throughput output generation will be enabled with GENERATE_THROUGHPUT_OUTPUT_INTERVAL.
*/
#define GENERATE_THROUGHPUT_OUTPUT					1






/*! \def LED_GREEN_PIN
*  \brief Pin where the green LED is connected.
*/
#define LED_GREEN_PIN								21

/*! \def LED_ORANGE_PIN
*  \brief Pin where the orange LED is connected.
*/
#define LED_ORANGE_PIN								20

/*! \def LED_RED_PIN
*  \brief Pin where the red LED is connected.
*/
#define LED_RED_PIN									19




/*! \def HW_BUF_IF_DATA_READER_TASK_INTERVAL
*  \brief Interval in [ms] of corresponding task which he will be called. 0 would be no delay - so to run as fast as possible.
*/
#define HW_BUF_IF_DATA_READER_TASK_INTERVAL			1

/*! \def HW_BUF_IF_DEVICE_DATA_WRITER_TASK_INTERVAL
*  \brief Interval in [ms] of corresponding task which he will be called. 0 would be no delay - so to run as fast as possible.
*/
#define HW_BUF_IF_DEVICE_DATA_WRITER_TASK_INTERVAL	1

/*! \def PACKAGE_GENERATOR_TASK_INTERVAL
*  \brief Interval in [ms] of corresponding task which he will be called. 0 would be no delay - so to run as fast as possible.
*/
#define PACKAGE_GENERATOR_TASK_INTERVAL				1

/*! \def WIRELESS_DATA_SEND_HANDLER_INTERVAL
*  \brief Interval in [ms] of corresponding task which he will be called. 0 would be no delay - so to run as fast as possible.
*/
#define WIRELESS_DATA_SEND_HANDLER_INTERVAL			0

/*! \def WIRELESS_ACK_SEND_HANDLER_INTERVAL
*  \brief Interval in [ms] of corresponding task which he will be called. 0 would be no delay - so to run as fast as possible.
*/
#define WIRELESS_ACK_SEND_HANDLER_INTERVAL			0

/*! \def WIRELESS_PACKAGE_EXTRACTOR_INTERVAL
*  \brief Interval in [ms] of corresponding task which he will be called. 0 would be no delay - so to run as fast as possible.
*/
#define WIRELESS_PACKAGE_EXTRACTOR_INTERVAL			0

/*! \def TOGGLE_GREEN_LED_INTERVAL
*  \brief Interval in [ms] of corresponding task which he will be called. 0 would be no delay - so to run as fast as possible.
*/
#define TOGGLE_GREEN_LED_INTERVAL					500

/*! \def TEST_DATA_GENERATOR_INTERVAL
*  \brief Interval in [ms] of corresponding task which he will be called. 0 would be no delay - so to run as fast as possible.
*/
#define TEST_DATA_GENERATOR_INTERVAL				10

/*! \def GENERATE_THROUGHPUT_OUTPUT_INTERVAL
*  \brief Interval in [ms] of corresponding task which he will be called. 0 would be no delay - so to run as fast as possible.
*/
#define GENERATE_THROUGHPUT_OUTPUT_INTERVAL			3000







/*! \def PACK_TYPE_XX
*  \brief Definition for the different available package types.
*/
#define PACK_TYPE_DATA_PACKAGE						(0x01)
#define PACK_TYPE_REC_ACKNOWLEDGE					(0x02)

/*! \def PACK_START
*  \brief Definition of the mark of a beginn of a wireless package.
*/
#define PACK_START									((uint8_t)'\e')

/*! \def PACK_REP
*  \brief If a PACK_START character is within the data, it will be replaced by PACK_REP PACK_START PACK_REP.
*/
#define PACK_REP									((uint8_t)'"')

/*! \def PACK_FILL
*  \brief Filling character if some is needed.
*/
#define PACK_FILL									((uint8_t)' ')



/*! \def NUM_OF_WIRELESS_CONNECTIONS
*  \brief Number of wireless connections.
*/
#define NUM_OF_WIRELESS_CONNECTIONS					(4)

/*! \def NUM_OF_DEVICE_CONNECTIONS
*  \brief Number of device connections.
*/
#define NUM_OF_DEVICE_CONNECTIONS					(4)




/*! \def PACKAGE_HEADER_SIZE
*  \brief Size of wireless package header in bytes - see tWirelessPackage without payload stuff plus sizeof PACK_START
*/
#define PACKAGE_HEADER_SIZE							(11)



/*! \def PACKAGE_MAX_PAYLOAD_SIZE
*  \brief Maximal size of payload.
*/
#define PACKAGE_MAX_PAYLOAD_SIZE					(512)




/*! \struct sWirelessPackage
*  \brief Structure that holds all the required information of a wireless package.
*/
typedef struct sWirelessPackage
{
	uint8_t packType;
	uint8_t devNum;
	uint8_t sessionNr;
	uint32_t sysTime;
	uint16_t payloadSize;
	uint8_t crc8Header;
	uint8_t* payload;
	uint16_t crc16payload;
} tWirelessPackage;




