#ifndef CORIOLIS_H_
#define CORIOLIS_H_

#include "WPILib.h"
#include "sysLib.h"

#include "Robot Modules/QueueManager.h"
#include "Libs/Sockets.h"

// Robot Modules
#include "Robot Modules/DriveBase.h"
#include "Robot Modules/RobotShooter.h"
#include "Robot Modules/BridgeTipper.h"

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
        Victor	shootBainBotVictor;
        Victor	intakeRoller;
        Relay	shootRoller;
        
        // bridge tipper relay
        Relay	bridgeTipRelay;
        
        /* input devices */
        Encoder			panEncoder;
        AnalogChannel	tiltPot;
        DigitalInput	bridgeTipUp;
        DigitalInput	bridgeTipDown;
        
        /* pid control loops */
        PIDController	panController;
        PIDController	tiltController;
        
        /* Robot specific stuff. */
        int imageX, imageY;
        
        // robot modules declaration
        DriveBase		robotDrive;
        RobotShooter	robotShooter;
        BridgeTipper	bridgeTipper;
        
        // debugging
        PIDTuner pidTuner;
};

#endif /*CORIOLIS_H_*/
