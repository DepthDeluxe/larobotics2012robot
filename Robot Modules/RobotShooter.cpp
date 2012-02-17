#ifndef ROBOTSHOOTER_CPP_
#define ROBOTSHOOTER_CPP_

#include "RobotShooter.h"

RobotShooter::RobotShooter()
{
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
}

void RobotShooter::SetValuesAuto(PIDController* panControl, PIDController* tiltControl, Victor* shootControl)
{
	panControl->SetSetpoint(m_panSetpoint);
	tiltControl->SetSetpoint(m_tiltSetpoint);
	shootControl->SetSpeed(m_shootPower);
}

void RobotShooter::SetValuesManual(Victor* panVictor, Victor* tiltVictor, Victor* shootVictor)
{
	panVictor->SetSpeed(m_panSpeed);
	tiltVictor->SetSpeed(m_panSpeed);
	shootVictor->SetSpeed(m_shootPower);
}

#endif /*ROBOTSHOOTER_CPP_*/
