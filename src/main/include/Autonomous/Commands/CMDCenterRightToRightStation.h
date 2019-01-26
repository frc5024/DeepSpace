#ifndef _CMDCENTERRIGHTTORIGHTSTATION_HG_
#define _CMDCENTERRIGHTTORIGHTSTATION_HG_

#include <frc/WPILib.h>
#include <frc/Timer.h>
#include <frc/commands/Command.h>
#include "Autonomous/Profiles/PFLCenterRightToRightStation.h"

/**
 *
 */
class CMDCenterRightToRightStation : public frc::Command
{
public:
	CMDCenterRightToRightStation();
	~CMDCenterRightToRightStation();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	PFLCenterRightToRightStation* pMotionProfiler;
	Timer* pTimer;
};

#endif
