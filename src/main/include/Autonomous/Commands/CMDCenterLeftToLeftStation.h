#ifndef _CMDCENTERLEFTTOLEFTSTATION_HG_
#define _CMDCENTERLEFTTOLEFTSTATION_HG_

#include <frc/WPILib.h>
#include <frc/Timer.h>
#include <frc/commands/Command.h>
#include "Autonomous/Profiles/PFLCenterLeftToLeftStation.h"

/**
 *
 */
class CMDCenterLeftToLeftStation : public frc::Command
{
public:
	CMDCenterLeftToLeftStation();
	~CMDCenterLeftToLeftStation();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	PFLCenterLeftToLeftStation* pMotionProfiler;
	Timer* pTimer;
};

#endif
