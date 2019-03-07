//! An interface command for activating the Pull Arm on the robot
#ifndef _DEPLOYLEG_HG_
#define _DEPLOYLEG_HG_

#include <frc/commands/TimedCommand.h>
#include <Subsystems/Leg.h>

class DeployLeg : public frc::TimedCommand {
 public:
  explicit DeployLeg(double timeout, double speed); //!< Class constructor
  void Initialize() override;                       //!< Runs once on initalization
  void Execute() override;
  void End() override;
  void Interrupted() override; //!< Runs once if the command is forced to stop
  double speed;
};

#endif // _DEPLOYLEG_HG_