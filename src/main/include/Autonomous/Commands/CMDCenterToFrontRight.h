#ifndef _CMDCENTERTOFRONTRIGHT_HG_
#define _CMDCENTERTOFRONTRIGHT_HG_

#include <frc/WPILib.h>
#include <frc/Timer.h>
#include <frc/commands/Command.h>
#include "Autonomous/Profiles/PFLCenterToFrontRight.h"

/**
 *
 */
class CMDCenterToFrontRight : public frc::Command
{
public:
	CMDCenterToFrontRight();
	~CMDCenterToFrontRight();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	PFLCenterToFrontRight* pMotionProfiler;
	Timer* pTimer;
};

#endif
