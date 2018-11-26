#ifndef _DRIVEWITHJOYSTICK_HG_
#define _DRIVEWITHJOYSTICK_HG_

#include <Commands/Command.h>
#include <Subsystems/DriveTrain.h>

class DriveWithJoystick : public frc::Command {
 public:
  DriveWithJoystick();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
private:
int directionMultiplier;
double speedMultiplier;

double speed;
double rotation;

frc::XboxController* pJoyDrive;
};

#endif // _DRIVEWITHJOYSTICK_HG_