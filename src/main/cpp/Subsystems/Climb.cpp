#include "Subsystems/Climb.h"

Climb::Climb() : Subsystem("Climb") {
  // Initialize the motors
  this->pArmMotor = new can::WPI_TalonSRX(CLIMB_ARM_MOTOR);
  this->pLegMotor = new can::WPI_TalonSRX(CLIMB_LEG_MOTOR);

  this->pArmMotor->SetNeutralMode(NeutralMode::Brake);
  this->pLegMotor->SetNeutralMode(NeutralMode::Brake);

  this->pArmMotor->SetSafetyEnabled(false);
	this->pLegMotor->SetSafetyEnabled(false);

}

void Climb::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void Climb::MoveArm(double Speed) {
  this->pArmMotor->Set(Speed);
}

void Climb::MoveLeg(double Speed) {
  this->pLegMotor->Set(Speed);
}

double Climb::getDistanceFromFloor() {
  double range = m_ultrasonic.GetValue() * kValueToInches;
  return range;
}