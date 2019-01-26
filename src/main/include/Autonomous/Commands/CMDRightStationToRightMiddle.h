#ifndef _CMDRIGHTSTATIONTORIGHTMIDDLE_HG_
#define _CMDRIGHTSTATIONTORIGHTMIDDLE_HG_

#include <frc/WPILib.h>
#include <frc/Timer.h>
#include <frc/commands/Command.h>
#include "Autonomous/Profiles/PFLRightStationToRightMiddle.h"

/**
 *
 */
class CMDRightStationToRightMiddle : public frc::Command
{
public:
	CMDRightStationToRightMiddle();
	~CMDRightStationToRightMiddle();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	PFLRightStationToRightMiddle* pMotionProfiler;
	Timer* pTimer;
};

#endif
