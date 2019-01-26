#include "Autonomous/Commands/CMDLowerLeftToLeftBack.h"
#include "Robot.h"
#include "Utilities/Log.h"

/**
 *
 */
CMDLowerLeftToLeftBack::CMDLowerLeftToLeftBack()
{
	LOG("[CMDLowerLeftToLeftBack] Constructed");

	if (Robot::m_DriveTrain != nullptr)
	{
		Requires(Robot::m_DriveTrain);
		this->pMotionProfiler = new PFLLowerLeftToLeftBack(*Robot::m_DriveTrain->GetLeftFrontMotor(), *Robot::m_DriveTrain->GetRightFrontMotor());
	}
	else
	{
		LOG("[CMDLowerLeftToLeftBack] driveTrain is NULL");
	}

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
CMDLowerLeftToLeftBack::~CMDLowerLeftToLeftBack()
{
	delete this->pTimer;
	delete this->pMotionProfiler;

	return;
}

/**
 *
 */
void CMDLowerLeftToLeftBack::Initialize()
{
	LOG("[CMDLowerLeftToLeftBack] Initializing" );

	this->pTimer->Reset();
	this->pTimer->Start();

	Robot::m_DriveTrain->InitMotionProfilingMode();

	return;
}

/**
 *
 */
void CMDLowerLeftToLeftBack::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

//	LOG("[CMDLowerLeftToLeftBack] Set Output: " << setOutput);

	Robot::m_DriveTrain->GetLeftFrontMotor()->Set(ControlMode::MotionProfile, setOutput);
	Robot::m_DriveTrain->GetRightFrontMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	return;
}

/**
 *
 */
bool CMDLowerLeftToLeftBack::IsFinished()
{
	if (this->pMotionProfiler->isFinished())
	{
		LOG("[CMDLowerLeftToLeftBack] MP Finished");

		return true;
	}

	return false;
}

/**
 *
 */
void CMDLowerLeftToLeftBack::End()
{
	LOG("[CMDLowerLeftToLeftBack] Ending" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void CMDLowerLeftToLeftBack::Interrupted()
{
	LOG("[CMDLowerLeftToLeftBack] Interrupted" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}
