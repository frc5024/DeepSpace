#include "Autonomous/Commands/CMDLowerRightToRightFront.h"
#include "Robot.h"
#include "Utilities/Log.h"

/**
 *
 */
CMDLowerRightToRightFront::CMDLowerRightToRightFront()
{
	LOG("[CMDLowerRightToRightFront] Constructed");

	if (Robot::m_DriveTrain != nullptr)
	{
		Requires(Robot::m_DriveTrain);
		this->pMotionProfiler = new PFLLowerRightToRightFront(*Robot::m_DriveTrain->GetLeftFrontMotor(), *Robot::m_DriveTrain->GetRightFrontMotor());
	}
	else
	{
		LOG("[CMDLowerRightToRightFront] driveTrain is NULL");
	}

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
CMDLowerRightToRightFront::~CMDLowerRightToRightFront()
{
	delete this->pTimer;
	delete this->pMotionProfiler;

	return;
}

/**
 *
 */
void CMDLowerRightToRightFront::Initialize()
{
	LOG("[CMDLowerRightToRightFront] Initializing" );

	this->pTimer->Reset();
	this->pTimer->Start();

	Robot::m_DriveTrain->InitMotionProfilingMode();

	return;
}

/**
 *
 */
void CMDLowerRightToRightFront::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

//	LOG("[CMDLowerRightToRightFront] Set Output: " << setOutput);

	Robot::m_DriveTrain->GetLeftFrontMotor()->Set(ControlMode::MotionProfile, setOutput);
	Robot::m_DriveTrain->GetRightFrontMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	return;
}

/**
 *
 */
bool CMDLowerRightToRightFront::IsFinished()
{
	if (this->pMotionProfiler->isFinished())
	{
		LOG("[CMDLowerRightToRightFront] MP Finished");

		return true;
	}

	return false;
}

/**
 *
 */
void CMDLowerRightToRightFront::End()
{
	LOG("[CMDLowerRightToRightFront] Ending" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void CMDLowerRightToRightFront::Interrupted()
{
	LOG("[CMDLowerRightToRightFront] Interrupted" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}
