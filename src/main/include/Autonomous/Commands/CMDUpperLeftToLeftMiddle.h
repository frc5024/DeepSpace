#ifndef _CMDUPPERLEFTTOLEFTMIDDLE_HG_
#define _CMDUPPERLEFTTOLEFTMIDDLE_HG_

#include <frc/WPILib.h>
#include <frc/Timer.h>
#include <frc/commands/Command.h>
#include "Autonomous/Profiles/PFLUpperLeftToLeftMiddle.h"

/**
 *
 */
class CMDUpperLeftToLeftMiddle : public frc::Command
{
public:
	CMDUpperLeftToLeftMiddle();
	~CMDUpperLeftToLeftMiddle();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	PFLUpperLeftToLeftMiddle* pMotionProfiler;
	Timer* pTimer;
};

#endif
