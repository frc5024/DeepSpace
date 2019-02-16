/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/Actions/MoveLegsTo.h"
#include "Robot.h"

MoveLegsTo::MoveLegsTo(Pos position, double spd, double timeout) : TimedCommand(timeout) {
	Requires(Robot::m_Leg);
	this->pos = position ;
	this->spd = spd ;
}

// Called just before this Command runs the first time
void MoveLegsTo::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void MoveLegsTo::Execute() {
	Robot::m_Leg->MoveLeg(this->spd) ;
}

// Make this return true when this Command no longer needs to run execute()
bool MoveLegsTo::IsFinished()
{
	switch (this->pos)
	{
		case P_TOP :	return Robot::m_Leg->AtTop() ;
		case P_MID :	return Robot::m_Leg->AtMiddle() ;
		case P_BOT :	return Robot::m_Leg->AtBottom() ;
		default : 		return true ; // error
	}
}

// Called once after isFinished returns true
void MoveLegsTo::End() {
	Robot::m_Leg->MoveLeg(0.0) ;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveLegsTo::Interrupted() {
	Robot::m_Leg->MoveLeg(0.0) ;
}
