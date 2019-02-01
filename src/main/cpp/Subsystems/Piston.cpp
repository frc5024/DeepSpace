#include "Subsystems/Piston.h"

Piston::Piston() : frc::Subsystem("Piston") {
  this->pSolenoid = new frc::Solenoid(PCM_CAN_ID, PISTON_ID);
}

void Piston::InitDefaultCommand() {
  SetDefaultCommand(new ControlSlider());
}

void Piston::Deploy() {
	this->pSolenoid->Set(true);
}

void Piston::Retract() {
	this->pSolenoid->Set(false);
}