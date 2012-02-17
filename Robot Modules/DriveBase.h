#ifndef DRIVEBASE_H_
#define DRIVEBASE_H_

#include "WPILib.h"

#define LO_GEAR 0
#define HI_GEAR 1

class DriveBase
{
private:
	float m_leftPower;
	float m_rightPower;
	
	int m_gear;
	
public:
	DriveBase();
	
	// control variables
	void Drive(float,float);
	void ChangeGear(int);
	
	void SetValues(Victor*, Victor*, Solenoid*, Solenoid*);
};

#endif /*DRIVEBASE_H_*/
