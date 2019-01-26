#ifndef _CMDCENTERTOFRONTLEFT_HG_
#define _CMDCENTERTOFRONTLEFT_HG_

#include <frc/WPILib.h>
#include <frc/Timer.h>
#include <frc/commands/Command.h>
#include "Autonomous/Profiles/PFLCenterToFrontLeft.h"

/**
 *
 */
class CMDCenterToFrontLeft : public frc::Command
{
public:
	CMDCenterToFrontLeft();
	~CMDCenterToFrontLeft();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	PFLCenterToFrontLeft* pMotionProfiler;
	Timer* pTimer;
};

#endif
