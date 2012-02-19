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
	
	// set PID values
	m_panControl->SetPID(RS_PAN_P, RS_PAN_I, RS_PAN_D);
	m_tiltControl->SetPID(RS_TILT_P, RS_TILT_I, RS_TILT_D);
	
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

void RobotShooter::EnableShooter(bool isactivated)
{
	m_shooterOn = isactivated;
}

void RobotShooter::Shoot()
{
	m_shoot = true;
}

void RobotShooter::ControlThread()
{
	if (m_isAutoAim)
	{
		// check to see if control is not enabled
		if (!m_panControl->IsEnabled() || !m_tiltControl->IsEnabled())
		{
			m_panControl->Enable();
			m_panControl->Enable();
		}
		
		// set setpoints on victors
		m_panControl->SetSetpoint(m_panSetpoint);
		m_tiltControl->SetSetpoint(m_tiltSetpoint);
	}
	else
	{
		// check to see if control is enabled
		if (m_panControl->IsEnabled() || m_tiltControl->IsEnabled())
		{
			m_panControl->Disable();
			m_tiltControl->Disable();
		}
		
		// set victor values
		m_panVictor->Set(victor_linearize(m_panSpeed));
		m_tiltVictor->Set(victor_linearize(m_panSpeed));
	}
	
	// set the shooting power if power turned on
	// and if not, turn it off
	if (m_shooterOn)
		m_shootVictor->Set(victor_linearize(m_shootPower));
	else
		m_shootVictor->Set(0.0);
}

#endif /*ROBOTSHOOTER_CPP_*/
