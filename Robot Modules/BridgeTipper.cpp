#ifndef BRIDGETIPPER_CPP_
#define BRIDGETIPPER_CPP_

#include "BridgeTipper.h"

BridgeTipper::BridgeTipper(Relay* bridgeTipControl, DigitalInput* bridgeTipUp, DigitalInput* bridgeTipDown)
{
	// save pointers
	motorControl = bridgeTipControl;
	upLimit = bridgeTipUp;
	downLimit = bridgeTipDown;
	
	// always start in the up position
	stopped = true;
	goingUp = false;
}

void BridgeTipper::Move()
{
	stopped = false;
	goingUp = !goingUp;
}

void BridgeTipper::ControlThread()
{
	if (!stopped)
	{
		if (goingUp)
		{
			motorControl->Set(Relay::kForward);
		}
		else
		{
			motorControl->Set(Relay::kReverse);
		}
	}
	else
	{
		motorControl->Set(Relay::kOff);
	}
}

#endif /*BRIDGETIPPER_CPP_*/
