#ifndef DRIVEBASE_H_
#define DRIVEBASE_H_

#include "WPILib.h"

class DriveBase
{
private:
	float m_leftSpeed;
	float m_rightSpeed;
	
public:
	DriveBase(Encoder*);
	
	void ProcessAuto();
	void ProcessManual();
	
	void SetValuesAuto(PIDController*);
	void SetValuesManual(Victor*, Victor*);
};

#endif /*DRIVEBASE_H_*/
