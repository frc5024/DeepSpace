#ifndef _CMDUPPERLEFTTOLEFTFRONT_HG_
#define _CMDUPPERLEFTTOLEFTFRONT_HG_

#include <frc/WPILib.h>
#include <frc/Timer.h>
#include <frc/commands/Command.h>
#include "Autonomous/Profiles/PFLUpperLeftToLeftFront.h"

/**
 *
 */
class CMDUpperLeftToLeftFront : public frc::Command
{
public:
	CMDUpperLeftToLeftFront();
	~CMDUpperLeftToLeftFront();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	PFLUpperLeftToLeftFront* pMotionProfiler;
	Timer* pTimer;
};

#endif
