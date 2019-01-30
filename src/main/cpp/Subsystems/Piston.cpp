#include "Subsystems/Piston.h"

Piston::Piston() : frc::Subsystem("Piston") {
  this->pSolenoid = new frc::DoubleSolenoid(PCM_CAN_ID, PISTON_FORWARD_ID, PISTON_BACKWARD_ID);
}

void Piston::InitDefaultCommand() {
  SetDefaultCommand(new ControlSlider());
}

void Piston::Deploy() {
	this->pSolenoid->Set(frc::DoubleSolenoid::Value::kForward);
}

void Piston::Retract() {
	this->pSolenoid->Set(frc::DoubleSolenoid::Value::kReverse);
}

void Piston::Release() {
	this->pSolenoid->Set(frc::DoubleSolenoid::Value::kOff);
}