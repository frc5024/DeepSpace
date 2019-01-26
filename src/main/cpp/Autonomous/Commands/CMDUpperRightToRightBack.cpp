#include "Autonomous/Commands/CMDUpperRightToRightBack.h"
#include "Robot.h"
#include "Utilities/Log.h"

/**
 *
 */
CMDUpperRightToRightBack::CMDUpperRightToRightBack()
{
	LOG("[CMDUpperRightToRightBack] Constructed");

	if (Robot::m_DriveTrain != nullptr)
	{
		Requires(Robot::m_DriveTrain);
		this->pMotionProfiler = new PFLUpperRightToRightBack(*Robot::m_DriveTrain->GetLeftFrontMotor(), *Robot::m_DriveTrain->GetRightFrontMotor());
	}
	else
	{
		LOG("[CMDUpperRightToRightBack] driveTrain is NULL");
	}

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
CMDUpperRightToRightBack::~CMDUpperRightToRightBack()
{
	delete this->pTimer;
	delete this->pMotionProfiler;

	return;
}

/**
 *
 */
void CMDUpperRightToRightBack::Initialize()
{
	LOG("[CMDUpperRightToRightBack] Initializing" );

	this->pTimer->Reset();
	this->pTimer->Start();

	Robot::m_DriveTrain->InitMotionProfilingMode();

	return;
}

/**
 *
 */
void CMDUpperRightToRightBack::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

//	LOG("[CMDUpperRightToRightBack] Set Output: " << setOutput);

	Robot::m_DriveTrain->GetLeftFrontMotor()->Set(ControlMode::MotionProfile, setOutput);
	Robot::m_DriveTrain->GetRightFrontMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	return;
}

/**
 *
 */
bool CMDUpperRightToRightBack::IsFinished()
{
	if (this->pMotionProfiler->isFinished())
	{
		LOG("[CMDUpperRightToRightBack] MP Finished");

		return true;
	}

	return false;
}

/**
 *
 */
void CMDUpperRightToRightBack::End()
{
	LOG("[CMDUpperRightToRightBack] Ending" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void CMDUpperRightToRightBack::Interrupted()
{
	LOG("[CMDUpperRightToRightBack] Interrupted" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}
