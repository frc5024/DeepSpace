#ifndef _CMDLOWERLEFTTOLEFTMIDDLE_HG_
#define _CMDLOWERLEFTTOLEFTMIDDLE_HG_

#include <frc/WPILib.h>
#include <frc/Timer.h>
#include <frc/commands/Command.h>
#include "Autonomous/Profiles/PFLLowerLeftToLeftMiddle.h"

/**
 *
 */
class CMDLowerLeftToLeftMiddle : public frc::Command
{
public:
	CMDLowerLeftToLeftMiddle();
	~CMDLowerLeftToLeftMiddle();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	PFLLowerLeftToLeftMiddle* pMotionProfiler;
	Timer* pTimer;
};

#endif
