#include "Subsystems/Arm.h"

Arm::Arm() : Subsystem("Arm") {
  // Initialize the motors
  this->pArmMotor = new frc::Spark(CLIMB_ARM_MOTOR);

  this->pArmMotor->SetSafetyEnabled(false);

}

void Arm::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void Arm::MoveArm(double Speed) {
  this->pArmMotor->Set(Speed);
}

double Arm::getDistanceFromFloor() {
  double range = m_ultrasonic.GetValue() * kValueToInches;
  return range;
}