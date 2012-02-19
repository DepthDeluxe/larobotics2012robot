#include "Coriolis.h"
#include "WPILib.h"

/*
 * This function is iteratively called, so be careful!
 */
void Coriolis::Teleop(void)
{
	/* Teleop. */
	
	/* Operator drive. */
	CRITICAL_REGION(semaphore)
	robotDrive.Drive(left.GetY(), right.GetY());
	END_REGION
	
	/* Lo/Hi gear handling. */
	CRITICAL_REGION(semaphore)
	if (left.GetTrigger())
		robotDrive.SetGear(LO_GEAR);
	else if (right.GetTrigger())
		robotDrive.SetGear(HI_GEAR);
	END_REGION
}
