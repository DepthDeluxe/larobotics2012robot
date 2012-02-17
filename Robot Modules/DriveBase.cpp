#ifndef DRIVEBASE_CPP_
#define DRIVEBASE_CPP_

#include "DriveBase.h"
#include "Utils.h"

DriveBase::DriveBase()
{
	m_leftPower = 0;
	m_rightPower = 0;
	m_gear = 0;
}

void DriveBase::ProcessAuto()
{
	// drive autonomous code goes here
}

void DriveBase::Drive(float leftPower, float rightPower)
{
	// set power values, left value is negative becasue motors are inverted
	m_leftPower = -leftPower;
	m_rightPower = rightPower;
}

void DriveBase::SetValuesAuto(PIDController* drivePID)
{
	
}

void DriveBase::SetValues(Victor* leftVictor, Victor* rightVictor, Solenoid* loGear, Solenoid* hiGear)
{
	// set victors
	leftVictor->Set(m_leftPower);
	rightVictor->Set(m_rightPower);
	
	// set gears
	if (gear == HI_GEAR)
	{
		loGear->Set(false);
		hiGear->Set(true);
	}
	else
	{
		loGear->Set(true);
		hiGear->Set(false);
	}
}

#endif
