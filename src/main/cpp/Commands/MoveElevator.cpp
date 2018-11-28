/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/MoveElevator.h>

#include "Robot.h"

MoveElevator::MoveElevator() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::m_Elevator);
  this->pJoyDrive = Robot::m_oi->GetJoystickDrive();
  
  
}

// Called just before this Command runs the first time
void MoveElevator::Initialize() {

  this->speed = 0;
  this->pos = 0;
  this->neg = 0;
  
}

// Called repeatedly when this Command is scheduled to run
void MoveElevator::Execute() {
  this->pos = pJoyDrive->GetTriggerAxis(XboxController::kLeftHand);
  this->neg = pJoyDrive->GetTriggerAxis(XboxController::kRightHand);

  this->speed = pos + neg;

  Robot::m_Elevator->setSpeed(speed);
}

// Make this return true when this Command no longer needs to run execute()
bool MoveElevator::IsFinished() { return false; }

// Called once after isFinished returns true
void MoveElevator::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveElevator::Interrupted() {
  
}
