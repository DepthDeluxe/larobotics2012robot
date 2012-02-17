#ifndef ROBOTSHOOTER_CPP_
#define ROBOTSHOOTER_CPP_

#include "RobotShooter.h"
#include "Utils.h"

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
	shootControl->Set(m_shootPower);
}

void RobotShooter::SetValuesManual(Victor* panVictor, Victor* tiltVictor, Victor* shootVictor)
{
	panVictor->Set(m_panSpeed);
	tiltVictor->Set(m_panSpeed);
	shootVictor->Set(m_shootPower);
}

#endif /*ROBOTSHOOTER_CPP_*/
