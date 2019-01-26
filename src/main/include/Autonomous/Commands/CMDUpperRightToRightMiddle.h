#ifndef _CMDUPPERRIGHTTORIGHTMIDDLE_HG_
#define _CMDUPPERRIGHTTORIGHTMIDDLE_HG_

#include <frc/WPILib.h>
#include <frc/Timer.h>
#include <frc/commands/Command.h>
#include "Autonomous/Profiles/PFLUpperRightToRightMiddle.h"

/**
 *
 */
class CMDUpperRightToRightMiddle : public frc::Command
{
public:
	CMDUpperRightToRightMiddle();
	~CMDUpperRightToRightMiddle();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	PFLUpperRightToRightMiddle* pMotionProfiler;
	Timer* pTimer;
};

#endif
