//! An interface command for activating the Pull Arm on the robot
#ifndef _RaiseLegs_HG_
#define _RaiseLegs_HG_

#include <frc/commands/TimedCommand.h>

class RaiseLegs : public frc::TimedCommand {
public:
	explicit RaiseLegs(double speed, double timeout);
	void Initialize() override;
	void Execute() override;
	void End() override;
	void Interrupted() override;
private:
	double speed;
};

#endif // _RaiseLegs_HG_