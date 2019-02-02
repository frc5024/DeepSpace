#include "Subsystems/HallEffect.h"
#include "Robot.h"
#include "RobotMap.h"

HallEffect::HallEffect() : Subsystem("HallEffect") {}

void HallEffect::InitDefaultCommand() {
  //Set the default command for a subsystem here.
   SetDefaultCommand(new DriveWithJoystick()); // todo: change later
}

bool HallEffect::nearMagnet1() {
  return this->hallSensor1->Get();
}

bool HallEffect::nearMagnet2() {
  return this->hallSensor2->Get();
}