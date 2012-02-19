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
	void SetPIDRange(float, float);
	void SetSetpointRange(float, float);
	void SetSetpoint(float);
	
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
	float minPIDValue;
	float maxPIDValue;
	float pidValMultiplier;
	float minSetpointValue;
	float maxSetpointValue;
	float setpointValMultiplier;
};
#endif
