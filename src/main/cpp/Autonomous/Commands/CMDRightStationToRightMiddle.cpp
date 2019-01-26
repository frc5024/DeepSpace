#include "Autonomous/Commands/CMDRightStationToRightMiddle.h"
#include "Robot.h"
#include "Utilities/Log.h"

/**
 *
 */
CMDRightStationToRightMiddle::CMDRightStationToRightMiddle()
{
	LOG("[CMDRightStationToRightMiddle] Constructed");

	if (Robot::m_DriveTrain != nullptr)
	{
		Requires(Robot::m_DriveTrain);
		this->pMotionProfiler = new PFLRightStationToRightMiddle(*Robot::m_DriveTrain->GetLeftFrontMotor(), *Robot::m_DriveTrain->GetRightFrontMotor());
	}
	else
	{
		LOG("[CMDRightStationToRightMiddle] driveTrain is NULL");
	}

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
CMDRightStationToRightMiddle::~CMDRightStationToRightMiddle()
{
	delete this->pTimer;
	delete this->pMotionProfiler;

	return;
}

/**
 *
 */
void CMDRightStationToRightMiddle::Initialize()
{
	LOG("[CMDRightStationToRightMiddle] Initializing" );

	this->pTimer->Reset();
	this->pTimer->Start();

	Robot::m_DriveTrain->InitMotionProfilingMode();

	return;
}

/**
 *
 */
void CMDRightStationToRightMiddle::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

//	LOG("[CMDRightStationToRightMiddle] Set Output: " << setOutput);

	Robot::m_DriveTrain->GetLeftFrontMotor()->Set(ControlMode::MotionProfile, setOutput);
	Robot::m_DriveTrain->GetRightFrontMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	return;
}

/**
 *
 */
bool CMDRightStationToRightMiddle::IsFinished()
{
	if (this->pMotionProfiler->isFinished())
	{
		LOG("[CMDRightStationToRightMiddle] MP Finished");

		return true;
	}

	return false;
}

/**
 *
 */
void CMDRightStationToRightMiddle::End()
{
	LOG("[CMDRightStationToRightMiddle] Ending" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void CMDRightStationToRightMiddle::Interrupted()
{
	LOG("[CMDRightStationToRightMiddle] Interrupted" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}
