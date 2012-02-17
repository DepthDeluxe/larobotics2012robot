#include "../Coriolis.h"
#include "WPILib.h"
#include <iostream>
#include "string.h"
#include "stdlib.h"

void Coriolis::ServerTask(void)
{
	/* Server stuff goes here. */
	int i = 0;
	char *buf = NULL;
	
	UdpSocket sock;
	printf("CORIOLIS:SERVER: Binding to socket...");
	if (!sock.Bind("10.1.14.2", 7654))
		printf("CORIOLIS:SERVER: Failed to bind socket...\n");
	else
		printf("Done.\n");
	while (true)
	{
		if (sock.Receive() > 0)
		{
			buf = sock.ReadBuffer();
			CRITICAL_REGION(semaphore)
			imageX = atoi(strtok(buf, ",E"));
			imageY = atoi(strtok(NULL, ",E"));
			END_REGION
		}
		else
			printf("CORIOLIS:SERVER:ERROR: Hmmmmm, something is not right...\n");
		i++;
		Wait(0.01);
	}
}
