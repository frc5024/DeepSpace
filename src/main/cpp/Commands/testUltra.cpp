/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/testUltra.h"
#include "Robot.h"
#include <iostream>

testUltra::testUltra() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::m_Arm);
  Requires(Robot::m_DriveTrain);
}

// Called just before this Command runs the first time
void testUltra::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void testUltra::Execute() {

  double distance = Robot::m_Arm->getDistanceFromFloor();

  std::cout << distance << std::endl;
//  Robot::m_DriveTrain->ArcadeDrive(distance, 0);
}

// Make this return true when this Command no longer needs to run execute()
bool testUltra::IsFinished() { return false; }

// Called once after isFinished returns true
void testUltra::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void testUltra::Interrupted() {}
