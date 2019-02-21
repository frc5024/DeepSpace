#include "Subsystems/Arm.h"

Arm::Arm() : Subsystem("Arm") {
	// Initialize the motors
	this->pArmMotor = new can::WPI_TalonSRX(CLIMB_ARM_MOTOR);
	this->pArmMotor->SetNeutralMode(NeutralMode::Brake);

	this->pArmMotor->SetSafetyEnabled(false);

	this->pArmMotor2 = new can::WPI_TalonSRX(CLIMB_ARM_MOTOR_2);
	this->pArmMotor2->SetNeutralMode(NeutralMode::Brake);

	this->pArmMotor2->SetSafetyEnabled(false);

	this->pArmHall = new frc::DigitalInput(ARM_PIN_LOWERED) ;
}

void Arm::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

void Arm::MoveArm(double speed)
{
	this->pArmMotor->Set(speed);
	this->pArmMotor2->Set(speed);
}

bool Arm::GetSensor(void)
{
	return ! this->pArmHall->Get() ;
}