//! An interface command for activating the Pull Arm on the robot
#ifndef _EndClimb_HG_
#define _EndClimb_HG_

#include <frc/commands/TimedCommand.h>
#include <Subsystems/Arm.h>
#include <Commands/ClimbManager.h>
#include <frc/GenericHID.h>

class EndClimb : public frc::TimedCommand {
 public:
  explicit EndClimb(double timeout);
  void Initialize() override;
  void Execute() override;
  void End() override;
  void Interrupted() override;
 private:
  frc::XboxController* pJoyDrive; //!< A mnemonic for the driver's controller
};

#endif // _EndClimb_HG_