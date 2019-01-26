#include "Autonomous/Commands/CMDCenterToFrontLeft.h"
#include "Robot.h"
#include "Utilities/Log.h"

/**
 *
 */
CMDCenterToFrontLeft::CMDCenterToFrontLeft()
{
	LOG("[CMDCenterToFrontLeft] Constructed");

	if (Robot::m_DriveTrain != nullptr)
	{
		Requires(Robot::m_DriveTrain);
		this->pMotionProfiler = new PFLCenterToFrontLeft(*Robot::m_DriveTrain->GetLeftFrontMotor(), *Robot::m_DriveTrain->GetRightFrontMotor());
	}
	else
	{
		LOG("[CMDCenterToFrontLeft] driveTrain is NULL");
	}

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
CMDCenterToFrontLeft::~CMDCenterToFrontLeft()
{
	delete this->pTimer;
	delete this->pMotionProfiler;

	return;
}

/**
 *
 */
void CMDCenterToFrontLeft::Initialize()
{
	LOG("[CMDCenterToFrontLeft] Initializing" );

	this->pTimer->Reset();
	this->pTimer->Start();

	Robot::m_DriveTrain->InitMotionProfilingMode();

	return;
}

/**
 *
 */
void CMDCenterToFrontLeft::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

//	LOG("[CMDCenterToFrontLeft] Set Output: " << setOutput);

	Robot::m_DriveTrain->GetLeftFrontMotor()->Set(ControlMode::MotionProfile, setOutput);
	Robot::m_DriveTrain->GetRightFrontMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	return;
}

/**
 *
 */
bool CMDCenterToFrontLeft::IsFinished()
{
	if (this->pMotionProfiler->isFinished())
	{
		LOG("[CMDCenterToFrontLeft] MP Finished");

		return true;
	}

	return false;
}

/**
 *
 */
void CMDCenterToFrontLeft::End()
{
	LOG("[CMDCenterToFrontLeft] Ending" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void CMDCenterToFrontLeft::Interrupted()
{
	LOG("[CMDCenterToFrontLeft] Interrupted" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}
