/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Autonomous/Actions/Crawl.h"
#include "Robot.h"

Crawl::Crawl() {
	Requires(Robot::m_CrawlDrive);
	Requires(Robot::m_Arm);
	this->wasOnFloor = true ;
}

void Crawl::Initialize() {
	this->wasOnFloor = true ;
}

void Crawl::Execute() {

	Robot::m_Arm->MoveArm(0.75);
	// Leg should hold position well
	Robot::m_CrawlDrive->Move(1.0);
}

bool Crawl::IsFinished() {

	bool nowOnFloor = Robot::m_CrawlDrive->GetSensor();

	if (this->wasOnFloor) {
		this->wasOnFloor = nowOnFloor ;
	} else {
		if (nowOnFloor) {
			return true ;
		}
	}
	return false;
}

void Crawl::End() {
	Robot::m_CrawlDrive->Move(0.0);
}

void Crawl::Interrupted() {
	Robot::m_CrawlDrive->Move(0.0);
}
