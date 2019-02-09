#include "Subsystems/Cargo.h"

Cargo::Cargo() : frc::Subsystem("Cargo") {
  this->pSolenoid = new frc::Solenoid(PCM_CAN_ID, CARGO_PISTON_ID);
}

void Cargo::InitDefaultCommand() {
  SetDefaultCommand(new ControlCargo());
}

void Cargo::Deploy() {
	this->pSolenoid->Set(true);
}

void Cargo::Retract() {
	this->pSolenoid->Set(false);
}