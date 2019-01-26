#ifndef _CMDUPPERLEFTTOLEFTBACK_HG_
#define _CMDUPPERLEFTTOLEFTBACK_HG_

#include <frc/WPILib.h>
#include <frc/Timer.h>
#include <frc/commands/Command.h>
#include "Autonomous/Profiles/PFLLowerRightToRightBack.h"

/**
 *
 */
class CMDLowerRightToRightBack : public frc::Command
{
public:
	CMDLowerRightToRightBack();
	~CMDLowerRightToRightBack();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	PFLLowerRightToRightBack* pMotionProfiler;
	Timer* pTimer;
};

#endif
