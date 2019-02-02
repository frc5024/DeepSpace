#ifndef _HALLEFFECTTEST_HG_
#define _HALLEFFECTTEST_HG_

#include <frc/commands/Command.h>
#include <Subsystems/HallEffect.h>

class HallEffectTest : public frc::Command {
 public:
  HallEffectTest();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};

#endif // _HALLEFFECTTEST_HG_