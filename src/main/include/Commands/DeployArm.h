//! An interface command for activating the Pull Arm on the robot
#ifndef _DEPLOYARM_HG_
#define _DEPLOYARM_HG_

#include <frc/commands/TimedCommand.h>
#include <Subsystems/Arm.h>

class DeployArm : public frc::TimedCommand {
 public:
  explicit DeployArm(double timeout);
  void Initialize() override;
  void Execute() override;
  void End() override;
  void Interrupted() override;
};

#endif // _DEPLOYARM_HG_