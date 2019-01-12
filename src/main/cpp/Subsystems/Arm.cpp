#include "Subsystems/Arm.h"

Arm::Arm() : Subsystem("Arm") {
  // Initialize the motors
  this->pArmMotor = new can::WPI_TalonSRX(CLIMB_ARM_MOTOR);

  this->pArmMotor->SetNeutralMode(NeutralMode::Brake);

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