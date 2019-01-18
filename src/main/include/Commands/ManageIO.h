//! An interface command for activating the Pull Arm on the robot
#ifndef _MANAGEIO_HG_
#define _MANAGEIO_HG_

#include <frc/commands/Command.h>
#include <frc/WPILib.h>
#include "RobotMap.h"
#include <frc/GenericHID.h>

class ManageIO : public frc::Command {
    public:
    ManageIO();                  //!< Class constructor
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

    frc::XboxController* pJoyDrive;

};    
#endif // _MANAGEIO_HG_