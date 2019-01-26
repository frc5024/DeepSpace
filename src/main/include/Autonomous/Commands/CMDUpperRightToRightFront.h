#ifndef _CMDUPPERRIGHTTORIGHTFRONT_HG_
#define _CMDUPPERRIGHTTORIGHTFRONT_HG_

#include <frc/WPILib.h>
#include <frc/Timer.h>
#include <frc/commands/Command.h>
#include "Autonomous/Profiles/PFLUpperRightToRightFront.h"

/**
 *
 */
class CMDUpperRightToRightFront : public frc::Command
{
public:
	CMDUpperRightToRightFront();
	~CMDUpperRightToRightFront();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	PFLUpperRightToRightFront* pMotionProfiler;
	Timer* pTimer;
};

#endif
