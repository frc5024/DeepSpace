#include "Autonomous/Commands/CMDUpperLeftToLeftFront.h"
#include "Robot.h"
#include "Utilities/Log.h"

/**
 *
 */
CMDUpperLeftToLeftFront::CMDUpperLeftToLeftFront()
{
	LOG("[CMDUpperLeftToLeftFront] Constructed");

	if (Robot::m_DriveTrain != nullptr)
	{
		Requires(Robot::m_DriveTrain);
		this->pMotionProfiler = new PFLUpperLeftToLeftFront(*Robot::m_DriveTrain->GetLeftFrontMotor(), *Robot::m_DriveTrain->GetRightFrontMotor());
	}
	else
	{
		LOG("[CMDUpperLeftToLeftFront] driveTrain is NULL");
	}

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
CMDUpperLeftToLeftFront::~CMDUpperLeftToLeftFront()
{
	delete this->pTimer;
	delete this->pMotionProfiler;

	return;
}

/**
 *
 */
void CMDUpperLeftToLeftFront::Initialize()
{
	LOG("[CMDUpperLeftToLeftFront] Initializing" );

	this->pTimer->Reset();
	this->pTimer->Start();

	Robot::m_DriveTrain->InitMotionProfilingMode();

	return;
}

/**
 *
 */
void CMDUpperLeftToLeftFront::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

//	LOG("[CMDUpperLeftToLeftFront] Set Output: " << setOutput);

	Robot::m_DriveTrain->GetLeftFrontMotor()->Set(ControlMode::MotionProfile, setOutput);
	Robot::m_DriveTrain->GetRightFrontMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	return;
}

/**
 *
 */
bool CMDUpperLeftToLeftFront::IsFinished()
{
	if (this->pMotionProfiler->isFinished())
	{
		LOG("[CMDUpperLeftToLeftFront] MP Finished");

		return true;
	}

	return false;
}

/**
 *
 */
void CMDUpperLeftToLeftFront::End()
{
	LOG("[CMDUpperLeftToLeftFront] Ending" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void CMDUpperLeftToLeftFront::Interrupted()
{
	LOG("[CMDUpperLeftToLeftFront] Interrupted" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}
