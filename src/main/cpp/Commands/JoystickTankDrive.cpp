/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/JoystickTankDrive.h"
#include "Robot.h"

JoystickTankDrive::JoystickTankDrive()
{
	Requires(Robot::m_DriveTrain);
	this->pJoyDrive = new frc::XboxController(XBOX_CONTROLLER_DRIVE_PORT);
	this->isReverse = false ;
}

void JoystickTankDrive::Initialize(){}

void JoystickTankDrive::Execute()
{
	float leftSpeed  = this->pJoyDrive->GetY(frc::XboxController::kLeftHand ) ;
	float rightSpeed = this->pJoyDrive->GetY(frc::XboxController::kRightHand) ;

	// If right bumper is held, slow down
	if (this->pJoyDrive->GetBumper(frc::XboxController::kRightHand))
	{
		leftSpeed  *= 0.6 ;
		rightSpeed *= 0.6 ;
	}

	// If (X) is pressed, toggle reverse driving
	if (this->pJoyDrive->GetXButtonPressed())
	{
		this->isReverse = ! this->isReverse ;
	}

	// If we're in reverse, reverse the speed
	if (this->isReverse)
	{
		leftSpeed  = - leftSpeed  ;
		rightSpeed = - rightSpeed ;
	}

	Robot::m_DriveTrain->TankDrive(leftSpeed, rightSpeed) ;

}	

// Make this return true when this Command no longer needs to run execute()
bool JoystickTankDrive::IsFinished() { return false; }

// Called once after isFinished returns true
void JoystickTankDrive::End()
{
	Robot::m_DriveTrain->TankDrive(0.0, 0.0) ;
	Robot::m_DriveTrain->TankDrive(0.0, 0.0) ;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void JoystickTankDrive::Interrupted()
{
	Robot::m_DriveTrain->TankDrive(0.0, 0.0) ;
	Robot::m_DriveTrain->TankDrive(0.0, 0.0) ;
}
