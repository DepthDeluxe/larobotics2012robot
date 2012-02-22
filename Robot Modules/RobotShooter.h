#ifndef ROBOTSHOOTER_H_
#define ROBOTSHOOTER_H_

// default includes
#include "WPILib.h"
#include "sysLib.h"

#include "../Utility/PIDTuner.h"

#define RS_PAN_P	-0.02
#define RS_PAN_I	0.0
#define RS_PAN_D	0.0

#define RS_TILT_P	-0.08
#define RS_TILT_I	0
#define RS_TILT_D	-0.08

#define RS_PAN_MIN	64
#define RS_PAN_MID	454
#define RS_PAN_MAX	825

#define RS_TILT_MIN	238
#define RS_TILT_MAX	975

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
	RobotShooter(Jaguar*, Jaguar*, Victor*, Victor*, Victor*, Relay*, AnalogChannel*, AnalogChannel*);
	
	// manual shooter set values
	void SetPanPower(float);
	void SetTiltPower(float);
	void SetShootPower(float);
	
	// enable auto
	void SetAutomated(bool);
	
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
	
	// Analog Inputs
	AnalogChannel* m_panPot;
	AnalogChannel* m_tiltPot;
	
	// smart dashboard
	SmartDashboard* dashboard;
	
	// PID Controllers
	PIDController	panControl;
	PIDController	tiltControl;
	
	float panSetpoint, tiltSetpoint;
	float panPower, tiltPower;
	float shootPower;
	
	// socket members goes here
	bool newData;
	bool isAutoAim;
	bool shooterOn;
	
	bool shoot;
	bool intakeBalls;
};

#endif /*ROBOTSHOOTER_H_*/
