#ifndef PIDTUNER_CPP_
#define PIDTUNER_CPP_

#include "PIDTuner.h"

PIDTuner::PIDTuner(PIDController* pidToBeTested) :
	pAdjust(1),
	iAdjust(2),
	dAdjust(3),
	setpointAdjust(4)
{
	// save pointer into class
	pidControl = pidToBeTested;
	
	// get instance of smartdashboard
	dashboard = SmartDashboard::GetInstance();
	
	// set range to default
	SetPIDRange(0,1);
	SetSetpointRange(0,10);
}

void PIDTuner::Run()
{
	// save PID values
	P = pAdjust.GetValue();
	I = iAdjust.GetValue();
	D = dAdjust.GetValue();
	setpoint = setpointAdjust.GetValue();
	
	pidControl->SetSetpoint(setpoint);
	
	// send to dashboard
	dashboard->PutDouble("P", P);
	dashboard->PutDouble("I", I);
	dashboard->PutDouble("D", D);
	dashboard->PutDouble("Setpoint", setpoint);
}

void PIDTuner::SetPIDRange(float minval, float maxval)
{
	minPIDValue = minval;
	maxPIDValue = maxval;
}

void PIDTuner::SetSetpointRange(float minval, float maxval)
{
	minSetpointValue = minval;
	maxSetpointValue = maxval;
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
