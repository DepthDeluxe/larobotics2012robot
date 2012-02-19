#ifndef CORIOLIS_H_
#define CORIOLIS_H_

#include "WPILib.h"
#include "sysLib.h"

#include "Robot Modules/QueueManager.h"
#include "Libs/Sockets.h"

// Robot Modules
#include "Robot Modules/DriveBase.h"
#include "Robot Modules/RobotShooter.h"

// Utilities
#include "Utility/PIDTuner.h"

class Coriolis: public SimpleRobot {

public:
        Coriolis(void);
        void RobotMain(void);
        void AutonomousTask(void);
        void ControlTask(void);
        void ServerTask(void);
        void Disabled(void);
        void Teleop(void);

private:
        Task		autoThread;
        Task		controlThread;
        Task		serverThread;
        SEM_ID		semaphore;
        Victor		leftDrive, rightDrive;
        Joystick	left, right;
        Solenoid	loGear, hiGear;
        
    	/* shooter motors */
        Victor	panVictor, tiltVictor;
        Victor	shootVictor;
        
        /* input devices */
        Encoder			panEncoder;
        AnalogChannel	tiltPot;
        
        /* pid control loops */
        PIDController	panController;
        PIDController	tiltController;
        
        /* Robot specific stuff. */
        int imageX, imageY;
        
        // robot modules declaration
        DriveBase		robotDrive;
        RobotShooter	robotShooter;
        
        // debugging
        PIDTuner pidTuner;
};

#endif /*CORIOLIS_H_*/
