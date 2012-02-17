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
	leftPower = -left.GetY();
	rightPower = right.GetY();
	END_REGION
	
	/* Lo/Hi gear handling. */
	CRITICAL_REGION(semaphore)
	if (left.GetTrigger())
		gear = LO_GEAR;
	else if (right.GetTrigger())
		gear = HI_GEAR;
	END_REGION
}
