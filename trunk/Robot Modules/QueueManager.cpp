#include "QueueManager.h"

QueueManager::QueueManager(int intake, int feed, int intakeMotor, int feedMotor) :
	m_intake(intake), m_feed(feed), m_intakeMotor(intakeMotor),
	m_feedMotor(feedMotor), m_currentCount(0.0) {
	m_in = m_prevIn = m_intake.Get();
	m_fed = m_prevFed = m_feed.Get();
}

void QueueManager::handle(Joystick *joy) {
	m_in = m_intake.Get();
	m_fed = m_feed.Get();
	
	if (m_in != m_prevIn) {
		m_currentCount = m_currentCount + 0.5;
		m_prevIn = m_in;
	}
	if (m_fed != m_prevFed) {
		m_currentCount = m_currentCount - 0.5;
		m_prevFed = m_fed;
	}
	if (m_currentCount < 0.0)
		m_currentCount = 0.0;

	// Intake Manager.
	if (m_currentCount >= 2.5) {
		m_intakeMotor.Set(Relay::kOff);
	} else
		m_intakeMotor.Set(Relay::kForward);

	// Feed Manager.
	if (!m_fed) {
		if (joy->GetTrigger()) {
			m_feedMotor.Set(Relay::kForward);
			Wait(0.5);
		} else
			m_feedMotor.Set(Relay::kOff);
	} else
		m_feedMotor.Set(Relay::kForward);
}

void QueueManager::dump(SmartDashboard *dashBoard)
{
	dashBoard->PutBoolean("Intake", m_in);
	dashBoard->PutBoolean("Feed", m_fed);
	dashBoard->PutDouble("Current Count", (double)m_currentCount);
}

void QueueManager::reset()
{
	m_currentCount = 0.0;
}

QueueManager::~QueueManager() {
}
