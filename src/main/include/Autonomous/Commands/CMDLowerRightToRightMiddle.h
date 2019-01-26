#ifndef _CMDLOWERRIGHTTORIGHTMIDDLE_HG_
#define _CMDLOWERRIGHTTORIGHTMIDDLE_HG_

#include <frc/WPILib.h>
#include <frc/Timer.h>
#include <frc/commands/Command.h>
#include "Autonomous/Profiles/PFLLowerRightToRightMiddle.h"

/**
 *
 */
class CMDLowerRightToRightMiddle : public frc::Command
{
public:
	CMDLowerRightToRightMiddle();
	~CMDLowerRightToRightMiddle();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	PFLLowerRightToRightMiddle* pMotionProfiler;
	Timer* pTimer;
};

#endif
