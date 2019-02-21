/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Autonomous/Actions/LowerArm.h"
#include "Robot.h"

LowerArm::LowerArm(float speed, float timeout)
{
	Requires(Robot::m_Arm);
	this->pTimer = new frc::Timer();
	this->speed = speed;
	this->timeout = timeout;
}

void LowerArm::Initialize()
{
	this->pTimer->Start();
}

void LowerArm::Execute()
{
	// Increase speed by 25% from 0 to 2 seconds
	float speedIncrease = std::min(this->pTimer->Get(), 2.0) / 8.0 ;

	// Apply our speed increase to our base speed of 75%
	float speedTotal = speedIncrease + this->speed ;

	// VROOM
	Robot::m_Arm->MoveArm(speedTotal) ;
}

bool LowerArm::IsFinished()
{
	return	(this->pTimer->Get() > timeout) ;
//	Robot::m_Arm->GetSensor()
//		||
	
}

void LowerArm::End()
{
	Robot::m_Arm->MoveArm(0.0) ;
}

void LowerArm::Interrupted()
{
	Robot::m_Arm->MoveArm(0.0) ;
}
