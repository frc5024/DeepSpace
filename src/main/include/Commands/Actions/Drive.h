//! An interface command for activating the Pull Arm on the robot
#ifndef _Drive_HG_
#define _Drive_HG_

#include <frc/commands/TimedCommand.h>
#include <Subsystems/Arm.h>

class Drive : public frc::TimedCommand {
 public:
  explicit Drive(double speed, double timeout);
  void Initialize() override;
  void Execute() override;
  void End() override;
  void Interrupted() override;
 private:
  double speed;
};

#endif // _Drive_HG_