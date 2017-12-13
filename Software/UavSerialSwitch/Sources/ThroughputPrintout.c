#include "ThroughputPrintout.h"
#include "Shell.h"
#include "FRTOS.h"
#include "Config.h"
#include <stdio.h> // sprintf

/* global variables */
long unsigned int numberOfAckReceived[NUMBER_OF_UARTS];
long unsigned int numberOfPacksReceived[NUMBER_OF_UARTS];
long unsigned int numberOfPayloadBytesExtracted[NUMBER_OF_UARTS];
long unsigned int numberOfPayloadBytesSent[NUMBER_OF_UARTS];
long unsigned int numberOfPacksSent[NUMBER_OF_UARTS];
long unsigned int numberOfAcksSent[NUMBER_OF_UARTS];
long unsigned int numberOfSendAttempts[NUMBER_OF_UARTS];
long unsigned int numberOfDroppedPackages[NUMBER_OF_UARTS];

void throughputPrintout_TaskEntry(void* p)
{
	const TickType_t taskInterval = pdMS_TO_TICKS(config.ThroughputPrintoutTaskInterval*1000); /* task interval in seconds, but configured in milliseconds */
	TickType_t lastWakeTime = xTaskGetTickCount(); /* Initialize the xLastWakeTime variable with the current time. */
	static char buf[200];

	static float averagePayloadReceived[NUMBER_OF_UARTS];
	static float averagePayloadSent[NUMBER_OF_UARTS];
	static float averagePacksSent[NUMBER_OF_UARTS];
	static float averagePacksReceived[NUMBER_OF_UARTS];
	static float averageAcksSent[NUMBER_OF_UARTS];
	static float averageAcksReceived[NUMBER_OF_UARTS];

	for(;;)
	{
		vTaskDelayUntil( &lastWakeTime, taskInterval ); /* Wait for the next cycle */
		/* calculate throughput in byte per sec */
		for(int cnt = 0; cnt < NUMBER_OF_UARTS; cnt++)
		{
			averagePayloadReceived[cnt] = numberOfPayloadBytesExtracted[cnt]/numberOfPacksReceived[cnt];
			averagePayloadSent[cnt] = numberOfPayloadBytesSent[cnt]/numberOfPacksSent[cnt];
			averagePacksReceived[cnt] = numberOfPacksReceived[cnt]/config.ThroughputPrintoutTaskInterval;
			averagePacksSent[cnt] = numberOfPacksSent[cnt]/config.ThroughputPrintoutTaskInterval;
			averageAcksReceived[cnt] = numberOfAckReceived[cnt]/config.ThroughputPrintoutTaskInterval;
			averageAcksSent[cnt] = numberOfAcksSent[cnt]/config.ThroughputPrintoutTaskInterval;
		}

		sprintf(buf, "--------------------------------------------------------------\r\n");
		pushMsgToShellQueue(buf, strlen(buf));

		/* print throughput information */
		sprintf(buf, "Wireless: Sent packages [packages/s]: %.1f,%.1f,%.1f,%.1f; Received packages: [packages/s] %.1f,%.1f,%.1f,%.1f\r\n",
				averagePacksSent[0], averagePacksSent[1], averagePacksSent[2], averagePacksSent[3],
				averagePacksReceived[0], averagePacksReceived[1], averagePacksReceived[2], averagePacksReceived[3]);
		pushMsgToShellQueue(buf, strlen(buf));

		sprintf(buf, "Wireless: Average payload sent [bytes/pack]: %.1f,%.1f,%.1f,%.1f; Average payload received: [bytes/pack] %.1f,%.1f,%.1f,%.1f\r\n",
				averagePayloadSent[0], averagePayloadSent[1], averagePayloadSent[2], averagePayloadSent[3],
				averagePayloadReceived[0], averagePayloadReceived[1], averagePayloadReceived[2], averagePayloadReceived[3]);
		pushMsgToShellQueue(buf, strlen(buf));

		sprintf(buf, "Wireless: Sent acknowledges [acks/s]: %.1f,%.1f,%.1f,%.2f; Received acknowledges: [acks/s] %.1f,%.1f,%.1f,%.1f\r\n",
				averageAcksSent[0], averageAcksSent[1], averageAcksSent[2], averageAcksSent[3],
				averageAcksReceived[0], averageAcksReceived[1], averageAcksReceived[2], averageAcksReceived[3]);
		pushMsgToShellQueue(buf, strlen(buf));

		sprintf(buf, "Device: Total number of dropped packages per device input: %lu,%lu,%lu,%lu\r\n",
				numberOfDroppedPackages[0], numberOfDroppedPackages[1], numberOfDroppedPackages[2], numberOfDroppedPackages[3]);
		pushMsgToShellQueue(buf, strlen(buf));

		sprintf(buf, "--------------------------------------------------------------\r\n");
		pushMsgToShellQueue(buf, strlen(buf));

		/* reset measurement */
		for(int cnt = 0; cnt < NUMBER_OF_UARTS; cnt++)
		{
			numberOfPacksReceived[cnt] = 0;
			numberOfPacksSent[cnt] = 0;
			numberOfAckReceived[cnt] = 0;
			numberOfAcksSent[cnt] = 0;
			numberOfPayloadBytesExtracted[cnt] = 0;
			numberOfPayloadBytesSent[cnt] = 0;
		}
	}
}
