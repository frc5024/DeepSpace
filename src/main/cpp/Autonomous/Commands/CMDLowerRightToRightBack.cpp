#include "Autonomous/Commands/CMDLowerRightToRightBack.h"
#include "Robot.h"
#include "Utilities/Log.h"

/**
 *
 */
CMDLowerRightToRightBack::CMDLowerRightToRightBack()
{
	LOG("[CMDLowerRightToRightBack] Constructed");

	if (Robot::m_DriveTrain != nullptr)
	{
		Requires(Robot::m_DriveTrain);
		this->pMotionProfiler = new PFLLowerRightToRightBack(*Robot::m_DriveTrain->GetLeftFrontMotor(), *Robot::m_DriveTrain->GetRightFrontMotor());
	}
	else
	{
		LOG("[CMDLowerRightToRightBack] driveTrain is NULL");
	}

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
CMDLowerRightToRightBack::~CMDLowerRightToRightBack()
{
	delete this->pTimer;
	delete this->pMotionProfiler;

	return;
}

/**
 *
 */
void CMDLowerRightToRightBack::Initialize()
{
	LOG("[CMDLowerRightToRightBack] Initializing" );

	this->pTimer->Reset();
	this->pTimer->Start();

	Robot::m_DriveTrain->InitMotionProfilingMode();

	return;
}

/**
 *
 */
void CMDLowerRightToRightBack::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

//	LOG("[CMDLowerRightToRightBack] Set Output: " << setOutput);

	Robot::m_DriveTrain->GetLeftFrontMotor()->Set(ControlMode::MotionProfile, setOutput);
	Robot::m_DriveTrain->GetRightFrontMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	return;
}

/**
 *
 */
bool CMDLowerRightToRightBack::IsFinished()
{
	if (this->pMotionProfiler->isFinished())
	{
		LOG("[CMDLowerRightToRightBack] MP Finished");

		return true;
	}

	return false;
}

/**
 *
 */
void CMDLowerRightToRightBack::End()
{
	LOG("[CMDLowerRightToRightBack] Ending" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void CMDLowerRightToRightBack::Interrupted()
{
	LOG("[CMDLowerRightToRightBack] Interrupted" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}
