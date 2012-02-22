#ifndef PIDTUNER_CPP_
#define PIDTUNER_CPP_

#include "PIDTuner.h"

PIDTuner::PIDTuner(PIDController* pidToBeTested) :
	pAdjust(3),
	iAdjust(4),
	dAdjust(5),
	setpointAdjust(6)
{
	// save pointer into class
	pidControl = pidToBeTested;
	
	// get instance of smartdashboard
	dashboard = SmartDashboard::GetInstance();
	
	pidControl->Enable();
	
	// set the pid range from 0 - 0.1;
	SetPIDRange(1);
}

void PIDTuner::Run()
{
	// save PID values
	P = pAdjust.GetValue() * pidScaleFactor;
	I = iAdjust.GetValue() * pidScaleFactor;
	D = dAdjust.GetValue() * pidScaleFactor;
	setpoint = setpointAdjust.GetValue();
	
	if (setpoint > 238 && setpoint < 974)
		pidControl->SetSetpoint(setpoint);
	
	if (P < 0)
		P = 0;
	if (I < 0)
		I = 0;
	if (D < 0)
		D = 0;
	
	P = -P;
	I = -I;
	D = -D;
	
	pidControl->SetPID(P,I,D);
	
	// send to dashboard
	dashboard->PutDouble("P", P);
	dashboard->PutDouble("I", I);
	dashboard->PutDouble("D", D);
	dashboard->PutDouble("Setpoint", setpoint);
	
	// send PID values
	dashboard->PutDouble("PID Result", pidControl->Get());
}

void PIDTuner::SetPIDRange(float range)
{
	// pot range is -2 to 975
	// or 977 nums
	
	pidScaleFactor = range / 977;
}

void PIDTuner::SetSetpoint(float set)
{
	setpoint = set;
}

float PIDTuner::GetP()
{
	return P;
}

float PIDTuner::GetI()
{
	return I;
}

float PIDTuner::GetD()
{
	return D;
}

#endif
