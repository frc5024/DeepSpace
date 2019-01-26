#include "Autonomous/Commands/CMDRightBackToRightStation.h"
#include "Robot.h"
#include "Utilities/Log.h"

/**
 *
 */
CMDRightBackToRightStation::CMDRightBackToRightStation()
{
	LOG("[CMDRightBackToRightStation] Constructed");

	if (Robot::m_DriveTrain != nullptr)
	{
		Requires(Robot::m_DriveTrain);
		this->pMotionProfiler = new PFLRightBackToRightStation(*Robot::m_DriveTrain->GetLeftFrontMotor(), *Robot::m_DriveTrain->GetRightFrontMotor());
	}
	else
	{
		LOG("[CMDRightBackToRightStation] driveTrain is NULL");
	}

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
CMDRightBackToRightStation::~CMDRightBackToRightStation()
{
	delete this->pTimer;
	delete this->pMotionProfiler;

	return;
}

/**
 *
 */
void CMDRightBackToRightStation::Initialize()
{
	LOG("[CMDRightBackToRightStation] Initializing" );

	this->pTimer->Reset();
	this->pTimer->Start();

	Robot::m_DriveTrain->InitMotionProfilingMode();

	return;
}

/**
 *
 */
void CMDRightBackToRightStation::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

//	LOG("[CMDRightBackToRightStation] Set Output: " << setOutput);

	Robot::m_DriveTrain->GetLeftFrontMotor()->Set(ControlMode::MotionProfile, setOutput);
	Robot::m_DriveTrain->GetRightFrontMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	return;
}

/**
 *
 */
bool CMDRightBackToRightStation::IsFinished()
{
	if (this->pMotionProfiler->isFinished())
	{
		LOG("[CMDRightBackToRightStation] MP Finished");

		return true;
	}

	return false;
}

/**
 *
 */
void CMDRightBackToRightStation::End()
{
	LOG("[CMDRightBackToRightStation] Ending" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void CMDRightBackToRightStation::Interrupted()
{
	LOG("[CMDRightBackToRightStation] Interrupted" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}
