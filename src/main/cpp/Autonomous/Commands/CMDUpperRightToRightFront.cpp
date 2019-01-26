#include "Autonomous/Commands/CMDUpperRightToRightFront.h"
#include "Robot.h"
#include "Utilities/Log.h"

/**
 *
 */
CMDUpperRightToRightFront::CMDUpperRightToRightFront()
{
	LOG("[CMDUpperRightToRightFront] Constructed");

	if (Robot::m_DriveTrain != nullptr)
	{
		Requires(Robot::m_DriveTrain);
		this->pMotionProfiler = new PFLUpperRightToRightFront(*Robot::m_DriveTrain->GetLeftFrontMotor(), *Robot::m_DriveTrain->GetRightFrontMotor());
	}
	else
	{
		LOG("[CMDUpperRightToRightFront] driveTrain is NULL");
	}

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
CMDUpperRightToRightFront::~CMDUpperRightToRightFront()
{
	delete this->pTimer;
	delete this->pMotionProfiler;

	return;
}

/**
 *
 */
void CMDUpperRightToRightFront::Initialize()
{
	LOG("[CMDUpperRightToRightFront] Initializing" );

	this->pTimer->Reset();
	this->pTimer->Start();

	Robot::m_DriveTrain->InitMotionProfilingMode();

	return;
}

/**
 *
 */
void CMDUpperRightToRightFront::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

//	LOG("[CMDUpperRightToRightFront] Set Output: " << setOutput);

	Robot::m_DriveTrain->GetLeftFrontMotor()->Set(ControlMode::MotionProfile, setOutput);
	Robot::m_DriveTrain->GetRightFrontMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	return;
}

/**
 *
 */
bool CMDUpperRightToRightFront::IsFinished()
{
	if (this->pMotionProfiler->isFinished())
	{
		LOG("[CMDUpperRightToRightFront] MP Finished");

		return true;
	}

	return false;
}

/**
 *
 */
void CMDUpperRightToRightFront::End()
{
	LOG("[CMDUpperRightToRightFront] Ending" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void CMDUpperRightToRightFront::Interrupted()
{
	LOG("[CMDUpperRightToRightFront] Interrupted" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}
