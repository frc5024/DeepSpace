#ifndef _CMDLOWERLEFTTOLEFTFRONT_HG_
#define _CMDLOWERLEFTTOLEFTFRONT_HG_

#include <frc/WPILib.h>
#include <frc/Timer.h>
#include <frc/commands/Command.h>
#include "Autonomous/Profiles/PFLLowerLeftToLeftFront.h"

/**
 *
 */
class CMDLowerLeftToLeftFront : public frc::Command
{
public:
	CMDLowerLeftToLeftFront();
	~CMDLowerLeftToLeftFront();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	PFLLowerLeftToLeftFront* pMotionProfiler;
	Timer* pTimer;
};

#endif
