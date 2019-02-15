#include "Subsystems/Flap.h"

Flap::Flap() : frc::Subsystem("Flap") {
  this->pSolenoid = new frc::DoubleSolenoid(PCM_CAN_ID, FLAP_ID_FORWARD, FLAP_ID_REVERSE);
}

void Flap::InitDefaultCommand() {
  SetDefaultCommand(new ControlSlider());
}

void Flap::Deploy() {
	this->pSolenoid->Set(frc::DoubleSolenoid::Value::kForward);
}

void Flap::Retract() {
	this->pSolenoid->Set(frc::DoubleSolenoid::Value::kReverse);
}

void Flap::Release(){
  this->pSolenoid->Set(frc::DoubleSolenoid::Value::kOff);
}