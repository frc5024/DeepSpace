#include "Autonomous/Commands/CMDCenterLeftToLeftStation.h"
#include "Robot.h"
#include "Utilities/Log.h"

/**
 *
 */
CMDCenterLeftToLeftStation::CMDCenterLeftToLeftStation()
{
	LOG("[CMDCenterLeftToLeftStation] Constructed");

	if (Robot::m_DriveTrain != nullptr)
	{
		Requires(Robot::m_DriveTrain);
		this->pMotionProfiler = new PFLCenterLeftToLeftStation(*Robot::m_DriveTrain->GetLeftFrontMotor(), *Robot::m_DriveTrain->GetRightFrontMotor());
	}
	else
	{
		LOG("[CMDCenterLeftToLeftStation] driveTrain is NULL");
	}

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
CMDCenterLeftToLeftStation::~CMDCenterLeftToLeftStation()
{
	delete this->pTimer;
	delete this->pMotionProfiler;

	return;
}

/**
 *
 */
void CMDCenterLeftToLeftStation::Initialize()
{
	LOG("[CMDCenterLeftToLeftStation] Initializing" );

	this->pTimer->Reset();
	this->pTimer->Start();

	Robot::m_DriveTrain->InitMotionProfilingMode();

	return;
}

/**
 *
 */
void CMDCenterLeftToLeftStation::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

//	LOG("[CMDCenterLeftToLeftStation] Set Output: " << setOutput);

	Robot::m_DriveTrain->GetLeftFrontMotor()->Set(ControlMode::MotionProfile, setOutput);
	Robot::m_DriveTrain->GetRightFrontMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	return;
}

/**
 *
 */
bool CMDCenterLeftToLeftStation::IsFinished()
{
	if (this->pMotionProfiler->isFinished())
	{
		LOG("[CMDCenterLeftToLeftStation] MP Finished");

		return true;
	}

	return false;
}

/**
 *
 */
void CMDCenterLeftToLeftStation::End()
{
	LOG("[CMDCenterLeftToLeftStation] Ending" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void CMDCenterLeftToLeftStation::Interrupted()
{
	LOG("[CMDCenterLeftToLeftStation] Interrupted" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}
