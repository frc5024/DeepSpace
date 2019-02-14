//! An interface command for activating the Pull Arm on the robot
#ifndef _HoldLegs_HG_
#define _HoldLegs_HG_

#include <frc/commands/TimedCommand.h>
#include <Subsystems/Leg.h>

class HoldLegs : public frc::TimedCommand {
 public:
  explicit HoldLegs(double timeout);
  void Initialize() override;
  void Execute() override;
  void End() override;
  void Interrupted() override;
};

#endif // _HoldLegs_HG_