/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Autonomous/AutoClimbHigh.h"
#include "Robot.h"

AutoClimbHigh::AutoClimbHigh() {
	Requires(Robot::m_Arm);
	Requires(Robot::m_Leg);
	Requires(Robot::m_CrawlDrive);
	Requires(Robot::m_DriveTrain);
	this->pTimer = new frc::Timer();
	this->stage = S_LOWER_ARM;
	this->onFloor = true;
}

void AutoClimbHigh::Initialize() {
	this->stage = S_LOWER_ARM;
	this->onFloor = true;
	this->pTimer->Reset();
	this->pTimer->Start();
}

void AutoClimbHigh::Execute() {
	// Execute the appropriate function for the current stage of climb
	switch (this->stage) {
		case S_LOWER_ARM : this->Execute_LowerArm() ; break;
		case S_LOWER_LEG : this->Execute_LowerLeg() ; break;
		case S_CRAWL	 : this->Execute_Crawl()	; break;
		case S_DRIVE	 : this->Execute_Drive()	; break;
		case S_RAISE_LEG : this->Execute_Raiseleg() ; break;
		default : this->stage = S_FINISHED ; break;
	}
}

void AutoClimbHigh::Execute_LowerArm(void) {
	/* Power is 35% to 100% throughout 2 seconds,	 	*
	 * Then caps out at 100% until sensor is tripped */
	float speed = 0.35 + std::min(this->pTimer->Get(), 2.0) * 0.325 ;

	Robot::m_Arm->MoveArm(speed); // Bring arm down

	// If arm is lowered or it's been 5 seconds, go to next stage
	if (Robot::m_Arm->GetSensor()
	||  this->pTimer->Get() > 5.0) {
		this->stage = S_LOWER_LEG;
		this->pTimer->Reset();
	}
}

void AutoClimbHigh::Execute_LowerLeg(void) {
	Robot::m_Arm->MoveArm(0.75); // Keep arm down
	Robot::m_Leg->MoveLeg(-1.0); // Bring leg down

	// If leg is at bottom or it's been 6 seconds, go to the next stage
	if (Robot::m_Leg->AtBottom()
	||  this->pTimer->Get() > 10.0) {
		this->stage = S_CRAWL;
		this->pTimer->Reset();
	}
}

void AutoClimbHigh::Execute_Crawl(void) {
	Robot::m_Arm->MoveArm(1.0); // Keep arm down
	Robot::m_Leg->MoveLeg(-1.0); // Keep leg down
	Robot::m_CrawlDrive->Move(1.0); // Crawl forward
	Robot::m_DriveTrain->TankDrive(0.6, -0.6); // Drive forward

	// Get if we are now on the floor
	bool nowOnFloor = Robot::m_CrawlDrive->GetSensor();

	// If we were in the air and are now on the floor, go to the next stage
	if (!this->onFloor && nowOnFloor) {
		this->stage = S_DRIVE;
		this->pTimer->Reset();
	} else {
		// Otherwise update our 'were' with our 'now'
		this->onFloor = nowOnFloor ;
	}

	// Or, if it's been 6 seconds, go to the next stage
	if (this->pTimer->Get() > 6.0) {
		this->stage = S_DRIVE;
		this->pTimer->Reset();
	}
}

void AutoClimbHigh::Execute_Drive(void) {
	Robot::m_Arm->MoveArm(-0.7); // Bring arm up slowly
	Robot::m_Leg->MoveLeg(-1.0); // Keep leg down
	Robot::m_CrawlDrive->Move(0.0); // Brake the crawlDrive

    // Drives from 60% to 30% throughout 2 seconds then flatlines at 30%
    double power = 0.6 - std::min(this->pTimer->Get(), 2.0) * 0.15 ;

	Robot::m_DriveTrain->TankDrive(power, -power); // Drive at 40% speed
	// We do this for only 1 seconds, no sensors for this part
	if (this->pTimer->Get() > 2.0) {
		this->stage = S_RAISE_LEG;
		this->pTimer->Reset();
	}
}

void AutoClimbHigh::Execute_Raiseleg(void) {
	Robot::m_Arm->MoveArm(0.0); // Brake
	Robot::m_DriveTrain->TankDrive(0.0,0.0); // Brake
	Robot::m_Leg->MoveLeg(1.0); // Bring legs back up

	// If leg is at top or it's been 6 seconds, we are finished
	if (Robot::m_Leg->AtTop()
	||	this->pTimer->Get() > 3.0) {
		this->stage = S_FINISHED ;
	}	
}

bool AutoClimbHigh::IsFinished() {
	return this->stage == S_FINISHED;
}

void AutoClimbHigh::End() {
	// Brake all subsystems and stop timer
	Robot::m_Arm->MoveArm(0.0);
	Robot::m_Leg->MoveLeg(0.0);
	Robot::m_DriveTrain->TankDrive(0.0, 0.0);
	Robot::m_CrawlDrive->Move(0.0);
	this->pTimer->Stop();
}

void AutoClimbHigh::Interrupted() {
	// Brake all subsystems and stop timer
	Robot::m_Arm->MoveArm(0.0);
	Robot::m_Leg->MoveLeg(0.0);
	Robot::m_DriveTrain->TankDrive(0.0, 0.0);
	Robot::m_CrawlDrive->Move(0.0);
	this->pTimer->Stop();
}
