//! An interface command for activating the Pull Arm on the robot
#ifndef _HoldArms_HG_
#define _HoldArms_HG_

#include <frc/commands/TimedCommand.h>
#include <Subsystems/Arm.h>

class HoldArms : public frc::TimedCommand {
 public:
  explicit HoldArms(double timeout);
  void Initialize() override;
  void Execute() override;
  void End() override;
  void Interrupted() override;
};

#endif // _HoldArms_HG_