/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef _FINISHCLIMB_HG_
#define _FINISHCLIMB_HG_

#include <frc/commands/Command.h>
#include <frc/Timer.h>

class FinishClimb : public frc::Command {
public:
	FinishClimb();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
private:
	frc::Timer* pTimer;
};

#endif /* _FINISHCLIMB_HG_ */