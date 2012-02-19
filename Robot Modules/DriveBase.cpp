#ifndef DRIVEBASE_CPP_
#define DRIVEBASE_CPP_

#include "DriveBase.h"
#include "../Utility/Utils.h"

DriveBase::DriveBase(Victor* leftVictor, Victor* rightVictor, Solenoid* loGear, Solenoid* hiGear)
{
	// fill pointers
	m_leftVictor = leftVictor;
	m_rightVictor = rightVictor;
	m_loGear = loGear;
	m_hiGear = hiGear;
	
	m_leftPower = 0;
	m_rightPower = 0;
	m_gear = 0;
}

void DriveBase::Drive(float leftPower, float rightPower)
{
	// set power values, left value is negative because motors are inverted
	m_leftPower = -leftPower;
	m_rightPower = rightPower;
}

void DriveBase::SetGear(int gear)
{
	// only adjust gear value if new set value is valid
	if (gear == HI_GEAR || gear == LO_GEAR)
		m_gear = gear;
}

void DriveBase::Autonomous()
{
	// drive autonomous code goes here
}

void DriveBase::ControlThread()
{
	// set victors
	m_leftVictor->Set(victor_linearize(m_leftPower));
	m_rightVictor->Set(victor_linearize(m_rightPower));
	
	// set gears
	if (m_gear == HI_GEAR)
	{
		m_loGear->Set(false);
		m_hiGear->Set(true);
	}
	else
	{
		m_loGear->Set(true);
		m_hiGear->Set(false);
	}
}

#endif
