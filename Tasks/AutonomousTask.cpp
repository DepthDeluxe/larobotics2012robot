#include "../Coriolis.h"
#include "WPILib.h"

void Coriolis::AutonomousTask(void) {
	printf("CORIOLIS: Autonomous started.\n");
	int i = 0;
	
	while (IsAutonomous())
	{
		if (i % 250 == 0)
			printf("CORIOLIS:AutonomousTask: Alive...\n");
		i++;
		Wait(0.005);
	}
	printf("CORIOLIS: Autonomous stop.\n");
}
