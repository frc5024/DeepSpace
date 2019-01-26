#ifndef _CMDUPPERLEFTTOLEFTBACK_HG_
#define _CMDUPPERLEFTTOLEFTBACK_HG_

#include <frc/WPILib.h>
#include <frc/Timer.h>
#include <frc/commands/Command.h>
#include "Autonomous/Profiles/PFLUpperLeftToLeftBack.h"

/**
 *
 */
class CMDUpperLeftToLeftBack : public frc::Command
{
public:
	CMDUpperLeftToLeftBack();
	~CMDUpperLeftToLeftBack();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	PFLUpperLeftToLeftBack* pMotionProfiler;
	Timer* pTimer;
};

#endif
