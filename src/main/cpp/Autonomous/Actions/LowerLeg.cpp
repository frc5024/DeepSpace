/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Autonomous/Actions/LowerLeg.h"
#include "Robot.h"

LowerLeg::LowerLeg()
{
	Requires(Robot::m_Arm);
	Requires(Robot::m_Leg);
}

void LowerLeg::Initialize() {}

void LowerLeg::Execute()
{	
	// Make sure arm is holding position
	if (Robot::m_Arm->GetSensor()) {
		Robot::m_Arm->MoveArm(ARM_HOLD_SPEED);
	} else {
		Robot::m_Arm->MoveArm(0.8);
	}

	// Move legs, checked if done in IsFinished()
	Robot::m_Leg->MoveLeg(-1.0);
}

bool LowerLeg::IsFinished()
{
	return Robot::m_Leg->AtBottom();
}

// Called once after isFinished returns true
void LowerLeg::End() {
	Robot::m_Arm->MoveArm(0.0);
	Robot::m_Leg->MoveLeg(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LowerLeg::Interrupted() {
	Robot::m_Arm->MoveArm(0.0);
	Robot::m_Leg->MoveLeg(0.0);
}
