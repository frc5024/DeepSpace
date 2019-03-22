#include "Subsystems/Arm.h"

Arm::Arm() : Subsystem("Arm") {
  // Initialize the motors
  this->pArmMotor = new can::WPI_TalonSRX(CLIMB_ARM_MOTOR);
  this->pArmMotor->SetNeutralMode(NeutralMode::Brake);

  this->pArmMotor->SetSafetyEnabled(false);

  this->pArmMotor2 = new can::WPI_TalonSRX(CLIMB_ARM_MOTOR_2);
  this->pArmMotor2->SetNeutralMode(NeutralMode::Brake);

  this->pArmMotor2->SetSafetyEnabled(false);

  Log("Building GearBox");
  this->pArmGearBox->motor = new frc::SpeedControllerGroup(*this->pArmMotor, *this->pArmMotor2);
}

void Arm::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void Arm::MoveArm(double Speed) {
  this->pArmGearBox->motor->Set(Speed);
}

double Arm::getDistanceFromFloor() {
  double range = m_ultrasonic.GetValue() * kValueToInches;
  return range;
}