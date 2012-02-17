#ifndef ROBOTSHOOTER_H_
#define ROBOTSHOOTER_H_

// default includes
#include "WPILib.h"
#include "sysLib.h"

#define RS_PAN_P	1
#define RS_PAN_I	1
#define RS_PAN_D	1

#define RS_TILT_P	1
#define RS_TILT_I	1
#define RS_TILT_D	1

//
// This is the class that manages the robot's shooter code
// it will receive udp data from the camera
//
class RobotShooter
{
private:
	float m_panSetpoint, m_tiltSetpoint;
	float m_panSpeed, m_tiltSpeed;
	float m_shootPower;
	
	// socket members goes here
	bool m_newData;
	
public:
	RobotShooter();
	
	void ProcessAuto();
	void ProcessManual(int, int, int);
	
	void SetValuesAuto(PIDController*, PIDController*, Victor*);
	void SetValuesManual(Victor*, Victor*, Victor*);
};

#endif /*ROBOTSHOOTER_H_*/
