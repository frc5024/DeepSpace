//#pragma once
#ifndef _HALLEFFECT_HG_
#define _HALLEFFECT_HG_

#include <frc/commands/Subsystem.h>

class HallEffect : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

 public:
  HallEffect();
  void InitDefaultCommand() override;
};

#endif // _HALLEFFECT_HG_