#include "Subsystems/Leg.h"

Leg::Leg() : Subsystem("Leg Subsystem") {
   // Initialize the motors
  this->pLegMotor = new can::WPI_VictorSPX(CLIMB_LEG_MOTOR);
  
  this->pLegMotor->SetNeutralMode(NeutralMode::Brake);

	this->pLegMotor->SetSafetyEnabled(false);
}

void Leg::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void Leg::MoveLeg(double Speed) {
  this->pLegMotor->Set(Speed);
}