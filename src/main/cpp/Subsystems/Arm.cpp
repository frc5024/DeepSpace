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

	// Current limiting for motor 1
	this->pArmMotor->ConfigPeakCurrentLimit(ARM_CURRENT_THRESHOLD, ARM_PEAK_TIMEOUT);
	this->pArmMotor->ConfigPeakCurrentDuration(ARM_CURRENT_TIMEOUT, ARM_PEAK_TIMEOUT);
	this->pArmMotor->ConfigContinuousCurrentLimit(ARM_CURRENT_HOLD, ARM_PEAK_TIMEOUT);

	// Current limiting for motor 2
	this->pArmMotor2->ConfigPeakCurrentLimit(ARM_CURRENT_THRESHOLD, ARM_PEAK_TIMEOUT);
	this->pArmMotor2->ConfigPeakCurrentDuration(ARM_CURRENT_TIMEOUT, ARM_PEAK_TIMEOUT);
	this->pArmMotor2->ConfigContinuousCurrentLimit(ARM_CURRENT_HOLD, ARM_PEAK_TIMEOUT);

	// Enable current limiting on each motor
	this->pArmMotor->EnableCurrentLimit(true);
	this->pArmMotor2->EnableCurrentLimit(true);
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