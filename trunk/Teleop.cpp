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
	
	CRITICAL_REGION(semaphore)
	// set shooter turns on if left trigger pressed
	robotShooter.SetShootPower(1.0);
	robotShooter.EnableShooter(left.GetTrigger());
	
	// intake balls and shoot if right trigger pressed
	if (right.GetTrigger())
	{
		robotShooter.IntakeBalls();
		
		// if shooter is sped up, shoot
		if (robotShooter.IsShooterOn())
			robotShooter.Shoot();
	}
	
	// if right button #3 pressed, toggle bridge tipper
	if (right.GetRawButton(3))
		bridgeTipper.Move();
	END_REGION
	
	/* Lo/Hi gear handling. */
	CRITICAL_REGION(semaphore)
	if (left.GetTrigger())
		robotDrive.SetGear(LO_GEAR);
	else if (right.GetTrigger())
		robotDrive.SetGear(HI_GEAR);
	END_REGION
}
