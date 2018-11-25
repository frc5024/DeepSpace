/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/DriveWithJoystick.h"

DriveWithJoystick::DriveWithJoystick() {
  if (CommandBase::pDriveTrain != nullptr) {
    Requires(CommandInterface::pDriveTrain);
  }
}

// Called just before this Command runs the first time
void DriveWithJoystick::Initialize() {
  // Set speed and direction multipliers
  this->directionMultiplier = 1;
  this->speedMultiplier     = 1;

  //set Speed and Rotation
  this->speed    = 0.0;
  this->rotation = 0.0;
}

// Called repeatedly when this Command is scheduled to run
void DriveWithJoystick::Execute() {
  // Deal with reversing and slow mode
	this->directionMultiplier *= (this->pJoyDrive->GetXButtonReleased())? -1 : 1;
  this->speedMultiplier = (this->pJoyDrive->GetBumper(XboxController::kRightHand)) ? 0.5 : 1;

  // Get movement data form controller
  this->speed    = pJoyDrive->GetY(XboxController::kLeftHand) * -1;
	this->rotation = pJoyDrive->GetX(XboxController::kLeftHand);

  this->speed    = (this->speed * this->speedMultiplier * this->directionMultiplier);
  this->rotation = (this->rotation * this->directionMultiplier);

  CommandInterface::pDriveTrain->ArcadeDrive(this->speed, this->rotation);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveWithJoystick::IsFinished() { return false; }

// Called once after isFinished returns true
void DriveWithJoystick::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveWithJoystick::Interrupted() {}
