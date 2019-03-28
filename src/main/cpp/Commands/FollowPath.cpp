/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include "Commands/FollowPath.h"

FollowPath::FollowPath(double timeout, TankProfile *path) : TimedCommand(timeout) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  this->path = path;
  Requires(Robot::m_DriveTrain);
}

// Called just before this Command runs the first time
void FollowPath::Initialize() {
  // this->pFollowerNotifier = new frc::Notifier(*this->Follow);
  // this->pFollowerNotifier->StartPeriodic(this->path->leftTrajectory->dt);
}

// Called repeatedly when this Command is scheduled to run
void FollowPath::Execute() {
  Log("Following path");
  if (this->path->leftFollower.finished == 1 || this->path->rightFollower.finished == 1 || this->path->length < this->path->leftFollower.segment)
  {
    // this->pFollowerNotifier->Stop();
    Log("Trying to run completed path!!");
    Robot::m_DriveTrain->RawDrive(0, 0);
    this->finished = true;
  }
  else
  {
    Robot::m_DriveTrain->Follow(this->path);
  }
}

// Called once after command times out
void FollowPath::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FollowPath::Interrupted() {}

bool FollowPath::IsFinished(){
  return this->finished || this->IsTimedOut();
}

void FollowPath::Follow(){
  
}