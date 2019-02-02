#include "Subsystems/HallEffect.h"
#include "Robot.h"
#include "RobotMap.h"

HallEffect::HallEffect() : Subsystem("HallEffect") {}

void HallEffect::InitDefaultCommand() {
   SetDefaultCommand(new HallEffectTest());
}

bool HallEffect::nearMagnet1() {
  return this->hallSensor1->Get();
}

bool HallEffect::nearMagnet2() {
  return this->hallSensor2->Get();
}