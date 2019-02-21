/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/BumperSuperCommand.h"
#include "Robot.h"

BumperSuperCommand::BumperSuperCommand() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::m_Piston);
  this->pJoyOp = Robot::m_oi->GetJoystickOperator();
}

// Called just before this Command runs the first time
void BumperSuperCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void BumperSuperCommand::Execute() {
  if (this->pJoyOp->GetBumper(Hand::kLeftHand));{
    Robot::m_Piston->Deploy();
    Robot::m_Flap->Deploy();
  }
}

// Make this return true when this Command no longer needs to run execute()
bool BumperSuperCommand::IsFinished() { return false; }

// Called once after isFinished returns true
void BumperSuperCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void BumperSuperCommand::Interrupted() {}
