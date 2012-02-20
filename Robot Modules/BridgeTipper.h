#ifndef BRIDGETIPPER_H_
#define BRIDGETIPPER_H_

#include "WPILib.h"

class BridgeTipper
{
public:
	BridgeTipper(Relay*, DigitalInput*, DigitalInput*);
	
	void Move();
	
	void ControlThread();
	
private:
	Relay*			motorControl;
	DigitalInput*	upLimit;
	DigitalInput*	downLimit;
	
	bool stopped;
	bool goingUp;
};

#endif /*BRIDGETIPPER_H_*/
