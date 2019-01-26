#ifndef _CMDLOWERRIGHTTORIGHTFRONT_HG_
#define _CMDLOWERRIGHTTORIGHTFRONT_HG_

#include <frc/WPILib.h>
#include <frc/Timer.h>
#include <frc/commands/Command.h>
#include "Autonomous/Profiles/PFLLowerRightToRightFront.h"

/**
 *
 */
class CMDLowerRightToRightFront : public frc::Command
{
public:
	CMDLowerRightToRightFront();
	~CMDLowerRightToRightFront();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	PFLLowerRightToRightFront* pMotionProfiler;
	Timer* pTimer;
};

#endif
