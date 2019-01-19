#include "Autonomous/Commands/CMDJustDriveForward.h"
#include "Robot.h"
#include "Utilities/Log.h"

/**
 *
 */
CMDJustDriveForward::CMDJustDriveForward()
{
	LOG("[CMDJustDriveForward] Constructed");

	if (Robot::m_DriveTrain != nullptr)
	{
		Requires(Robot::m_DriveTrain);
		this->pMotionProfiler = new PFLJustDriveForward(*Robot::m_DriveTrain->GetLeftFrontMotor(), *Robot::m_DriveTrain->GetRightFrontMotor());
	}
	else
	{
		LOG("[CMDJustDriveForward] driveTrain is NULL");
	}

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
CMDJustDriveForward::~CMDJustDriveForward()
{
	delete this->pTimer;
	delete this->pMotionProfiler;

	return;
}

/**
 *
 */
void CMDJustDriveForward::Initialize()
{
	LOG("[CMDJustDriveForward] Initializing" );

	this->pTimer->Reset();
	this->pTimer->Start();

	Robot::m_DriveTrain->InitMotionProfilingMode();

	return;
}

/**
 *
 */
void CMDJustDriveForward::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

//	LOG("[CMDJustDriveForward] Set Output: " << setOutput);

	Robot::m_DriveTrain->GetLeftFrontMotor()->Set(ControlMode::MotionProfile, setOutput);
	Robot::m_DriveTrain->GetRightFrontMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	return;
}

/**
 *
 */
bool CMDJustDriveForward::IsFinished()
{
	if (this->pMotionProfiler->isFinished())
	{
		LOG("[CMDJustDriveForward] MP Finished");

		return true;
	}

	return false;
}

/**
 *
 */
void CMDJustDriveForward::End()
{
	LOG("[CMDJustDriveForward] Ending" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void CMDJustDriveForward::Interrupted()
{
	LOG("[CMDJustDriveForward] Interrupted" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}
