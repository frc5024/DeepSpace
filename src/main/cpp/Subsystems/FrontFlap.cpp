#include "Subsystems/FrontFlap.h"

Flap::Flap() : frc::Subsystem("FrontFlap") {
  this->pSolenoid = new frc::DoubleSolenoid(PCM_CAN_ID,FRONTFLAP_ID_FORWARD, FRONTFLAP_ID_REVERSE);
}

void FrontFlap::InitDefaultCommand() {
  SetDefaultCommand(new ControlCargo());
}

void FrontFlap::Deploy() {
	this->pSolenoid->Set(frc::DoubleSolenoid::Value::kForward);
}

void FrontFlap::Retract() {
	this->pSolenoid->Set(frc::DoubleSolenoid::Value::kReverse);
}

void FrontFlap::Release(){
  this->pSolenoid->Set(frc::DoubleSolenoid::Value::kOff);
}