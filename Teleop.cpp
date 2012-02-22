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
		robotShooter.Shoot();
	}
	
	// set pan and tilt variables
	robotShooter.SetPanPower(left.GetX());
	robotShooter.SetTiltPower(right.GetX());
	
	// if right button #3 pressed, toggle bridge tipper
	if (left.GetRawButton(3))
		bridgeTipper.Move();
	
	if (right.GetRawButton(11))
		autoAimToggle = !autoAimToggle;
	robotShooter.SetAutomated(autoAimToggle);
		
	END_REGION
	
	/* Lo/Hi gear handling. */
	CRITICAL_REGION(semaphore)
	if (left.GetRawButton(2))
		robotDrive.SetGear(LO_GEAR);
	else if (right.GetRawButton(2))
		robotDrive.SetGear(HI_GEAR);
	END_REGION
}
