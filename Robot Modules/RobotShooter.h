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

// structure that defines packet information
struct RobotVisionPacket
{
	float PanOffset;
	float Tilt;
	float Speed;
};

//
// This is the class that manages the robot's shooter code
// it will receive udp data from the camera
//
class RobotShooter
{
public:
	RobotShooter(Jaguar*, Jaguar*, Victor*, Victor*, Victor*, Relay*, PIDController*, PIDController*);
	
	// auto shoot function
	void ProcessAuto();
	
	// manual shooter set values
	void SetPanPower(float);
	void SetTiltPower(float);
	void SetShootPower(float);
	
	// other shoot functions
	void EnableShooter(bool);
	void Shoot();
	
	// ball intake
	void IntakeBalls();
	
	// return functions
	bool IsShooterOn();
	
	// function that sends variables to physical objects
	void ControlThread();
	
private:
	// victors
	Jaguar*		m_panJaguar;
	Jaguar*		m_tiltJaguar;
	Victor*		m_shootVictor;
	Victor*		m_shootBBVictor;
	Victor*		m_intakeRoller;
	Relay*		m_shootRoller;
	
	// PID controllers
	PIDController*	m_tiltControl;
	PIDController*	m_panControl;
	
	// smart dashboard
	SmartDashboard* dashboard;
	
	float m_panSetpoint, m_tiltSetpoint;
	float m_panPower, m_tiltPower;
	float m_shootPower;
	
	// socket members goes here
	bool m_newData;
	bool m_isAutoAim;
	bool m_shooterOn;
	
	bool m_shoot;
	bool m_intakeBalls;
};

#endif /*ROBOTSHOOTER_H_*/
