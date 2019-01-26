#include "Autonomous/Commands/CMDUpperRightToRightMiddle.h"
#include "Robot.h"
#include "Utilities/Log.h"

/**
 *
 */
CMDUpperRightToRightMiddle::CMDUpperRightToRightMiddle()
{
	LOG("[CMDUpperRightToRightMiddle] Constructed");

	if (Robot::m_DriveTrain != nullptr)
	{
		Requires(Robot::m_DriveTrain);
		this->pMotionProfiler = new PFLUpperRightToRightMiddle(*Robot::m_DriveTrain->GetLeftFrontMotor(), *Robot::m_DriveTrain->GetRightFrontMotor());
	}
	else
	{
		LOG("[CMDUpperRightToRightMiddle] driveTrain is NULL");
	}

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
CMDUpperRightToRightMiddle::~CMDUpperRightToRightMiddle()
{
	delete this->pTimer;
	delete this->pMotionProfiler;

	return;
}

/**
 *
 */
void CMDUpperRightToRightMiddle::Initialize()
{
	LOG("[CMDUpperRightToRightMiddle] Initializing" );

	this->pTimer->Reset();
	this->pTimer->Start();

	Robot::m_DriveTrain->InitMotionProfilingMode();

	return;
}

/**
 *
 */
void CMDUpperRightToRightMiddle::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

//	LOG("[CMDUpperRightToRightMiddle] Set Output: " << setOutput);

	Robot::m_DriveTrain->GetLeftFrontMotor()->Set(ControlMode::MotionProfile, setOutput);
	Robot::m_DriveTrain->GetRightFrontMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	return;
}

/**
 *
 */
bool CMDUpperRightToRightMiddle::IsFinished()
{
	if (this->pMotionProfiler->isFinished())
	{
		LOG("[CMDUpperRightToRightMiddle] MP Finished");

		return true;
	}

	return false;
}

/**
 *
 */
void CMDUpperRightToRightMiddle::End()
{
	LOG("[CMDUpperRightToRightMiddle] Ending" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void CMDUpperRightToRightMiddle::Interrupted()
{
	LOG("[CMDUpperRightToRightMiddle] Interrupted" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}
