#include "Autonomous/Commands/CMDUpperLeftToLeftBack.h"
#include "Robot.h"
#include "Utilities/Log.h"

/**
 *
 */
CMDUpperLeftToLeftBack::CMDUpperLeftToLeftBack()
{
	LOG("[CMDUpperLeftToLeftBack] Constructed");

	if (Robot::m_DriveTrain != nullptr)
	{
		Requires(Robot::m_DriveTrain);
		this->pMotionProfiler = new PFLUpperLeftToLeftBack(*Robot::m_DriveTrain->GetLeftFrontMotor(), *Robot::m_DriveTrain->GetRightFrontMotor());
	}
	else
	{
		LOG("[CMDUpperLeftToLeftBack] driveTrain is NULL");
	}

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
CMDUpperLeftToLeftBack::~CMDUpperLeftToLeftBack()
{
	delete this->pTimer;
	delete this->pMotionProfiler;

	return;
}

/**
 *
 */
void CMDUpperLeftToLeftBack::Initialize()
{
	LOG("[CMDUpperLeftToLeftBack] Initializing" );

	this->pTimer->Reset();
	this->pTimer->Start();

	Robot::m_DriveTrain->InitMotionProfilingMode();

	return;
}

/**
 *
 */
void CMDUpperLeftToLeftBack::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

//	LOG("[CMDUpperLeftToLeftBack] Set Output: " << setOutput);

	Robot::m_DriveTrain->GetLeftFrontMotor()->Set(ControlMode::MotionProfile, setOutput);
	Robot::m_DriveTrain->GetRightFrontMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	return;
}

/**
 *
 */
bool CMDUpperLeftToLeftBack::IsFinished()
{
	if (this->pMotionProfiler->isFinished())
	{
		LOG("[CMDUpperLeftToLeftBack] MP Finished");

		return true;
	}

	return false;
}

/**
 *
 */
void CMDUpperLeftToLeftBack::End()
{
	LOG("[CMDUpperLeftToLeftBack] Ending" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void CMDUpperLeftToLeftBack::Interrupted()
{
	LOG("[CMDUpperLeftToLeftBack] Interrupted" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}
