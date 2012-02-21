#ifndef ROBOTSHOOTER_CPP_
#define ROBOTSHOOTER_CPP_

#include "RobotShooter.h"
#include "../Utility/Utils.h"

RobotShooter::RobotShooter(Jaguar* panJaguar, Jaguar* tiltJaguar, Victor* shootVictor,
		Victor* shootBainBotVictor, Victor* intakeRoller, Relay* shootRoller,
		PIDController* panControl, PIDController* tiltControl)
{
	// save pointers
	m_panJaguar = panJaguar;
	m_tiltJaguar = tiltJaguar;
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
	m_panPower = 0;
	m_tiltPower = 0;
	
	m_newData = false;
	m_isAutoAim = false;
	m_shooterOn = false;
	m_shoot = false;
	m_intakeBalls = false;
	
	// start with PID Controllers disabled
	m_panControl->Disable();
	m_tiltControl->Disable();
	
	dashboard = SmartDashboard::GetInstance();
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

void RobotShooter::IntakeBalls()
{
	m_intakeBalls = true;
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
		m_panJaguar->Set(victor_linearize(m_panPower));
		m_tiltJaguar->Set(victor_linearize(m_tiltPower));
		
		dashboard->PutDouble("Pan Power", m_panPower);
		dashboard->PutDouble("Tilt Power", m_tiltPower);
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
		// return functions
		m_intakeRoller->Set(-0.5);
		m_intakeBalls = false;
	}
	else
	{
		m_intakeRoller->Set(0.0);
	}
	
	dashboard->PutBoolean("IsShooting", m_shoot);
	
	// shooter roller
	if (m_shoot)
	{
		m_shootRoller->Set(Relay::kForward);
		m_shoot = false;
	}
	else
	{
		m_shootRoller->Set(Relay::kOff);
	}
}

#endif /*ROBOTSHOOTER_CPP_*/
