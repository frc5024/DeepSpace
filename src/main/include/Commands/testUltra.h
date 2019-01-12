#pragma once

#include <frc/commands/Command.h>
#include <Subsystems/DriveTrain.h>
#include <Subsystems/Climb.h>
#include "RobotMap.h"
#include <frc/GenericHID.h>

class testUltra : public frc::Command {
 public:
  testUltra();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
