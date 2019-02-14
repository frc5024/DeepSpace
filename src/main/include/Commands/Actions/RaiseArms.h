//! An interface command for activating the Pull Arm on the robot
#ifndef _RaiseArms_HG_
#define _RaiseArms_HG_

#include <frc/commands/TimedCommand.h>
#include <Subsystems/Arm.h>

class RaiseArms : public frc::TimedCommand {
 public:
  explicit RaiseArms(double speed, double timeout);
  void Initialize() override;
  void Execute() override;
  void End() override;
  void Interrupted() override;
 private:
  double speed;
};

#endif // _RaiseArms_HG_