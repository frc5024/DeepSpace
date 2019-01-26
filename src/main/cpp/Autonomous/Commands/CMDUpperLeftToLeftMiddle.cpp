#include "Autonomous/Commands/CMDUpperLeftToLeftMiddle.h"
#include "Robot.h"
#include "Utilities/Log.h"

/**
 *
 */
CMDUpperLeftToLeftMiddle::CMDUpperLeftToLeftMiddle()
{
	LOG("[CMDUpperLeftToLeftMiddle] Constructed");

	if (Robot::m_DriveTrain != nullptr)
	{
		Requires(Robot::m_DriveTrain);
		this->pMotionProfiler = new PFLUpperLeftToLeftMiddle(*Robot::m_DriveTrain->GetLeftFrontMotor(), *Robot::m_DriveTrain->GetRightFrontMotor());
	}
	else
	{
		LOG("[CMDUpperLeftToLeftMiddle] driveTrain is NULL");
	}

	this->pTimer = new Timer();

	return;
}

/**
 *
 */
CMDUpperLeftToLeftMiddle::~CMDUpperLeftToLeftMiddle()
{
	delete this->pTimer;
	delete this->pMotionProfiler;

	return;
}

/**
 *
 */
void CMDUpperLeftToLeftMiddle::Initialize()
{
	LOG("[CMDUpperLeftToLeftMiddle] Initializing" );

	this->pTimer->Reset();
	this->pTimer->Start();

	Robot::m_DriveTrain->InitMotionProfilingMode();

	return;
}

/**
 *
 */
void CMDUpperLeftToLeftMiddle::Execute()
{
	this->pMotionProfiler->control();
	this->pMotionProfiler->PeriodicTask();

	SetValueMotionProfile setOutput = this->pMotionProfiler->getSetValue();

//	LOG("[CMDUpperLeftToLeftMiddle] Set Output: " << setOutput);

	Robot::m_DriveTrain->GetLeftFrontMotor()->Set(ControlMode::MotionProfile, setOutput);
	Robot::m_DriveTrain->GetRightFrontMotor()->Set(ControlMode::MotionProfile, setOutput);

	this->pMotionProfiler->start();

	return;
}

/**
 *
 */
bool CMDUpperLeftToLeftMiddle::IsFinished()
{
	if (this->pMotionProfiler->isFinished())
	{
		LOG("[CMDUpperLeftToLeftMiddle] MP Finished");

		return true;
	}

	return false;
}

/**
 *
 */
void CMDUpperLeftToLeftMiddle::End()
{
	LOG("[CMDUpperLeftToLeftMiddle] Ending" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}

/**
 *
 */
void CMDUpperLeftToLeftMiddle::Interrupted()
{
	LOG("[CMDUpperLeftToLeftMiddle] Interrupted" );

	this->pMotionProfiler->reset();
	Robot::m_DriveTrain->ResetDrive();

	return;
}
