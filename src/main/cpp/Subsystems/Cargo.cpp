#include "Subsystems/Cargo.h"

Cargo::Cargo() : frc::Subsystem("Cargo") {
  this->pSolenoid = new frc::DoubleSolenoid(CARGO_PISTON_FORWARD_ID, CARGO_PISTON_BACKWARD_ID);
}

void Cargo::InitDefaultCommand() {
  SetDefaultCommand(new ControlCargo());
}

void Cargo::Deploy() {
	this->pSolenoid->Set(frc::DoubleSolenoid::Value::kForward);
}

void Cargo::Retract() {
	this->pSolenoid->Set(frc::DoubleSolenoid::Value::kReverse);
}

void Cargo::Release(){
  this->pSolenoid->Set(frc::DoubleSolenoid::Value::kOff);
}