#ifndef _CMDJUSTDRIVEFORWARDTIMED_HG_
#define _CMDJUSTDRIVEFORWARDTIMED_HG_

#include <frc/WPILib.h>
#include <frc/Timer.h>
#include <frc/commands/Command.h>

/**
 *
 */
class CMDJustDriveForwardTimed : public frc::Command
{
public:
	CMDJustDriveForwardTimed(double speed = 0.3, double rotation = 0.0, double duration = 2.0);
	~CMDJustDriveForwardTimed();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	frc::Timer* pTimer;
    double dSpeed, dRotation, dDuration;
};

#endif