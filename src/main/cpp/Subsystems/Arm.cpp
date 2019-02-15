#include "Subsystems/Arm.h"

Arm::Arm() : Subsystem("Arm") {
  // Initialize the motors
  this->pArmMotor = new can::WPI_TalonSRX(CLIMB_ARM_MOTOR);
  this->pArmMotor->SetNeutralMode(NeutralMode::Brake);

  this->pArmMotor->SetSafetyEnabled(false);

  this->pArmMotor2 = new can::WPI_TalonSRX(CLIMB_ARM_MOTOR_2);
  this->pArmMotor2->SetNeutralMode(NeutralMode::Brake);

  this->pArmMotor2->SetSafetyEnabled(false);

  this->pGyro = new AHRS(SPI::Port::kMXP);
  this->pGyro->Reset();
}

void Arm::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void Arm::MoveArm(double Speed) {
  this->pArmMotor->Set(Speed);
  this->pArmMotor2->Set(Speed);
}

double Arm::getDistanceFromFloor() {
  double range = m_ultrasonic.GetValue() * kValueToInches;
  return range;
}

float Arm::GetAngle() {
  return this->pGyro->GetPitch() * -1;
}