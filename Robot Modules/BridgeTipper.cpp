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
	goingDown = true;
	
	dashboard = SmartDashboard::GetInstance();
}

void BridgeTipper::Move()
{
	stopped = false;
	goingDown = !goingDown;
}

void BridgeTipper::ControlThread()
{
	if (!stopped)
	{
		if (goingDown)
		{
			motorControl->Set(Relay::kForward);
			stopped = !((bool)downLimit->Get());
		}
		else
		{
			motorControl->Set(Relay::kReverse);
			stopped = !((bool)upLimit->Get());
		}
	}
	else
	{
		motorControl->Set(Relay::kOff);
	}
	
	dashboard->PutInt("Down Limit Switch", downLimit->Get());
	dashboard->PutInt("Up Limit Switch", upLimit->Get());
}

#endif /*BRIDGETIPPER_CPP_*/
