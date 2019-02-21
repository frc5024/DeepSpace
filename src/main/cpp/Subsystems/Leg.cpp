#include "Subsystems/Leg.h"

Leg::Leg() : Subsystem("Leg Subsystem") {
	// Initialize the motors
	this->pLegMotor = new can::WPI_TalonSRX(CLIMB_LEG_MOTOR);

	this->pLegMotor->SetNeutralMode(NeutralMode::Brake);

	this->pLegMotor->SetSafetyEnabled(false);

	this->pTopHall = new frc::DigitalInput(LEG_PIN_TOP);

	this->pMiddleHall = new frc::DigitalInput(LEG_PIN_MIDDLE);

	this->pBottomHall = new frc::DigitalInput(LEG_PIN_BOTTOM);
}

void Leg::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void Leg::MoveLeg(double spd)
{
	if (spd > 0.0 && this->AtTop()
	||  spd < 0.0 && this->AtBottom())
		spd = 0.0 ;

	this->pLegMotor->Set(spd) ;
}

bool Leg::AtTop(void)
{
	return ! this->pTopHall->Get() ;
}

bool Leg::AtMiddle(void)
{
	return ! this->pMiddleHall->Get() ;
}

bool Leg::AtBottom(void)
{
	return ! this->pBottomHall->Get() ;
}
