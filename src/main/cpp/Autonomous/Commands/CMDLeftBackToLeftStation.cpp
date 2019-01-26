#include "Autonomous/Commands/CMDLeftBackToLeftStation.h"
#include "Robot.h"
#include "Utilities/Log.h"

/**
 *
 */
CMDLeftBackToLeftStation::CMDLeftBackToLeftStation()
{
	LOG("[CMDLeftBackToLeftStation] Constructed");

	if (Robot::m_DriveTrain != nullptr)
	{
		Requires(Robot::m_DriveTrain);
		this->pMotionProfiler = new PFLLeftBackToLeftStation(*Robot::m_DriveTrain->GetLeftFrontMotor(), *Robot::m_DriveTrain->GetRightFrontMotor());
	}
	else
	{
		LOG("[CMDLeftBackToLeftStation] driveTrain is NULL");
	}

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
CMDLeftBackToLeftStation::~CMDLeftBackToLeftStation()
{
	delete this->pTimer;
	delete this->pMotionProfiler;

	return;
}

/**
 *
 */
void CMDLeftBackToLeftStation::Initialize()
{
	LOG("[CMDLeftBackToLeftStation] Initializing" );

	this->pTimer->Reset();
	this->pTimer->Start();

	Robot::m_DriveTrain->InitMotionProfilingMode();

	return;
}

/**
 *
 */
void CMDLeftBackToLeftStation::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

//	LOG("[CMDLeftBackToLeftStation] Set Output: " << setOutput);

	Robot::m_DriveTrain->GetLeftFrontMotor()->Set(ControlMode::MotionProfile, setOutput);
	Robot::m_DriveTrain->GetRightFrontMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	return;
}

/**
 *
 */
bool CMDLeftBackToLeftStation::IsFinished()
{
	if (this->pMotionProfiler->isFinished())
	{
		LOG("[CMDLeftBackToLeftStation] MP Finished");

		return true;
	}

	return false;
}

/**
 *
 */
void CMDLeftBackToLeftStation::End()
{
	LOG("[CMDLeftBackToLeftStation] Ending" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void CMDLeftBackToLeftStation::Interrupted()
{
	LOG("[CMDLeftBackToLeftStation] Interrupted" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}
