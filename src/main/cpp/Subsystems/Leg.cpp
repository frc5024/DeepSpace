#include "Subsystems/Leg.h"

Leg::Leg() : Subsystem("Leg Subsystem") {
	// Initialize the motors
	this->pLegMotor = new can::WPI_TalonSRX(CLIMB_LEG_MOTOR);

	this->pLegMotor->SetNeutralMode(NeutralMode::Brake);

	this->pLegMotor->SetSafetyEnabled(false);

	this->pTopHall = new frc::DigitalInput(LEG_PIN_TOP);

	this->pMiddleHall = new frc::DigitalInput(LEG_PIN_MIDDLE);

	this->pBottomHall = new frc::DigitalInput(LEG_PIN_BOTTOM);

	this->legPosition = Quadrant::Q_TOP ;
}

void Leg::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void Leg::MoveLeg(double spd) {

	// If we're braking, there's no point is checking anything
	if (spd == 0.0) {
		this->pLegMotor->Set(spd);
		return;
	}

	switch (this->legPosition)
	{
		case Q_TOP_MIDDLE :
			if (spd > 0.0) // If we're going down
			{ 
				this->pLegMotor->Set(spd) ; // Go down
				if (this->AtMiddle()) // If we're at the middle
				{ 
					this->legPosition = Q_MIDDLE ; // We know where we are
				}
			}
			else // If we're going up
			{ 
				if (this->AtTop()) // If we're at the top
				{ 
					this->legPosition = Q_TOP ; // We know where we are
					this->pLegMotor->Set(0.0) ; // Brake
				}
				else
				{
					this->pLegMotor->Set(spd) ; // Go up
				}
			}
			break;
		case Q_MIDDLE_BOTTOM :
			if (spd > 0.0) // If we're going down
			{
				if (this->AtBottom()) // If we're at the bottom
				{
					this->legPosition = Q_BOTTOM ; // We know where we are
					this->pLegMotor->Set(0.0) ; // Brake
				}
				else
				{
					this->pLegMotor->Set(spd) ; // Go down
				}
			}
			else // If we're going up
			{
				this->pLegMotor->Set(spd) ; // Go up
				if (this->AtMiddle()) // If we're at the middle
				{
					this->legPosition = Q_MIDDLE ; // We know where we are
				}
			}
			break;
		case Q_TOP :
			if (spd > 0.0) // If we're going down
			{
				this->pLegMotor->Set(spd) ; // Go down
				this->legPosition = Q_TOP_MIDDLE ; // We're somewhere in here
			}
			break;
		case Q_MIDDLE :
			this->pLegMotor->Set(spd) ; // Safe to move either direction
			if (spd > 0.0) // If we're going down
			{
				this->legPosition = Q_MIDDLE_BOTTOM ; // We're somewhere in here
			}
			else // If we're going up
			{
				this->legPosition = Q_TOP_MIDDLE ; // We're somewhere in here
			}
			break;
		case Q_BOTTOM :
			if (spd < 0.0) // If we're going up
			{
				this->pLegMotor->Set(spd) ; // Go up
				this->legPosition = Q_MIDDLE_BOTTOM ; // We're somewhere in here
			}
			break;
		default:
			break;
	}
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

Leg::Quadrant Leg::GetPosition(void)
{
	return this->legPosition ;
}
