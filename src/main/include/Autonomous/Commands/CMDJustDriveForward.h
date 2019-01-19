#ifndef _CMDJUSTDRIVEFORWARD_HG_
#define _CMDJUSTDRIVEFORWARD_HG_

#include <frc/WPILib.h>
#include <frc/Timer.h>
#include <frc/commands/Command.h>
#include "Autonomous/Profiles/PFLJustDriveForward.h"

/**
 *
 */
class CMDJustDriveForward : public frc::Command
{
public:
	CMDJustDriveForward();
	~CMDJustDriveForward();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	PFLJustDriveForward* pMotionProfiler;
	Timer* pTimer;
};

#endif
