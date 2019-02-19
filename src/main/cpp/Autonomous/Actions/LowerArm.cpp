/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Autonomous/Actions/LowerArm.h"
#include "Robot.h"

LowerArm::LowerArm() : frc::TimedCommand(TIMEOUT_TIME)
{
	Requires(Robot::m_Arm);
}

void LowerArm::Initialize() {}

void LowerArm::Execute()
{
	Robot::m_Arm->MoveArm(PREDEFINED_ARM_SPEED) ;
}

void LowerArm::End()
{
	Robot::m_Arm->MoveArm(0.0) ;
}

void LowerArm::Interrupted()
{
	Robot::m_Arm->MoveArm(0.0) ;
}
