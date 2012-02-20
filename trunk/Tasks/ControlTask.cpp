#include "../Coriolis.h"
#include "../Utility/Utils.h"
#include "WPILib.h"

void Coriolis::ControlTask(void) {
	int i = 0;
	printf("CORIOLIS: Control task started.\n");

	while (true) {
		CRITICAL_REGION(semaphore)
		
		// handle drivebase
		robotDrive.ControlThread();
		
		// handle robotshooter
		robotShooter.ControlThread();
		
		// handle bridgetipper
		bridgeTipper.ControlThread();
		
		// update pidtuner
		pidTuner.Run();
		
		END_REGION
		/************************/
		
		if (i % 250 == 0)
			printf("CORIOLIS:ControlTask: Alive...\n");
		Wait(0.01);
		i++;
	}
	printf("CORIOLIS: Control task end.\n");
}
