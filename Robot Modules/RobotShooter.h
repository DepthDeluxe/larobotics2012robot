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
	// victors
	Victor*		m_panVictor;
	Victor*		m_tiltVictor;
	Victor*		m_shootVictor;
	
	// PID controllers
	PIDController*	m_tiltControl;
	PIDController*	m_panControl;
	
	float m_panSetpoint, m_tiltSetpoint;
	float m_panSpeed, m_tiltSpeed;
	float m_shootPower;
	
	// socket members goes here
	bool m_newData;
	bool m_isAutoAim;
	
	bool m_shoot;
	bool m_intakeBalls;
	
public:
	RobotShooter(Victor*, Victor*, Victor*, PIDController*, PIDController*);
	
	void ProcessAuto();
	void ProcessManual(int, int, int);
	void Shoot();
	
	void ControlThread();
};

#endif /*ROBOTSHOOTER_H_*/
