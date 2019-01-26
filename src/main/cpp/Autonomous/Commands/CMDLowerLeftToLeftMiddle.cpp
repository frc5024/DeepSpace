#include "Autonomous/Commands/CMDLowerLeftToLeftMiddle.h"
#include "Robot.h"
#include "Utilities/Log.h"

/**
 *
 */
CMDLowerLeftToLeftMiddle::CMDLowerLeftToLeftMiddle()
{
	LOG("[CMDLowerLeftToLeftMiddle] Constructed");

	if (Robot::m_DriveTrain != nullptr)
	{
		Requires(Robot::m_DriveTrain);
		this->pMotionProfiler = new PFLLowerLeftToLeftMiddle(*Robot::m_DriveTrain->GetLeftFrontMotor(), *Robot::m_DriveTrain->GetRightFrontMotor());
	}
	else
	{
		LOG("[CMDLowerLeftToLeftMiddle] driveTrain is NULL");
	}

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
CMDLowerLeftToLeftMiddle::~CMDLowerLeftToLeftMiddle()
{
	delete this->pTimer;
	delete this->pMotionProfiler;

	return;
}

/**
 *
 */
void CMDLowerLeftToLeftMiddle::Initialize()
{
	LOG("[CMDLowerLeftToLeftMiddle] Initializing" );

	this->pTimer->Reset();
	this->pTimer->Start();

	Robot::m_DriveTrain->InitMotionProfilingMode();

	return;
}

/**
 *
 */
void CMDLowerLeftToLeftMiddle::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

//	LOG("[CMDLowerLeftToLeftMiddle] Set Output: " << setOutput);

	Robot::m_DriveTrain->GetLeftFrontMotor()->Set(ControlMode::MotionProfile, setOutput);
	Robot::m_DriveTrain->GetRightFrontMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	return;
}

/**
 *
 */
bool CMDLowerLeftToLeftMiddle::IsFinished()
{
	if (this->pMotionProfiler->isFinished())
	{
		LOG("[CMDLowerLeftToLeftMiddle] MP Finished");

		return true;
	}

	return false;
}

/**
 *
 */
void CMDLowerLeftToLeftMiddle::End()
{
	LOG("[CMDLowerLeftToLeftMiddle] Ending" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void CMDLowerLeftToLeftMiddle::Interrupted()
{
	LOG("[CMDLowerLeftToLeftMiddle] Interrupted" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}
