#include "../Coriolis.h"
#include "../Utils.h"
#include "WPILib.h"

void Coriolis::ControlTask(void) {
	int i = 0;
	printf("CORIOLIS: Control task started.\n");

	while (true) {
		CRITICAL_REGION(semaphore)
		
		/* Handle drive. */
		leftDrive.Set(victor_linearize(leftPower));
		rightDrive.Set(victor_linearize(rightPower));
		/*****************/
		
		/* Handle transmission. */
		if (gear == HI_GEAR)
		{
			loGear.Set(true);
			hiGear.Set(false);
		}
		else if (gear == LO_GEAR)
		{
			loGear.Set(false);
			hiGear.Set(true);
		}
		
		/* handle PID Controls */
		panController.SetSetpoint(panSetpoint);
		tiltController.SetSetpoint(tiltSetpoint);
		
		END_REGION
		/************************/
		
		if (i % 250 == 0)
			printf("CORIOLIS:ControlTask: Alive...\n");
		Wait(0.01);
		i++;
	}
	printf("CORIOLIS: Control task end.\n");
}
