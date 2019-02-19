/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef _LOWERARM_HG_
#define _LOWERARM_HG_

#include <frc/commands/TimedCommand.h>

#define PREDEFINED_ARM_SPEED	0.5	//whole-percent
#define TIMEOUT_TIME	0.1	//seconds

class LowerArm : public frc::TimedCommand {
public:
	explicit LowerArm();
	void Initialize() override;
	void Execute() override;
	void End() override;
	void Interrupted() override;
};

#endif /* _LOWERARM_HG_ */
