#pragma once


/*! \def BAUD_RATES_WIRELESS_CONN
*  \brief Configuration of baud rates on wireless side from 0 to 3.
* Regarding the supported baud rates see implementation of hwBufIfConfigureBaudRate in hwBufferInterface.cpp
*/
#define BAUD_RATES_WIRELESS_CONN			{57600, 57600, 57600, 57600}

/*! \def BAUD_RATES_DEVICE_CONN
*  \brief Configuration of baud rates on wireless side from 0 to 3.
* Regarding the supported baud rates see implementation of hwBufIfConfigureBaudRate in hwBufferInterface.cpp
*/
#define BAUD_RATES_DEVICE_CONN				{57600, 57600, 57600, 57600}




/*! \def PRIO_WIRELESS_CONN_DEV_X
*  \brief Priority of the differ+ent wireless connections from the viewpoint of a single device.
* 0: Wireless connection is not used; 1: Highes priority; 2: Second priority, ..
*/
#define PRIO_WIRELESS_CONN_DEV_0			{1, 0, 0, 0}
#define PRIO_WIRELESS_CONN_DEV_1			{0, 1, 0, 0}
#define PRIO_WIRELESS_CONN_DEV_2			{0, 0, 1, 0}
#define PRIO_WIRELESS_CONN_DEV_3			{0, 0, 0, 1}

/*! \def SEND_CNT_WIRELESS_CONN_DEV_X
*  \brief Number of times a package should be tried to be sent over a single wireless connection.
*/
#define SEND_CNT_WIRELESS_CONN_DEV_0		{1, 0, 0, 0}
#define SEND_CNT_WIRELESS_CONN_DEV_1		{0, 1, 0, 0}
#define SEND_CNT_WIRELESS_CONN_DEV_2		{0, 0, 1, 0}
#define SEND_CNT_WIRELESS_CONN_DEV_3		{0, 0, 0, 1}

/*! \def RESEND_DELAY_WIRELESS_CONN_DEV_X
*  \brief Time in ms that should be waited until a package is sent again when no acknowledge is received per device and wireless connection.
*/
#define RESEND_DELAY_WIRELESS_CONN_DEV_0	{30, 30, 30, 30}
#define RESEND_DELAY_WIRELESS_CONN_DEV_1	{30, 30, 30, 30}
#define RESEND_DELAY_WIRELESS_CONN_DEV_2	{30, 30, 30, 30}
#define RESEND_DELAY_WIRELESS_CONN_DEV_3	{30, 30, 30, 30}




/*! \def MAX_THROUGHPUT_WIRELESS_CONN
*  \brief Maximal throughput per wireless connection (0 to 3) in bytes/s.
*/
#define MAX_THROUGHPUT_WIRELESS_CONN		{10000, 10000, 10000, 10000}

/*! \def USUAL_PACKET_SIZE_DEVICE_CONN
*  \brief Usual packet size per device in bytes if known or 0 if unknown.
*/
#define USUAL_PACKET_SIZE_DEVICE_CONN		{25, 25, 25, 25}

/*! \def PACKAGE_GEN_MAX_TIMEOUT
*  \brief Maximal time in ms that is waited until packet size is reached. If timeout is reached, the packet will be sent anyway, independent of the amount of the available data.
*/
#define PACKAGE_GEN_MAX_TIMEOUT				{5, 5, 5, 5}




/*! \def DELAY_DISMISS_OLD_PACK_PER_DEV
*  \brief Maximal time in [ms] that is waited when a new packet is available of a device and an old one is still in the buffer till the old one is removed from the buffer.
*/
#define DELAY_DISMISS_OLD_PACK_PER_DEV		{255, 255, 255, 255}




/*! \def SEND_ACK_PER_WIRELESS_CONN
*  \brief To be able to configure on which wireless connections acknowledges should be sent if a data package has been received. Set to 0 if no acknowledge should be sent, 1 if yes.
*/
#define SEND_ACK_PER_WIRELESS_CONN			{0, 0, 0, 0}


/*! \def USE_CTS_PER_WIRELESS_CONN
*  \brief To be able to configure on which wireless connections CTS for hardware flow control should be used. Set to 0 if it shouldn't be used, 1 if yes.
*			If enabled, data transmission is stopped CTS input is high and continued if low.
*/
#define USE_CTS_PER_WIRELESS_CONN			{0, 0, 0, 0}





/*! \def USE_GOLAY_ERROR_CORRECTING_CODING
*  \brief Set to 0 for normal operation, 1 to enable golay coding in order to be able to correct up to 3 bit errors in a 24 bit word. Doubles the data rate.
*			TODO: Replace Golay coding by some coding that is able to handle missing bytes (erasure code) or/and add some interleaving
*/
#define USE_GOLAY_ERROR_CORRECTING_CODING	(0)

