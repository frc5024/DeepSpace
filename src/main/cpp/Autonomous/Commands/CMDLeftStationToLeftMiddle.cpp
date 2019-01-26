#include "Autonomous/Commands/CMDLeftStationToLeftMiddle.h"
#include "Robot.h"
#include "Utilities/Log.h"

/**
 *
 */
CMDLeftStationToLeftMiddle::CMDLeftStationToLeftMiddle()
{
	LOG("[CMDLeftStationToLeftMiddle] Constructed");

	if (Robot::m_DriveTrain != nullptr)
	{
		Requires(Robot::m_DriveTrain);
		this->pMotionProfiler = new PFLLeftStationToLeftMiddle(*Robot::m_DriveTrain->GetLeftFrontMotor(), *Robot::m_DriveTrain->GetRightFrontMotor());
	}
	else
	{
		LOG("[CMDLeftStationToLeftMiddle] driveTrain is NULL");
	}

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
CMDLeftStationToLeftMiddle::~CMDLeftStationToLeftMiddle()
{
	delete this->pTimer;
	delete this->pMotionProfiler;

	return;
}

/**
 *
 */
void CMDLeftStationToLeftMiddle::Initialize()
{
	LOG("[CMDLeftStationToLeftMiddle] Initializing" );

	this->pTimer->Reset();
	this->pTimer->Start();

	Robot::m_DriveTrain->InitMotionProfilingMode();

	return;
}

/**
 *
 */
void CMDLeftStationToLeftMiddle::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

//	LOG("[CMDLeftStationToLeftMiddle] Set Output: " << setOutput);

	Robot::m_DriveTrain->GetLeftFrontMotor()->Set(ControlMode::MotionProfile, setOutput);
	Robot::m_DriveTrain->GetRightFrontMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	return;
}

/**
 *
 */
bool CMDLeftStationToLeftMiddle::IsFinished()
{
	if (this->pMotionProfiler->isFinished())
	{
		LOG("[CMDLeftStationToLeftMiddle] MP Finished");

		return true;
	}

	return false;
}

/**
 *
 */
void CMDLeftStationToLeftMiddle::End()
{
	LOG("[CMDLeftStationToLeftMiddle] Ending" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void CMDLeftStationToLeftMiddle::Interrupted()
{
	LOG("[CMDLeftStationToLeftMiddle] Interrupted" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}
