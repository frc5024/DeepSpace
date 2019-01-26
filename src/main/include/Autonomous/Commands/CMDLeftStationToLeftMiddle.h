#ifndef _CMDLEFTSTATIONTOLEFTMIDDLE_HG_
#define _CMDLEFTSTATIONTOLEFTMIDDLE_HG_

#include <frc/WPILib.h>
#include <frc/Timer.h>
#include <frc/commands/Command.h>
#include "Autonomous/Profiles/PFLLeftStationToLeftMiddle.h"

/**
 *
 */
class CMDLeftStationToLeftMiddle : public frc::Command
{
public:
	CMDLeftStationToLeftMiddle();
	~CMDLeftStationToLeftMiddle();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	PFLLeftStationToLeftMiddle* pMotionProfiler;
	Timer* pTimer;
};

#endif
