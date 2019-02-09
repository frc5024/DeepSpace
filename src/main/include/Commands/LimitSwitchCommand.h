#pragma once

#include <frc/commands/Command.h>
#include <Subsystems/LimitSwitches.h>

class LimitSwitchCommand : public frc::Command {
 public:
  LimitSwitchCommand();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
