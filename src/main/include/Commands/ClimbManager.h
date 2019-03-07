//! An interface command for managing the climb mechanism
#ifndef _CLIMBMANAGER_HG_
#define _CLIMBMANAGER_HG_

#include <frc/commands/Command.h>
#include <frc/GenericHID.h>
#include <frc/XboxController.h>

class ClimbManager : public frc::Command {
  public:
   /**
    * Enum for all the possible climb state's 
    */
    enum ClimbState {
      kInactive,
      kActive
    };

    static ClimbState CurrentClimbState; //!< States the current climb state of the robot

    ClimbManager();             //!< Class constructor
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

	  frc::XboxController* pJoyDrive; //!< A mnemonic for the driver's controller because we are lazy 
};

#endif //__CLIMBMANAGER_HG_