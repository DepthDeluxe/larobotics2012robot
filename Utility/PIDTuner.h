#ifndef PIDTUNER_H_
#define PIDTUNER_H_

#include "WPILib.h"

class PIDTuner
{
public:
	// constructor
	PIDTuner(PIDController*);
	
	// runtime functions
	void Run();
	
	// set functions
	void SetSetpoint(float);
	void SetPIDRange(float);
	
	// get functions
	float GetP();
	float GetI();
	float GetD();
	
private:
	// hardware interfaces
	AnalogChannel	pAdjust;
	AnalogChannel	iAdjust;
	AnalogChannel	dAdjust;
	AnalogChannel	setpointAdjust;
	
	PIDController*	pidControl;
	
	SmartDashboard* dashboard;
	
	// soft variables
	float P;
	float I;
	float D;
	float setpoint;
	float pidScaleFactor;
	float setpointMin;
	float setpointMax;
};
#endif
