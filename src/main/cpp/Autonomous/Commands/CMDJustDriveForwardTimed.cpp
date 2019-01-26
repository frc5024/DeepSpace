#include "Autonomous/Commands/CMDJustDriveForwardTimed.h"
#include "Robot.h"
#include "Utilities/Log.h"

/**
 *
 */
CMDJustDriveForwardTimed::CMDJustDriveForwardTimed(double speed, double rotation, double duration)
{
	LOG("[CMDJustDriveForwardTimed] Constructed");

	if (Robot::m_DriveTrain != nullptr)
	{
		Requires(Robot::m_DriveTrain);
	}
	else
	{
		LOG("[CMDJustDriveForwardTimed] driveTrain is NULL");
	}

	this->pTimer = new frc::Timer();
    this->dSpeed = speed;
    this->dRotation = rotation;
    this->dDuration = duration;

	return;
}

/**
 *
 */
CMDJustDriveForwardTimed::~CMDJustDriveForwardTimed()
{
	delete this->pTimer;

	return;
}

/**
 *
 */
void CMDJustDriveForwardTimed::Initialize()
{
	LOG("[CMDJustDriveForwardTimed] Initializing" );

    Robot::m_DriveTrain->ResetDrive();

	this->pTimer->Reset();
	this->pTimer->Start();

	return;
}

/**
 *
 */
void CMDJustDriveForwardTimed::Execute()
{
    if (this->pTimer->Get() < this->dDuration)
    {
        Robot::m_DriveTrain->ArcadeDrive(dSpeed, dRotation);
    }
    else
    {
        Robot::m_DriveTrain->ArcadeDrive(0, 0);
    }

	return;
}

/**
 *
 */
bool CMDJustDriveForwardTimed::IsFinished()
{
	return this->pTimer->Get() > this->dDuration;
}

/**
 *
 */
void CMDJustDriveForwardTimed::End()
{
	Robot::m_DriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void CMDJustDriveForwardTimed::Interrupted()
{
	Robot::m_DriveTrain->ResetDrive();

	return;
}
