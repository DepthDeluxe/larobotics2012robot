#include "../Coriolis.h"
#include "../Utility/Utils.h"
#include "WPILib.h"

void Coriolis::ControlTask(void) {
	int i = 0;
	printf("CORIOLIS: Control task started.\n");

	while (true) {
		CRITICAL_REGION(semaphore)
		
		// update pidtuner
		pidTuner.Run();
		
		// handle drivebase
		robotDrive.ControlThread();
		
		// handle robotshooter
		robotShooter.ControlThread();
		
		END_REGION
		/************************/
		
		if (i % 250 == 0)
			printf("CORIOLIS:ControlTask: Alive...\n");
		Wait(0.01);
		i++;
	}
	printf("CORIOLIS: Control task end.\n");
}
