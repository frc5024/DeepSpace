#ifndef _CMDLEFTBACKTOLEFTSTATION_HG_
#define _CMDLEFTBACKTOLEFTSTATION_HG_

#include <frc/WPILib.h>
#include <frc/Timer.h>
#include <frc/commands/Command.h>
#include "Autonomous/Profiles/PFLLeftBackToLeftStation.h"

/**
 *
 */
class CMDLeftBackToLeftStation : public frc::Command
{
public:
	CMDLeftBackToLeftStation();
	~CMDLeftBackToLeftStation();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	PFLLeftBackToLeftStation* pMotionProfiler;
	Timer* pTimer;
};

#endif
