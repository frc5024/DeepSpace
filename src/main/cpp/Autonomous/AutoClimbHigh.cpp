/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Autonomous/AutoClimbHigh.h"
#include "Robot.h"

AutoClimbHigh::AutoClimbHigh()
{
	Requires(Robot::m_Arm) ;
	Requires(Robot::m_Leg) ;
	Requires(Robot::m_CrawlDrive) ;
	Requires(Robot::m_DriveTrain) ;

	this->pTimer = new frc::Timer() ;

	this->stage = S_LOWER_ARM ;

	this->onFloor = true ;
}

void AutoClimbHigh::Initialize()
{
	this->stage = S_LOWER_ARM ;
	this->onFloor = true ;
	this->pTimer->Reset() ;
	this->pTimer->Start() ;
}

void AutoClimbHigh::Execute()
{
	switch (this->stage)
	{
		case S_LOWER_ARM : this->Execute_LowerArm() ; break ;
		case S_LOWER_LEG : this->Execute_LowerLeg() ; break ;
		case S_CRAWL	 : this->Execute_Crawl()	; break ;
		case S_DRIVE	 : this->Execute_Drive()	; break ;
		case S_RAISE_LEG : this->Execute_Raiseleg() ; break ;
		default : this->stage = S_FINISHED ; break ;
	}
}

void AutoClimbHigh::Execute_LowerArm(void)
{
	/* Power is 0% to 100% throughout 3 seconds,	 *
	 * Then caps out at 100% until sensor is tripped */
	float speed = std::min(this->pTimer->Get(), 3.0) / 3.0 ;

	Robot::m_Arm->MoveArm(speed) ; // Bring arm down

	if (Robot::m_Arm->GetSensor()  // We are fully lowered if the sensor trips
	||  this->pTimer->Get() > 5.0) // Time out if it's been 6 seconds
	{
		this->stage = S_LOWER_LEG ;
		this->pTimer->Reset() ;
	}
}

void AutoClimbHigh::Execute_LowerLeg(void)
{
	Robot::m_Arm->MoveArm(0.8) ; // Keep arm down
	Robot::m_Leg->MoveLeg(-1.0) ; // Bring leg down

	if (Robot::m_Leg->AtBottom() // We are fully lowered if sensor trips
	||  this->pTimer->Get() > 6.0) // Time out if it's been 6 seconds
	{
		this->stage = S_CRAWL ;
		this->pTimer->Reset() ;
	}
}

void AutoClimbHigh::Execute_Crawl(void)
{
	Robot::m_Arm->MoveArm(0.8) ; // Keep arm down
	Robot::m_Leg->MoveLeg(-1.0) ; // Keep leg down
	Robot::m_CrawlDrive->Move(1.0) ; // Crawl forward

	// Get if we are now on the floor
	bool nowOnFloor = Robot::m_CrawlDrive->GetSensor() ;
	if (this->onFloor)
	{
		this->onFloor = nowOnFloor ; // Update state
	}
	else
	{
		// If we were in the air and are now on the floor
		if (nowOnFloor)
		{
			this->stage = S_DRIVE ;
			this->pTimer->Reset() ;
		}
	}

	// Timeout if it's been 6 seconds
	if (this->pTimer->Get() > 6.0)
	{
		this->stage = S_DRIVE ;
		this->pTimer->Reset() ;
	}
}

void AutoClimbHigh::Execute_Drive(void)
{
	Robot::m_Arm->MoveArm(-0.5) ; // Bring arm up slowly
	Robot::m_Leg->MoveLeg(1.0) ; // Keep leg down
	Robot::m_CrawlDrive->Move(0.0) ; // Brake the crawlDrive
	Robot::m_DriveTrain->TankDrive(0.6, 0.6) ; // Drive at 60% speed

	// We do this for only 1 seconds, no sensors for this part
	if (this->pTimer->Get() > 1.0)
	{
		this->stage = S_RAISE_LEG ;
		this->pTimer->Reset() ;
	}
}

void AutoClimbHigh::Execute_Raiseleg(void)
{
	Robot::m_Arm->MoveArm(0.0) ; // Brake
	Robot::m_DriveTrain->TankDrive(0.0,0.0) ; // Brake
	Robot::m_Leg->MoveLeg(-1.0) ; // Bring legs back up


	if (Robot::m_Leg->AtTop() // If leg is raised all the way
	||	this->pTimer->Get() > 6.0) // Timeout if it's been 6 seconds
	{
		this->stage = S_FINISHED ;
	}	
}

bool AutoClimbHigh::IsFinished()
{
	return (this->stage == S_FINISHED) ;
}

void AutoClimbHigh::End()
{
	Robot::m_Arm->MoveArm(0.0) ;
	Robot::m_Leg->MoveLeg(0.0) ;
	Robot::m_DriveTrain->TankDrive(0.0, 0.0);
	Robot::m_CrawlDrive->Move(0.0) ;
	this->pTimer->Stop() ;
}

void AutoClimbHigh::Interrupted()
{
	Robot::m_Arm->MoveArm(0.0) ;
	Robot::m_Leg->MoveLeg(0.0) ;
	Robot::m_DriveTrain->TankDrive(0.0, 0.0);
	Robot::m_CrawlDrive->Move(0.0) ;
	this->pTimer->Stop() ;
}
