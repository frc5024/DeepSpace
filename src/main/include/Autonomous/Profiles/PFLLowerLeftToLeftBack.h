#ifndef _PFLUPPERLEFTTOLEFTBACK_HG_
#define _PFLUPPERLEFTTOLEFTBACK_HG_

#include <frc/WPILib.h>
#include <ctre/Phoenix.h>
#include "Autonomous/Instrumentation.h"

#include "Autonomous/Paths/PTHLowerLeftToLeftBack.h"

/**
 *
 */
class PFLLowerLeftToLeftBack
{
public:
	PFLLowerLeftToLeftBack(can::WPI_TalonSRX & leftTalon, can::WPI_TalonSRX & rightTalon);

	void control();
	SetValueMotionProfile getSetValue();
	int GetTrajectoryDuration(int durationMs);
	void PeriodicTask();
	void reset();
	void start();
	void startFilling();
	void startFilling(const double profileLeft[][3], const double profileRight[][3], int totalCnt);
	bool isFinished();

private:
	MotionProfileStatus _status;
	double _pos = 0, _vel = 0, _heading = 0;
	TalonSRX & _talonLeft;
	TalonSRX & _talonRight;
	int _state = 0;
	int _loopTimeout = -1;
	bool _bStart = false;
	SetValueMotionProfile _setValue;
	static const int kMinPointsInTalon = 5;
	static const int kNumLoopsTimeout = 10;
	Notifier _notifer;
};

#endif
