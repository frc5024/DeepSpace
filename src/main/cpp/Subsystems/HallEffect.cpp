#include "Subsystems/HallEffect.h"
#include "Robot.h"
#include "RobotMap.h"

HallEffect::HallEffect() : Subsystem("HallEffect") {
  this->hallSensor1 = new frc::DigitalInput(3);
  this->hallSensor2 = new frc::DigitalInput(4);
}

void HallEffect::InitDefaultCommand() {
   SetDefaultCommand(new HallEffectTest());
}

bool HallEffect::nearMagnet1() {
  return this->hallSensor1->Get();
}

bool HallEffect::nearMagnet2() {
  return this->hallSensor2->Get();
}