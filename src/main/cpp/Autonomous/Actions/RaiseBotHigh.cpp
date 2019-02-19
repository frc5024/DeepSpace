/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Autonomous/Actions/RaiseBotHigh.h"
#include "Robot.h"

RaiseBotHigh::RaiseBotHigh(void)
{
	Requires(Robot::m_Arm) ;
	Requires(Robot::m_Leg) ;
	Requires(Robot::m_CrawlDrive) ;

	this->pTimer = new frc::Timer();

	this->onFloor = true ;
}

void RaiseBotHigh::Initialize()
{
	this->onFloor = true ; // Assume robot starts grounded, I'd hope
	this->pTimer->Start();
}

void RaiseBotHigh::Execute()
{
	// MoveArm and MoveLeg auto-stop when they reach a sensor

	Robot::m_Arm->MoveArm(0.75) ;
	Robot::m_Leg->MoveLeg(-1.0) ;
	Robot::m_CrawlDrive->Move(1.0) ;
}

bool RaiseBotHigh::IsFinished()
{
	// Check if we WERE in the air and are NOW on the floor
	bool nowOnFloor = Robot::m_CrawlDrive->GetSensor() ;
	if (this->onFloor == false) {
		if (nowOnFloor == true) {
			return true ;
		}
	} else {
		this->onFloor = nowOnFloor ;
	}

	// Timeout if it's been too long
	if (this->pTimer->Get() > 6.0)
		return true ;
	return false ;
}

void RaiseBotHigh::End()
{
	Robot::m_Arm->MoveArm(0.0) ;
	Robot::m_Leg->MoveLeg(0.0) ;
	Robot::m_CrawlDrive->Move(0.0) ;
	this->pTimer->Stop();
	this->pTimer->Reset();
}

void RaiseBotHigh::Interrupted()
{
	Robot::m_Arm->MoveArm(0.0) ;
	Robot::m_Leg->MoveLeg(0.0) ;
	Robot::m_CrawlDrive->Move(0.0) ;
	this->pTimer->Stop();
	this->pTimer->Reset();
}
