/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Subsystems/Intake.hpp>

Intake::Intake() : Subsystem("Intake") {
	this->pLeftMotor = new can::WPI_TalonSRX(INTAKE_LEFT_MOTOR_ID) ;
	this->pRightMotor = new can::WPI_TalonSRX(INTAKE_RIGHT_MOTOR_ID) ;
  
	this->pLeftMotor->Follow(*pRightMotor) ;
	this->pLeftMotor->SetInverted(true) ; // TODO: Check inversion is right!
	this->pRightMotor->SetInverted(false) ; // TODO: make sure when given positive double, it intakes
	this->pLeftMotor->SetNeutralMode(NeutralMode::Brake);
	this->pRightMotor->SetNeutralMode(NeutralMode::Brake);
	this->pLeftMotor->SetSafetyEnabled(false);
	this->pRightMotor->SetSafetyEnabled(false);

	this->pGripperSolenoid = new frc::DoubleSolenoid(
		GRIPPER_SOLENOID_CAN_ID,
		GRIPPER_SOLENOID_FORWARDCHANNEL_ID,
		GRIPPER_SOLENOID_REVERSECHANNEL_ID
	);

  return ;
}

void Intake::InitDefaultCommand() {

}

void Intake::IntakeUse(double spd) { 
	this->pRightMotor->Set(spd) ;
}

void Intake::OpenGripper(void) {
	this->pGripperSolenoid->Set(frc::DoubleSolenoid::Value::kReverse) ;
	this->gripperClosed = false ;
}

void Intake::CloseGripper(void) {
	this->pGripperSolenoid->Set(frc::DoubleSolenoid::Value::kForward);
	this->gripperClosed = true ;
}

bool Intake::IsGripperClosed(void) {
	return this->gripperClosed ;
}
