//! An interface command for controlling the cargo chute
#ifndef _CONTROLCARGO_HG_
#define _CONTROLCARGO_HG_

#include <frc/commands/Command.h>
#include <Subsystems/Cargo.h>
#include "RobotMap.h"
#include <frc/GenericHID.h>
#include <frc/WPILib.h>

class ControlCargo : public frc::Command {
 public:
  ControlCargo();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
  private:
  double speed; 
  frc::XboxController* pJoyOp; 
};

#endif // _CONTROLCARGO_HG_