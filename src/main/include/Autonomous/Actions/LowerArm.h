/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef _LOWERARM_HG_
#define _LOWERARM_HG_

#include <frc/commands/TimedCommand.h>

class LowerArm : public frc::TimedCommand {
public:
	explicit LowerArm(float speed, float timeout);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
private:
	float speed; //!< Whole-percent power to use for arm
};

#endif /* _LOWERARM_HG_ */
