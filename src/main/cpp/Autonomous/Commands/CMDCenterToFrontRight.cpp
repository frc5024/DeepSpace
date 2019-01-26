#include "Autonomous/Commands/CMDCenterToFrontRight.h"
#include "Robot.h"
#include "Utilities/Log.h"

/**
 *
 */
CMDCenterToFrontRight::CMDCenterToFrontRight()
{
	LOG("[CMDCenterToFrontRight] Constructed");

	if (Robot::m_DriveTrain != nullptr)
	{
		Requires(Robot::m_DriveTrain);
		this->pMotionProfiler = new PFLCenterToFrontRight(*Robot::m_DriveTrain->GetLeftFrontMotor(), *Robot::m_DriveTrain->GetRightFrontMotor());
	}
	else
	{
		LOG("[CMDCenterToFrontRight] driveTrain is NULL");
	}

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
CMDCenterToFrontRight::~CMDCenterToFrontRight()
{
	delete this->pTimer;
	delete this->pMotionProfiler;

	return;
}

/**
 *
 */
void CMDCenterToFrontRight::Initialize()
{
	LOG("[CMDCenterToFrontRight] Initializing" );

	this->pTimer->Reset();
	this->pTimer->Start();

	Robot::m_DriveTrain->InitMotionProfilingMode();

	return;
}

/**
 *
 */
void CMDCenterToFrontRight::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

//	LOG("[CMDCenterToFrontRight] Set Output: " << setOutput);

	Robot::m_DriveTrain->GetLeftFrontMotor()->Set(ControlMode::MotionProfile, setOutput);
	Robot::m_DriveTrain->GetRightFrontMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	return;
}

/**
 *
 */
bool CMDCenterToFrontRight::IsFinished()
{
	if (this->pMotionProfiler->isFinished())
	{
		LOG("[CMDCenterToFrontRight] MP Finished");

		return true;
	}

	return false;
}

/**
 *
 */
void CMDCenterToFrontRight::End()
{
	LOG("[CMDCenterToFrontRight] Ending" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void CMDCenterToFrontRight::Interrupted()
{
	LOG("[CMDCenterToFrontRight] Interrupted" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}
