#ifndef ROBOTSHOOTER_CPP_
#define ROBOTSHOOTER_CPP_

#include "RobotShooter.h"
#include "../Utility/Utils.h"

RobotShooter::RobotShooter(Jaguar* panJaguar, Jaguar* tiltJaguar, Victor* shootVictor,
		Victor* shootBainBotVictor, Victor* intakeRoller, Relay* shootRoller,
		AnalogChannel* panPot, AnalogChannel* tiltPot) :
			panControl(RS_PAN_P, RS_PAN_I, RS_PAN_D, panPot, panJaguar),
			tiltControl(RS_TILT_P, RS_TILT_I, RS_TILT_D, tiltPot, tiltJaguar)
{
	// save pointers
	m_panJaguar = panJaguar;
	m_tiltJaguar = tiltJaguar;
	m_shootVictor = shootVictor;
	m_shootBBVictor = shootBainBotVictor;
	m_intakeRoller = intakeRoller;
	m_shootRoller = shootRoller;
	m_panPot = panPot;
	m_tiltPot = tiltPot;
	
	// enable pids
	panControl.Enable();
	
	// disable tilt pid because control loop is unstable
	tiltControl.Disable();
	
	// set default PID values
	panControl.SetSetpoint(RS_PAN_MID);
	tiltControl.SetSetpoint(RS_TILT_MIN);
	
	// init variables
	panSetpoint = 367;
	tiltSetpoint = 0;
	shootPower = 0;
	panPower = 0;
	tiltPower = 0;
	
	// all bools are initialized false
	newData = false;
	isAutoAim = false;
	shooterOn = false;
	shoot = false;
	intakeBalls = false;
	
	// load instance of smartdashboard
	dashboard = SmartDashboard::GetInstance();
}

void RobotShooter::SetPanPower(float power)
{
	panPower = power;
}

void RobotShooter::SetTiltPower(float power)
{
	tiltPower = power;
}

void RobotShooter::SetShootPower(float power)
{
	shootPower = power;
}

void RobotShooter::SetAutomated(bool automated)
{
	isAutoAim = automated;
}

void RobotShooter::EnableShooter(bool isactivated)
{
	shooterOn = isactivated;
}

void RobotShooter::Shoot()
{
	shoot = true;
}

void RobotShooter::IntakeBalls()
{
	intakeBalls = true;
}

bool RobotShooter::IsShooterOn()
{
	return shooterOn;
}

void RobotShooter::ControlThread()
{
	if (isAutoAim)
	{		
		panControl.Enable();
	}
	else
	{	
		panControl.Disable();
		
		// set victor values
		m_panJaguar->Set(victor_linearize(panPower));
		m_tiltJaguar->Set(victor_linearize(tiltPower));
		
		dashboard->PutDouble("Pan Power", panPower);
		dashboard->PutDouble("Tilt Power", tiltPower);
	}
	
	// set the shooting power if power turned on
	// and if not, turn it off
	if (shooterOn)
	{
		m_shootVictor->Set(victor_linearize(shootPower));
		m_shootBBVictor->Set(victor_linearize(shootPower));
	}
	else
	{
		m_shootVictor->Set(0.0);
		m_shootBBVictor->Set(0.0);
	}
	
	// intake roller
	if (intakeBalls)
	{	
		// return functions
		m_intakeRoller->Set(-0.5);
		intakeBalls = false;
	}
	else
	{
		m_intakeRoller->Set(0.0);
	}
	
	dashboard->PutBoolean("IsShooting", shoot);
	
	// shooter roller
	if (shoot)
	{
		m_shootRoller->Set(Relay::kForward);
		shoot = false;
	}
	else
	{
		m_shootRoller->Set(Relay::kOff);
	}
	
	// put other dashboard values
	dashboard->PutInt("Pan Value", m_panPot->GetValue());
	dashboard->PutInt("Tilt Value", m_tiltPot->GetValue());
}

#endif /*ROBOTSHOOTER_CPP_*/
