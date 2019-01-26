#ifndef _CMDUPPERLEFTTOLEFTBACK_HG_
#define _CMDUPPERLEFTTOLEFTBACK_HG_

#include <frc/WPILib.h>
#include <frc/Timer.h>
#include <frc/commands/Command.h>
#include "Autonomous/Profiles/PFLLowerLeftToLeftBack.h"

/**
 *
 */
class CMDLowerLeftToLeftBack : public frc::Command
{
public:
	CMDLowerLeftToLeftBack();
	~CMDLowerLeftToLeftBack();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	PFLLowerLeftToLeftBack* pMotionProfiler;
	Timer* pTimer;
};

#endif
