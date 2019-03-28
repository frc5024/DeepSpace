#ifndef _CLIMBMANAGER_HG_
#define _CLIMBMANAGER_HG_

#include <frc/commands/Command.h>
#include <frc/GenericHID.h>
#include <frc/XboxController.h>

class ClimbManager : public frc::Command {
public:
    enum ClimbState {
        kInactive,
        kAuto,
        kActive
    };
    static ClimbState CurrentClimbState;

    ClimbManager();//!< Class constructor
    void Initialize() override; //!< Runs once on initalization
    void Execute() override;    //!< Called in a loop during Teleop
    bool IsFinished() override;
    void End() override;         //!< Runs once when IsFinished() returns true
    void Interrupted() override; //!< Runs once if the command is forced to stop
    frc::XboxController* pJoyOp;
    void UpdateRumble(void); //!< Updates whether the controller should be rumbleing or not    
};

#endif //__CLIMBMANAGER_HG_
