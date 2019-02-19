//! An interface command for toggleing the gripper
#ifndef _CONTROLHATCHGRIPPER_HG_
#define _CONTROLHATCHGRIPPER_HG_

#include <frc/commands/Command.h>
#include <Subsystems/HatchGripper.h>
#include "RobotMap.h"
#include <frc/WPILib.h>
#include <frc/GenericHID.h>

class ControlHatchGripper : public frc::Command {
 public:
  ControlHatchGripper();             //!< Class constructor
  void Initialize() override; //!< Runs once on initalization
  void Execute() override;    //!< Called in a loop during Teleop
  bool IsFinished() override;
  void End() override;         //!< Runs once when IsFinished() returns true
  void Interrupted() override; //!< Runs once if the command is forced to stop
  
private:
	double speed;
	frc::XboxController* pJoyOp; //!< A mnemonic for the operator's controller
};

#endif // _CONTROLHATCHGRIPPER_HG_