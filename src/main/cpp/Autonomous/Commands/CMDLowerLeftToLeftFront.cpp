#include "Autonomous/Commands/CMDLowerLeftToLeftFront.h"
#include "Robot.h"
#include "Utilities/Log.h"

/**
 *
 */
CMDLowerLeftToLeftFront::CMDLowerLeftToLeftFront()
{
	LOG("[CMDLowerLeftToLeftFront] Constructed");

	if (Robot::m_DriveTrain != nullptr)
	{
		Requires(Robot::m_DriveTrain);
		this->pMotionProfiler = new PFLLowerLeftToLeftFront(*Robot::m_DriveTrain->GetLeftFrontMotor(), *Robot::m_DriveTrain->GetRightFrontMotor());
	}
	else
	{
		LOG("[CMDLowerLeftToLeftFront] driveTrain is NULL");
	}

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
CMDLowerLeftToLeftFront::~CMDLowerLeftToLeftFront()
{
	delete this->pTimer;
	delete this->pMotionProfiler;

	return;
}

/**
 *
 */
void CMDLowerLeftToLeftFront::Initialize()
{
	LOG("[CMDLowerLeftToLeftFront] Initializing" );

	this->pTimer->Reset();
	this->pTimer->Start();

	Robot::m_DriveTrain->InitMotionProfilingMode();

	return;
}

/**
 *
 */
void CMDLowerLeftToLeftFront::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

//	LOG("[CMDLowerLeftToLeftFront] Set Output: " << setOutput);

	Robot::m_DriveTrain->GetLeftFrontMotor()->Set(ControlMode::MotionProfile, setOutput);
	Robot::m_DriveTrain->GetRightFrontMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	return;
}

/**
 *
 */
bool CMDLowerLeftToLeftFront::IsFinished()
{
	if (this->pMotionProfiler->isFinished())
	{
		LOG("[CMDLowerLeftToLeftFront] MP Finished");

		return true;
	}

	return false;
}

/**
 *
 */
void CMDLowerLeftToLeftFront::End()
{
	LOG("[CMDLowerLeftToLeftFront] Ending" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void CMDLowerLeftToLeftFront::Interrupted()
{
	LOG("[CMDLowerLeftToLeftFront] Interrupted" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}
