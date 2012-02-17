#ifndef CORIOLIS_H_
#define CORIOLIS_H_

#include "WPILib.h"
#include "sysLib.h"

#include "Libs/QueueManager.h"
#include "Libs/Sockets.h"

#define LO_GEAR 0
#define HI_GEAR 1

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
        Task autoThread;
        Task controlThread;
        Task serverThread;
        SEM_ID semaphore;
        Victor leftDrive, rightDrive;
        Joystick left, right;
        Solenoid loGear, hiGear;
        
        /* shooter motors */
        Victor	panVictor, tiltVictor;
        
        /* encoders */
        Encoder		panEncoder, tiltEncoder;
        
        /* pid control loops */
        PIDController	panController;
        PIDController	tiltController;
        
        /* Robot specific stuff. */
        int imageX, imageY;
        int gear;
        float leftPower, rightPower;
        float panSetpoint, tiltSetpoint;
};

#endif /*CORIOLIS_H_*/
