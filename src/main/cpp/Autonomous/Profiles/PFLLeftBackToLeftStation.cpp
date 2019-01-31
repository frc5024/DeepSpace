#include "Autonomous/Profiles/PFLLeftBackToLeftStation.h"
#include "RobotMap.h"

/**
 *
 */
PFLLeftBackToLeftStation::PFLLeftBackToLeftStation(can::WPI_TalonSRX & talonLeft, can::WPI_TalonSRX & talonRight) : 
	_talonLeft(talonLeft), _talonRight(talonRight), _notifer(&PFLLeftBackToLeftStation::PeriodicTask, this)
{
	_pos = 0, _vel = 0, _heading = 0, _state = 0;
	_loopTimeout = 30;
	_bStart = false;
	_setValue = SetValueMotionProfile::Disable;

	_talonLeft.ChangeMotionControlFramePeriod(5);
	_talonRight.ChangeMotionControlFramePeriod(5);

	_notifer.StartPeriodic(0.005);

	return;
}

/**
 *
 */
void PFLLeftBackToLeftStation::PeriodicTask()
{
	_talonLeft.ProcessMotionProfileBuffer();
	_talonRight.ProcessMotionProfileBuffer();
}

/**
 *
 */
void PFLLeftBackToLeftStation::reset()
{
	_talonLeft.ClearMotionProfileTrajectories();
	_talonRight.ClearMotionProfileTrajectories();
	_setValue = SetValueMotionProfile::Disable;
	_state = 0;
	_loopTimeout = -1;
	_bStart = false;
}

/**
 * Called every loop.
 */
void PFLLeftBackToLeftStation::control()
{
	if (_loopTimeout < 0)
	{
		/* do nothing, timeout is disabled */
	} else
	{
		if (_loopTimeout == 0)
		{
			Instrumentation::OnNoProgress();
		}
		else
		{
			--_loopTimeout;
		}
	}

	if (_talonLeft.GetControlMode() != ControlMode::MotionProfile)
	{
		_state = 0;
		_loopTimeout = -1;
	}
	else
	{
		switch (_state)
		{
			case 0: /* wait for application to tell us to start an MP */
				if (_bStart)
				{
					_bStart = false;

					_setValue = SetValueMotionProfile::Disable;
					startFilling();

					/*
					 * MP is being sent to CAN bus, wait a small amount of time
					 */
					_state = 1;
					_loopTimeout = kNumLoopsTimeout;
				}
				break;
			case 1:
				if (_status.btmBufferCnt > kMinPointsInTalon)
				{
					_setValue = SetValueMotionProfile::Enable;
					_state = 2;
					_loopTimeout = kNumLoopsTimeout;
				}
				break;
			case 2: /* check the status of the MP */
				if (_status.isUnderrun == false)
				{
					_loopTimeout = kNumLoopsTimeout;
				}

				if (_status.activePointValid && _status.isLast)
				{
					_setValue = SetValueMotionProfile::Hold;
					_state = 0;
					_loopTimeout = -1;
				}
				break;
		}

		/* Get the motion profile status every loop */
		_talonLeft.GetMotionProfileStatus(_status);
		_heading = _talonLeft.GetActiveTrajectoryPosition(1);
		_pos = _talonLeft.GetActiveTrajectoryPosition();
		_vel = _talonLeft.GetActiveTrajectoryVelocity();

		/* printfs and/or logging */
		Instrumentation::Process(_status, _pos, _vel, _heading);
	}
}

/**
 *
 */
int PFLLeftBackToLeftStation::GetTrajectoryDuration(int durationMs)
{
	return durationMs;
}

/**
 *
 */
void PFLLeftBackToLeftStation::startFilling()
{
	startFilling(kLeftBackToLeftStationLeft, kLeftBackToLeftStationRight, kLeftBackToLeftStationSz);
}

/**
 *
 */
bool PFLLeftBackToLeftStation::isFinished()
{
	return _setValue == SetValueMotionProfile::Hold;
}

/**
 *
 */
void PFLLeftBackToLeftStation::startFilling(const double profileLeft[][3], const double profileRight[][3], int totalCnt)
{
	TrajectoryPoint pointLeft;
	TrajectoryPoint pointRight;

	if (_status.hasUnderrun) {
		Instrumentation::OnUnderrun();
		_talonLeft.ClearMotionProfileHasUnderrun(TIMEOUT_MS);
		_talonRight.ClearMotionProfileHasUnderrun(TIMEOUT_MS);
	}

	_talonLeft.ClearMotionProfileTrajectories();
	_talonRight.ClearMotionProfileTrajectories();

	_talonLeft.ConfigMotionProfileTrajectoryPeriod(BASE_TRAJECTORY_PERIOD_MS, TIMEOUT_MS);
	_talonRight.ConfigMotionProfileTrajectoryPeriod(BASE_TRAJECTORY_PERIOD_MS, TIMEOUT_MS);

	for (int i = 0; i < totalCnt; ++i)
	{
		double positionRotLeft  = profileLeft[i][0];
		double velocityRPMLeft  = profileLeft[i][1];
		double positionRotRight = profileRight[i][0];
		double velocityRPMRight = profileRight[i][1];

		pointLeft.position = positionRotLeft * 5120; //Convert Revolutions to Units
		pointLeft.velocity = velocityRPMLeft * 5120 / 600.0; //Convert RPM to Units/100ms
		pointLeft.headingDeg = 0; /* future feature - not used in this example*/
		pointLeft.profileSlotSelect0 = 0; /* which set of gains would you like to use [0,3]? */
		pointLeft.profileSlotSelect1 = 0; /* future feature  - not used in this example - cascaded PID [0,1], leave zero */
		pointLeft.timeDur = GetTrajectoryDuration((int) profileLeft[i][2]);
		pointLeft.zeroPos = false;
		if (i == 0)
			pointLeft.zeroPos = true; /* set this to true on the first point */

		pointLeft.isLastPoint = false;
		if ((i + 1) == totalCnt)
			pointLeft.isLastPoint = true; /* set this to true on the last point  */

		pointRight.position = positionRotRight * 5120; //Convert Revolutions to Units
		pointRight.velocity = velocityRPMRight * 5120 / 600.0; //Convert RPM to Units/100ms
		pointRight.headingDeg = 0; /* future feature - not used in this example*/
		pointRight.profileSlotSelect0 = 0; /* which set of gains would you like to use [0,3]? */
		pointRight.profileSlotSelect1 = 0; /* future feature  - not used in this example - cascaded PID [0,1], leave zero */
		pointRight.timeDur = GetTrajectoryDuration((int) profileRight[i][2]);
		pointRight.zeroPos = false;
		if (i == 0)
			pointRight.zeroPos = true; /* set this to true on the first point */

		pointRight.isLastPoint = false;
		if ((i + 1) == totalCnt)
			pointRight.isLastPoint = true; /* set this to true on the last point  */

		_talonLeft.PushMotionProfileTrajectory(pointLeft);
		_talonRight.PushMotionProfileTrajectory(pointRight);
	}
}

/**
 *
 */
void PFLLeftBackToLeftStation::start()
{
	_bStart = true;
}

/**
 *
 */
SetValueMotionProfile PFLLeftBackToLeftStation::getSetValue()
{
	return _setValue;
}
