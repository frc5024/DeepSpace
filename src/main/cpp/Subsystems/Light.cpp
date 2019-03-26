#include "Subsystems/Light.h"

Light::Light() : frc::Subsystem("Light") {
  this->pLight = new frc::Solenoid(PCM_CAN_ID, LIGHT_ID);
}

void Light::InitDefaultCommand() {
  SetDefaultCommand(new ControlLight());
}

void Light::On() {
	this->pLight->Set(true);
}

void Light::Off() {
	this->pLight->Set(false);
}