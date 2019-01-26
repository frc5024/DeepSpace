//#pragma once
#ifndef _HALLEFFECT_HG_
#define _HALLEFFECT_HG_

#include "Subsystems/HallEffect.h"

HallEffect::HallEffect() : Subsystem("HalllEffect") {}

void HallEffect::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
#endif // _HALLEFFECT_HG_