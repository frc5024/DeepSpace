#ifndef _CMDUPPERRIGHTTORIGHTBACK_HG_
#define _CMDUPPERRIGHTTORIGHTBACK_HG_

#include <frc/WPILib.h>
#include <frc/Timer.h>
#include <frc/commands/Command.h>
#include "Autonomous/Profiles/PFLUpperRightToRightBack.h"

/**
 *
 */
class CMDUpperRightToRightBack : public frc::Command
{
public:
	CMDUpperRightToRightBack();
	~CMDUpperRightToRightBack();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	PFLUpperRightToRightBack* pMotionProfiler;
	Timer* pTimer;
};

#endif
