#ifndef ROBOTSHOOTER_CPP_
#define ROBOTSHOOTER_CPP_

#include "RobotShooter.h"
#include "../Utility/Utils.h"

RobotShooter::RobotShooter(Victor* panVictor, Victor* tiltVictor, Victor* shootVictor,
		Victor* shootBainBotVictor, Victor* intakeRoller, Relay* shootRoller,
		PIDController* panControl, PIDController* tiltControl)
{
	// save pointers
	m_panVictor = panVictor;
	m_tiltVictor = tiltVictor;
	m_shootVictor = shootVictor;
	m_shootBBVictor = shootBainBotVictor;
	m_intakeRoller = intakeRoller;
	m_shootRoller = shootRoller;
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

void RobotShooter::SetPanPower(float power)
{
	m_panPower = power;
}

void RobotShooter::SetTiltPower(float power)
{
	m_tiltPower = power;
}

void RobotShooter::SetShootPower(float power)
{
	m_shootPower = power;
}

void RobotShooter::EnableShooter(bool isactivated)
{
	m_shooterOn = isactivated;
}

void RobotShooter::Shoot()
{
	m_shoot = true;
}

bool RobotShooter::IsShooterOn()
{
	return m_shooterOn;
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
		
		// set setpoints on pan and tilt controls
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
		m_panVictor->Set(victor_linearize(m_panPower));
		m_tiltVictor->Set(victor_linearize(m_panPower));
	}
	
	// set the shooting power if power turned on
	// and if not, turn it off
	if (m_shooterOn)
	{
		m_shootVictor->Set(victor_linearize(m_shootPower));
		m_shootBBVictor->Set(victor_linearize(m_shootPower));
	}
	else
	{
		m_shootVictor->Set(0.0);
		m_shootBBVictor->Set(0.0);
	}
	
	// intake roller
	if (m_intakeBalls)
	{
		m_intakeRoller->Set(1.0);
	}
	else
	{
		m_intakeRoller->Set(0.0);
	}
	
	// shooter roller
	if (m_shoot)
	{
		m_shootRoller->Set(Relay::kForward);
	}
	else
	{
		m_shootRoller->Set(Relay::kOff);
	}
}

#endif /*ROBOTSHOOTER_CPP_*/
