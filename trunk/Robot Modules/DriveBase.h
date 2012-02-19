#ifndef DRIVEBASE_H_
#define DRIVEBASE_H_

#include "WPILib.h"

#define LO_GEAR 0
#define HI_GEAR 1

class DriveBase
{
private:
	// pointers to all that this module uses
	Victor*		m_leftVictor;
	Victor*		m_rightVictor;
	Solenoid*	m_loGear;
	Solenoid*	m_hiGear;
	
	float m_leftPower;
	float m_rightPower;
	
	int m_gear;
	
public:
	// constructor
	DriveBase(Victor*, Victor*, Solenoid*, Solenoid*);
	
	// control variables
	void Drive(float,float);
	void SetGear(int);
	
	// task functions
	void Autonomous();
	void ControlThread();
};

#endif /*DRIVEBASE_H_*/
