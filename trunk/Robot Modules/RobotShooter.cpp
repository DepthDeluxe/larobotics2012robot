#ifndef ROBOTSHOOTER_CPP_
#define ROBOTSHOOTER_CPP_

#include "RobotShooter.h"
#include "../Utils.h"

RobotShooter::RobotShooter(Victor* panVictor, Victor* tiltVictor, Victor* shootVictor,
		PIDController* panControl, PIDController* tiltControl)
{
	// save pointers
	m_panVictor = panVictor;
	m_tiltVictor = tiltVictor;
	m_shootVictor = shootVictor;
	m_panControl = panControl;
	m_tiltControl = tiltControl;
	
	// init variables
	m_panSetpoint = 0;
	m_tiltSetpoint = 0;
	m_shootPower = 0;
}

void RobotShooter::ProcessAuto()
{
	
}

void RobotShooter::ProcessManual(int panSpeed, int tiltSpeed, int shootPower)
{
	m_panSpeed = panSpeed;
	m_tiltSpeed = tiltSpeed;
	m_shootPower = shootPower;
	m_shoot = false;
	m_intakeBalls = false;
}

void RobotShooter::Shoot()
{
	m_shoot = true;
}

void RobotShooter::ControlThread()
{
	m_panControl->SetSetpoint(m_panSetpoint);
	m_tiltControl->SetSetpoint(m_tiltSetpoint);
	m_shootVictor->Set(m_shootPower);
	
	m_panVictor->Set(m_panSpeed);
	m_tiltVictor->Set(m_panSpeed);
}

#endif /*ROBOTSHOOTER_CPP_*/
