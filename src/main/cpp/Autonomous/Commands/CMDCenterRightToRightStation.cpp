#include "Autonomous/Commands/CMDCenterRightToRightStation.h"
#include "Robot.h"
#include "Utilities/Log.h"

/**
 *
 */
CMDCenterRightToRightStation::CMDCenterRightToRightStation()
{
	LOG("[CMDCenterRightToRightStation] Constructed");

	if (Robot::m_DriveTrain != nullptr)
	{
		Requires(Robot::m_DriveTrain);
		this->pMotionProfiler = new PFLCenterRightToRightStation(*Robot::m_DriveTrain->GetLeftFrontMotor(), *Robot::m_DriveTrain->GetRightFrontMotor());
	}
	else
	{
		LOG("[CMDCenterRightToRightStation] driveTrain is NULL");
	}

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
CMDCenterRightToRightStation::~CMDCenterRightToRightStation()
{
	delete this->pTimer;
	delete this->pMotionProfiler;

	return;
}

/**
 *
 */
void CMDCenterRightToRightStation::Initialize()
{
	LOG("[CMDCenterRightToRightStation] Initializing" );

	this->pTimer->Reset();
	this->pTimer->Start();

	Robot::m_DriveTrain->InitMotionProfilingMode();

	return;
}

/**
 *
 */
void CMDCenterRightToRightStation::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

//	LOG("[CMDCenterRightToRightStation] Set Output: " << setOutput);

	Robot::m_DriveTrain->GetLeftFrontMotor()->Set(ControlMode::MotionProfile, setOutput);
	Robot::m_DriveTrain->GetRightFrontMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	return;
}

/**
 *
 */
bool CMDCenterRightToRightStation::IsFinished()
{
	if (this->pMotionProfiler->isFinished())
	{
		LOG("[CMDCenterRightToRightStation] MP Finished");

		return true;
	}

	return false;
}

/**
 *
 */
void CMDCenterRightToRightStation::End()
{
	LOG("[CMDCenterRightToRightStation] Ending" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void CMDCenterRightToRightStation::Interrupted()
{
	LOG("[CMDCenterRightToRightStation] Interrupted" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}
