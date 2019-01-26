#ifndef _CMDRIGHTBACKTORIGHTSTATION_HG_
#define _CMDRIGHTBACKTORIGHTSTATION_HG_

#include <frc/WPILib.h>
#include <frc/Timer.h>
#include <frc/commands/Command.h>
#include "Autonomous/Profiles/PFLRightBackToRightStation.h"

/**
 *
 */
class CMDRightBackToRightStation : public frc::Command
{
public:
	CMDRightBackToRightStation();
	~CMDRightBackToRightStation();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	PFLRightBackToRightStation* pMotionProfiler;
	Timer* pTimer;
};

#endif
