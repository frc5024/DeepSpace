/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Autonomous/Actions/FinishClimb.h"
#include "Robot.h"

FinishClimb::FinishClimb()
{
	Requires(Robot::m_DriveTrain);
	Requires(Robot::m_Arm);
	Requires(Robot::m_Leg);

	this->pTimer = new frc::Timer() ;
}

void FinishClimb::Initialize()
{
	this->pTimer->Start();
	Robot::m_Leg->SetPos(Leg::Quadrant::Q_BOTTOM) ;
}

void FinishClimb::Execute()
{
	float time = this->pTimer->Get() ;
	
	if (time > 2.0)
	{
		/*	----==== STAGE 3 ====----	*
		 * Stop driving and raise legs	*/
		Robot::m_Arm->MoveArm(0.0);
		Robot::m_DriveTrain->ArcadeDrive(0.0, 0.0);
		Robot::m_Leg->MoveLeg(1.0); // Legs won't go past top
	} else
	if (time > 1.0)
	{
		/*		----==== STAGE 2 ====----		*
		 * Stop arms and keep moving forward	*/
		Robot::m_Arm->MoveArm(0.0);
		Robot::m_DriveTrain->ArcadeDrive(0.5, 0.0);
		Robot::m_Leg->MoveLeg(0.0);
	} else
	{
		/*	----==== STAGE 1 ====----		*
		 * Bring arms up and move forward	*/
		Robot::m_Arm->MoveArm(-0.5);
		Robot::m_DriveTrain->ArcadeDrive(0.5, 0.0);
		Robot::m_Leg->MoveLeg(0.0);
	}
}

bool FinishClimb::IsFinished()
{
	if (this->pTimer->Get() > 8.0)
		return true ;
	return false;
}

void FinishClimb::End()
{
	Robot::m_Arm->MoveArm(0.0);
	Robot::m_DriveTrain->ArcadeDrive(0.0, 0.0);
	Robot::m_Leg->MoveLeg(0.0);
	this->pTimer->Reset();
	this->pTimer->Stop();
}

void FinishClimb::Interrupted()
{
	Robot::m_Arm->MoveArm(0.0);
	Robot::m_DriveTrain->ArcadeDrive(0.0, 0.0);
	Robot::m_Leg->MoveLeg(0.0);
	this->pTimer->Reset();
	this->pTimer->Stop();
}
