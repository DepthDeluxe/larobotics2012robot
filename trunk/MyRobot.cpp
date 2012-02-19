#include "WPILib.h"
#include "Coriolis.h"

/*
 * Starter function for them tasks. Please DO NOT screw around with me!
 */
static void startThread(Coriolis *ptr, int id) {
	if (id == 1) // Control thread id.
	{
		printf("CORIOLIS: Beginning ControlTask...\n");
		ptr->ControlTask();
	} else if (id == 2) // Autonomous ID.
	{
		printf("CORIOLIS: Beginning AutonomousTask...\n");
		ptr->AutonomousTask();
	} else if (id == 3)
	{
		printf("CORIOLIS: Server task starting...\n");
		ptr->ServerTask();
	}
}

Coriolis::Coriolis(void) :
	autoThread("autonomousThread", (FUNCPTR) startThread),
	controlThread("controlThread", (FUNCPTR) startThread),
	serverThread("serverThread", (FUNCPTR) startThread),
	leftDrive(4), rightDrive(5), left(1), right(2), loGear(4), hiGear(5),
	panVictor(6), tiltVictor(7),
	shootVictor(8),
	panEncoder(5,6), tiltEncoder(7,8),
	panController(0, 0, 0, &panEncoder, &panVictor),
	tiltController(0, 0, 0, &tiltEncoder, &tiltVictor),
	robotDrive(&leftDrive, &rightDrive, &loGear, &hiGear),
	robotShooter(&panVictor, &tiltVictor, &shootVictor, &panController, &tiltController)
{
	printf("CORIOLIS: Initializing.\n");
	semaphore = semMCreate(SEM_Q_PRIORITY | SEM_INVERSION_SAFE | SEM_DELETE_SAFE);
	
	/* Constructs. */
	printf("CORIOLIS: Successfully initialized and configured. Ready to start!\n");
}

/*
 * This function should not be edited AT ALL. If not carefully arranged, the robot code 
 * could malfunction uncotnrollably. Edit only in the places with seperate source files.
 */
void Coriolis::RobotMain(void) {
	printf("CORIOLIS: Main thread started.\n");
	bool alreadyAuto = false;
	controlThread.Start((INT32) this, 1);
	//serverThread.Start((INT32) this, 3);
	int i = 0;

	while (true) 
	{
		/*
		 * Driver control.
		 */
		if (IsOperatorControl() && IsEnabled()) 
		{
			Teleop();
			if (i % 250 == 0)
				printf("CORIOLIS:Teleop(): Alive...\n");
		}
		/*
		 * BEGIN an autonomous task.
		 */
		else if (IsAutonomous() && IsEnabled() && !alreadyAuto) 
		{
			autoThread.Start((INT32) this, 2);
			alreadyAuto = true;
		}
		/*
		 * END the autonomous task.
		 */
		else if (IsAutonomous() && IsDisabled() && alreadyAuto)
		{
			autoThread.Stop();
			alreadyAuto = false;
		}
		/*
		 * Disabled.
		 */
		else if (IsDisabled())
		{
			alreadyAuto = false;
			Disabled();
			if (i % 250 == 0)
				printf("CORIOLIS:Disabled(): Alive...\n");
		}
		
		if (i % 100 == 0)
			ToggleRIOUserLED();
		
		Wait(0.005);
		i++;
	}
}

START_ROBOT_CLASS(Coriolis)
