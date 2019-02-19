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

	// Construct all to 0, is initialized later
	this->armSpd = 0.0 ;
	this->legSpd = 0.0 ;
	this->crawlSpd = 0.0 ;
	this->onFloor = false ;
}

void RaiseBotHigh::Initialize()
{
	this->armSpd = 0.63 ; // mAgIc nUmBeR
	this->legSpd = -1.0 ; // full speed = slowly down
	this->crawlSpd = 1.0 ; // full speed = crawl forward
	this->onFloor = true ; // Assume robot starts grounded, I'd hope
}

void RaiseBotHigh::Execute()
{
	// Check if Arm is done
	if (Robot::m_Arm->GetSensor()) {
		this->armSpd = ARM_HOLD_SPEED ;
	} else {
		this->armSpd = 0.63 ;
	}

	// Check if leg is done
	if (Robot::m_Leg->AtBottom()) {
		this->legSpd = 0.0 ; // Not hold_speed becuase there's no failsafe if it goes past the sensor
	} else {
		this->legSpd = -1.0 ;
	}

	// DRIVE! BRRRRRRRR BRR BRR BRRRRR
	Robot::m_Arm->MoveArm(this->armSpd) ;
	Robot::m_Leg->MoveLeg(this->legSpd) ;
	Robot::m_CrawlDrive->Move(this->crawlSpd) ;

}

void RaiseBotHigh::IsFinished()
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
	return false ;
}

void RaiseBotHigh::End()
{
	Robot::m_Arm->MoveArm(0.0) ;
	Robot::m_Leg->MoveLeg(0.0) ;
	Robot::m_CrawlDrive->Move(0.0) ;
}

void RaiseBotHigh::Interrupted()
{
	Robot::m_Arm->MoveArm(0.0) ;
	Robot::m_Leg->MoveLeg(0.0) ;
	Robot::m_CrawlDrive->Move(0.0) ;
}
