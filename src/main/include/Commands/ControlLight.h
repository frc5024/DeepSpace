//! An interface command for toggling the green light on the robot
#ifndef _CONTROLLIGHT_HG_
#define _CONTROLLIGHT_HG_

#include <frc/commands/Command.h>
#include <Subsystems/Light.h>
#include "RobotMap.h"
#include <frc/WPILib.h>
#include <frc/GenericHID.h>

class ControlLight : public frc::Command {
 public:
  ControlLight();             //!< Class constructor
  void Initialize() override; //!< Runs once on initalization
  void Execute() override;    //!< Called in a loop during Teleop
  bool IsFinished() override;
  void End() override;         //!< Runs once when IsFinished() returns true
  void Interrupted() override; //!< Runs once if the command is forced to stop
  
private:
	bool state; //!< The current state that the green light is in (true for on and false for off)
	frc::XboxController* pJoyOp; //!< A mnemonic for the driver's controller
};

#endif // _CONTROLLIGHT_HG_