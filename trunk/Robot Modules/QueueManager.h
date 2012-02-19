#ifndef QUEUEMANAGER_H_
#define QUEUEMANAGER_H_

#include "WPILib.h"

class QueueManager
{
public:
	QueueManager(int intake, int feed, int intakeMotor, int feedMotor);
	void handle(Joystick *joy);
	void dump(SmartDashboard *dashBoard);
	void reset();
	virtual ~QueueManager();
	
private:
	DigitalInput m_intake, m_feed;
	Relay m_intakeMotor, m_feedMotor;
	float m_currentCount;
	bool m_in, m_fed, m_prevIn, m_prevFed;
};

#endif /*QUEUEMANAGER_H_*/
