#include "Subsystems/HatchGripper.h"

HatchGripper::HatchGripper() : frc::Subsystem("HatchGripper") {
  this->pHatchSolenoid = new frc::DoubleSolenoid(HatchGripper_FORWARD_ID, HatchGripper_REVERSE_ID);
}

void HatchGripper::InitDefaultCommand() {
  SetDefaultCommand(new ControlHatchGripper());
}

void HatchGripper::Deploy() {
	this->pHatchSolenoid->Set(frc::DoubleSolenoid::Value::kForward);
}

void HatchGripper::Retract() {
	this->pHatchSolenoid->Set(frc::DoubleSolenoid::Value::kReverse);
}

void HatchGripper::TurnOff() {
	this->pHatchSolenoid->Set(frc::DoubleSolenoid::Value::kOff);
}