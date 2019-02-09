#include "Subsystems/HallEffect.h"
#include "Robot.h"
#include "RobotMap.h"

HallEffect::HallEffect() : Subsystem("HallEffect") {
  this->hallSensor1 = new frc::DigitalInput(6);
  this->hallSensor2 = new frc::DigitalInput(5);
  this->hallSensor3 = new frc::DigitalInput(1);
  this->hallSensor4 = new frc::DigitalInput(2);
  this->hallSensor5 = new frc::DigitalInput(0);
  this->hallSensor6 = new frc::DigitalInput(3);
  this->hallSensor7 = new frc::DigitalInput(4);

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

bool HallEffect::nearMagnet3() {
  return this->hallSensor3->Get();
}

bool HallEffect::nearMagnet4() {
  return this->hallSensor4->Get();
}

bool HallEffect::nearMagnet5() {
  return this->hallSensor5->Get();
}

bool HallEffect::nearMagnet6() {
  return this->hallSensor6->Get();
}

bool HallEffect::nearMagnet7() {
  return this->hallSensor7->Get();
}