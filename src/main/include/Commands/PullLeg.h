//! An interface command for activating the Pull Arm on the robot
#ifndef _PULLLEG_HG_
#define _PULLLEG_HG_

#include <frc/commands/Command.h>
#include <Subsystems/Leg.h>
#include "RobotMap.h"
#include <frc/GenericHID.h>

class PullLeg : public frc::Command {
    public:
    PullLeg();                  //!< Class constructor
    void Initialize() override; //!< Runs once on initalization
    void Execute() override;    //!< Called in a loop during Teleop
    
    /**
     * Used to tell wpilib if the command is fully finished. This should never return true
     * Because we always want to be able to drive the bot during teleop
     *
     * @return True if command is finished, else false
     */
    bool IsFinished() override;
    
    void End() override;         //!< Runs once when IsFinished() returns true
    void Interrupted() override; //!< Runs once if the command is forced to stop                


    private:
    double speedMultiplier;

    double speed;  

    frc::XboxController* pJoyDrive;

};    
#endif // _PULLLEG_HG_